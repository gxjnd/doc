
#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>

#include<netinet/in.h>
#include<string.h>

#include <unistd.h> // for close

int main() {

// socket -> connect -> recv
// create a socket
char server_message[256] = "you have reached the server!"; 
char data[256] ;


char filename[128]="a.txt";


int ret ;
int i ;
int network_socket;
network_socket = socket(AF_INET, SOCK_STREAM,0);
FILE *fp;

fp=fopen(filename,"rb");
    if(fp==NULL){
        printf("can't open file \n");
        return 0;
        }


// specify an address for the socket
struct sockaddr_in server_address;
server_address.sin_family = AF_INET;
server_address.sin_port = htons(8888);
server_address.sin_addr.s_addr =INADDR_ANY;
int bytes;



start:
while(connect(network_socket, (struct sockaddr * ) &server_address,sizeof(server_address))==-1){
    printf("connect fail\n");

    sleep(0.6);
    goto start;
    }
		
/*
int connection_status = 


connect(network_socket, (struct sockaddr * ) &server_address,sizeof(server_address))                                  
*/

// check for error with the connection
/*
if (connection_status == -1){
printf("There was an error a to the renvote socket ");
}
*/

// recieve data from the server
//send(network_socket, server_message, sizeof(server_message) ,0);
send(network_socket, filename, strlen(filename) ,0);
//printf("%d\n",sizeof(server_message));

send(network_socket,"\0",1,0);
    printf("send contxt ..");
    
for(;;){
        memset((void *)data,0,sizeof(data));
        i=fread(data,1,sizeof(data),fp);
        if(i==0){
            printf("\nsend success\n");
            break;
            }
        ret=send(network_socket,data,i,0);
        putchar('.');
        if(ret==-1){
            printf("\n send fail\n");
            break;
            }
        }
    fclose(fp);
    
    
    
  
/*
char  server_response[256];
char *append =server_response;


bytes = recv(network_socket, append, 256 ,0);


// print out the server's response
printf ( "server sent the data %s\n" ,server_response);
// and then close the socket
printf("sizeof%d\n", sizeof(append));
printf("%d\n",bytes);


server_response[bytes] = 0;
printf("%c\n",server_response[bytes] );
*/
close(network_socket) ;
return 0;
}
