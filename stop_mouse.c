#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include<time.h>

int hideConsole ( void );
 

int main()
{
	hideConsole();
	int x,y;//������������λ��
	while(!_kbhit())
	{
		x=rand()%1+300;
		y=rand()%1+300;
		SetCursorPos(x,y);
		Sleep(500);
	}
	return 0;
}



int hideConsole ( void )
{
  

HWND hWnd = GetConsoleWindow();
   // ShowWindow( hWnd, SW_MINIMIZE );
    ShowWindow( hWnd, SW_HIDE );

return 0;
}
 
