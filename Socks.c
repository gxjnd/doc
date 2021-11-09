
#define _GNU_SOURCE
#include <sys/types.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <netdb.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <pthread.h>






typedef struct _socks5 socks5_t;

struct _socks5 {
  uint8_t command;
  char *domainName;
  int fd;
  uint8_t *ipv4;
  uint16_t *ipv6;
  char *password;
  uint16_t port;
  char *username;
};



void socks5_set_command(socks5_t *socks5, int command) {
  socks5->command = command;
}


static int get_ipv4(socks5_t *socks5, char *address) {
  uint32_t index = 0;
  uint32_t len = 0;
  uint32_t length = strlen(address);
  uint32_t tmp[4] = {0};
  for (uint32_t itr = 0; itr != length; ++itr) {
    if (index == 4)
      return 0;
    if (address[itr] >= '0' && address[itr] <= '9') {
      if (len == 0 && address[itr] == '0' && address[itr + 1] != 0 &&
          address[itr + 1] != '.')
        return -1;
      tmp[index] = tmp[index] * 10 + address[itr] - '0';
      ++len;
      if (tmp[index] > 255)
        return -1;
    } else if (address[itr] == '.') {
      len = 0;
      ++index;
    }
  }
  socks5->ipv4 = (uint8_t *)malloc(sizeof(uint8_t) * 4);
  for (uint32_t itr = 0; itr != 4; ++itr)
    socks5->ipv4[itr] = tmp[itr];
  return 0;
}

static int get_ipv6(socks5_t *socks5, char *address) {
  uint32_t index = 0;
  uint32_t len = 0;
  uint32_t length = strlen(address);
  uint32_t tmp[8] = {0};
  for (uint32_t itr = 0; itr != length; ++itr) {
    if (index == 8)
      return -1;
    if ((address[itr] >= '0' && address[itr] <= '9') ||
        (address[itr] >= 'a' && address[itr] <= 'f') ||
        (address[itr] >= 'A' && address[itr] <= 'F')) {
      if (len == 3)
        return -1;
      tmp[index] *= 16;
      if (address[itr] >= '0' && address[itr] <= '9')
        tmp[index] += address[itr] - '0';
      else if (address[itr] >= 'a' && address[itr] <= 'f')
        tmp[index] += address[itr] - 'a' + 10;
      else if (address[itr] >= 'A' && address[itr] <= 'F')
        tmp[index] += address[itr] - 'A' + 10;
      ++len;
    } else if (address[itr] == ':') {
      len = 0;
      ++index;
    }
  }
  socks5->ipv6 = (uint16_t *)malloc(sizeof(uint16_t) * 8);
  for (uint32_t itr = 0; itr != 8; ++itr)
    socks5->ipv6[itr] = tmp[itr];
  return 0;
}

static int get_domainName(socks5_t *socks5, char *address) {
  uint32_t length = strlen(address);
  if (length > 255)
    return -1;
  socks5->domainName = strdup(address);
}

int socks5_set_address(socks5_t *socks5, char *address, uint16_t port) {
  {
    if (address == NULL && strlen(address) > 255)
      return -1;
    if (socks5->domainName != NULL)
      free(socks5->domainName);
    if (socks5->ipv4 != NULL)
      free(socks5->ipv4);
    if (socks5->ipv6 != NULL)
      free(socks5->ipv6);
    if (socks5->password != NULL)
      free(socks5->password);
    if (socks5->username != NULL)
      free(socks5->username);
  }
  socks5->port = port;
  if (get_ipv4(socks5, address) == 0)
    return 0;
  else if (get_ipv6(socks5, address) == 0)
    return 0;
  else if (get_domainName(socks5, address) == 0)
    return 0;
  return -1;
}


int socks5_connect_user(socks5_t *socks5) {}

