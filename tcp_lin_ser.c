
#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>

#include<netinet/in.h>
#include<pthread.h>

#include <string.h>

#include <unistd.h> // for close
void * serve_client(void * client_socket);




int main() {

// socket -> bind -> listen -> accept


char server_message[256] = "you have reached the server!"; 

// create the server socket
int server_socket;
server_socket = socket(AF_INET, SOCK_STREAM,0);


// define the server address
struct sockaddr_in server_address;
server_address.sin_family = AF_INET;
server_address.sin_port = htons(8888);
server_address.sin_addr.s_addr =INADDR_ANY;

// bind the socket to our specified IP and port
bind(server_socket ,(struct sockaddr*) &server_address,sizeof(server_address));

listen(server_socket,5);
int client_socket;
pthread_t tid[128];
int count_thread= 0;

for(;;) {
  client_socket = accept(server_socket ,NULL,NULL);
  //send
 // printf("$$$$\n");
 // send(client_socket, server_message, sizeof(server_message) ,0);
  
  pthread_create(tid+count_thread,NULL,serve_client, (void *)&client_socket);
  
  
  sleep(1);
  
}


// and then close the socket
close(server_socket) ;



  return 0;
  
  
}




void * serve_client(void * client_socket){
int bytes;
  int i;
  char c;
  
FILE *fp;
char  server_response[256];
char  data[256];
  //char *append =server_response;
  
  int * client_sock = (int *) client_socket;
  
 // bytes = recv(*client_sock, append, 256 ,0);
  // print out the server's response
 // printf ( "server sent the data %s\n" ,server_response);

  for(i=0; i<sizeof(server_response);i++){
      if(recv(*client_sock,&c,1,0)!=1){
          printf("recv fail\n");
          close(*client_sock) ;
          return (void *)0;
          }
      if(c==0){
          break;
          }
      server_response[i]=c;
      }
      printf("%s\n",server_response);

char cstr[80];
    int j=0;
    int k = 0;
    for(k; server_response[k]!='\0'; k++)
	{     
    cstr[j]= server_response[k];
  
	j++;
	}
	
	  printf("\n------%s",cstr);



        fp=fopen(cstr,"wb");
        if(fp==NULL){
            printf("can't write to file for save \n");
            close(*client_sock) ;
            return (void *)0;
        }
        
        printf("recv context");
  
  memset((void *)data, 0,sizeof(data));
       
for(;;){





  i=recv(*client_sock,data,sizeof(data),0);
  putchar('.');
  if(i==-1){
      printf("\n reve contxt fail\n");
      break;
      }
  else if(i==0){
    
      printf("\n recv success\n");
      break;
      }
  else{
      fwrite((void *)data,1,i,fp);
      }
  }
  
  
printf("%s",data);
fclose(fp);
        
              
              
  
  
pthread_exit(NULL);
}