int socks5_set_user_password(socks5_t *socks5, char *username, char *password) {
  if (strlen(username) > 255 || strlen(password) > 255)
    return -1;
  if (socks5->username != NULL)
    free(socks5->username);
  if (socks5->password != NULL)
    free(socks5->password);
  socks5->username = strdup(username);
  socks5->password = strdup(password);
  return 0;
}




/*
 * @brief Method
 *
 * 0x00         : NO AUTHENTICATION REQUIRED
 * 0x01         : GSSAPI
 * 0x02         : USERNAME / PASSWORD
 * 0x03 to 0x7F : IANA ASSIGNED
 * 0x80 to 0xFE : RESERVED FOR PRIVATE METHODS
 * 0xFF         : NO ACCEPTABLE METHODS
 */

static int reponse_method(socks5_t *socks5, unsigned char method) {
  if (method == 0x00)
    return 0;
  else if (method == 0x01)
    return -1;
  else if (method == 0x02)
    return socks5_connect_user(socks5);
  else if (method >= 0x03 && method <= 0x7F)
    return -1;
  else if (method >= 0x80 && method <= 0xFE)
    return -1;
  else
    return -1;
}

static int request_method_dependent(socks5_t *socks5) {
  uint32_t lenght = 0;
  unsigned char msg[512] = {0};
  msg[0] = 0x05;
  msg[1] = socks5->command;
  msg[2] = 0x00;
  if (socks5->ipv4 != NULL) {
    msg[3] = 0x01;
    msg[4] = socks5->ipv4[0];
    msg[5] = socks5->ipv4[1];
    msg[6] = socks5->ipv4[2];
    msg[7] = socks5->ipv4[3];
    msg[8] = 0;
    msg[9] = 80;
    lenght = 10;
  } else if (socks5->domainName != NULL) {
    msg[3] = 0x03;
    msg[4] = (uint8_t)strlen(socks5->domainName);
    for (uint32_t itr = 0; itr != msg[4]; ++itr)
      msg[itr + 5] = socks5->domainName[itr];
    lenght = 10;
  } else if (socks5->ipv6 != NULL) {
    msg[3] = 0x04;
    lenght = 10;
  }
  write(socks5->fd, msg, lenght);
}

int socks5_connect(socks5_t *socks5) {
  if (socks5->fd == -1)
    return -1;
  write(socks5->fd, "\x05\x01\x00", 3);
  unsigned char tmp[512];
  if (read(socks5->fd, tmp, 512) != 2)
    return -1;
  reponse_method(socks5, tmp[1]);
  request_method_dependent(socks5);
  int ret = read(socks5->fd, tmp, 512);
  if (tmp[1] != 0){
    //printf("service rley erro\n");
return -1;
  }
  


char        sndBuf[1024] = {0};
char        rcvBuf[2048] = {0};
int         num          = 0;
char       *pRcv         = rcvBuf;

sprintf(sndBuf, "GET / HTTP/1.1/n");

strcat(sndBuf, "Host: oocitynotbad.ga/n/r/n");


  
write(socks5->fd, sndBuf, sizeof(sndBuf));
  

    
    
  return 0;
}




int main(){
  


	
socks5_t socks5 = {0};
  socks5.fd = socket(AF_INET, SOCK_STREAM, 0);
  if (socks5.fd == -1)
  {
    return -1;
  }
	
struct sockaddr_in addr = {0};
 

	
bzero(&addr, sizeof(addr)); 

  

addr.sin_addr.s_addr = inet_addr("127.0.0.1");
addr.sin_family = AF_INET;
addr.sin_port = htons(1080);

    // connect the client socket to server socket 

  if (connect(socks5.fd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
      printf("connect failed\n");
      return -1;
    }
    printf("connect wait \n");
    
socks5_set_command(&socks5, 0x01);

//func(sock_fd);



//close(sock_fd); 

	


socks5_set_address(&socks5, "192.227.227.210", atoi("80"));
socks5_connect(&socks5);


  


  return 0;
}





