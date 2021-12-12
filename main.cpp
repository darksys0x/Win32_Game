#include <stdio.h>
//#pragma warning(push,0)
#include <Windows.h>
#include <winbase.h>
//#pragma warning(pop)
#include "main.h"



_In_opt_ HWND gGameWindow;
BOOL gGameIsRunning; 


int WinMain(
    _In_ HINSTANCE Instance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd
)
    
{

    if (Game_is_running() == TRUE) {

        MessageBoxA(NULL, "Another instance of this program is already running!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        goto Exit;
    }

    if (CreateMainGameWindow() != ERROR_SUCCESS) {

        goto Exit;

    }

    // this recive message 

  

    MSG Message; 
    gGameIsRunning = TRUE;
    while (gGameIsRunning == TRUE)// will keep the running untel the gGameIsRunning switch to False 
    {
        while (PeekMessageA(&Message, gGameWindow, 0, 0, PM_REMOVE)) {

            DispatchMessageA(&Message);


        } //peekMessage is very similer to  getMessage accept peekmessage dosont block  implies

        // processPlayerInput();
       //  RenderFrameGraphics();
    }

      
Exit:
    return 0;
}


LRESULT CALLBACK MainWndProc(_In_ HWND WindowHandle, _In_ UINT Message, _In_ WPARAM WParam, _In_ LPARAM LParam)
{
    //char buf[12] = { 0 };
    //_itoa(Message, buf, 10); //10 base 
    //OutputDebugStringA(buf);
    //OutputDebugStringA("\n");
    LRESULT Ruselt = 0; 
    switch (Message)
    {
      
       case WM_CLOSE://If an application processes this message, it should return zero.
        {
           gGameIsRunning == FALSE;
           PostQuitMessage(0); // since the user hit the close butten that will change the "gGameIsRunning" to false 
           break;
        }

    default:
         Ruselt = DefWindowProc(WindowHandle, Message, WParam, LParam);
    }
    return Ruselt;
}


DWORD CreateMainGameWindow(void) {
    DWORD Ruselt = ERROR_SUCCESS;

    WNDCLASSEXA WindowClass;
    memset(&WindowClass, 0, sizeof(WindowClass));



    WindowClass.cbSize = sizeof(WNDCLASSEXA);

    WindowClass.style = 0;

    WindowClass.lpfnWndProc = MainWndProc; // long pointer proc

    WindowClass.cbClsExtra = 0;

    WindowClass.cbWndExtra = 0;

    WindowClass.hInstance = GetModuleHandleA(NULL); // is same of "hInstance"

    WindowClass.hIcon = LoadIconA(NULL, IDI_APPLICATION);

    WindowClass.hIconSm = LoadIconA(NULL, IDI_APPLICATION);

    WindowClass.hCursor = LoadCursorA(NULL, IDC_ARROW);

    WindowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    WindowClass.lpszMenuName = NULL;

    WindowClass.lpszClassName = GAME_NAME "Hamad_Game_WIDOWCLASS";



    if (!RegisterClassExA(&WindowClass)) // if fails it will be return 0;
    {
        Ruselt = GetLastError();
        MessageBoxA(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        goto Exit;
    }

    gGameWindow = CreateWindowExA(WS_EX_CLIENTEDGE, WindowClass.lpszClassName, "Hamad Game", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 240, 120, NULL, NULL, GetModuleHandle(NULL), NULL);

    if (gGameWindow == NULL) //if fails it will be return 0;
    {
        Ruselt = GetLastError();
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        goto Exit;
    }
Exit:
    return Ruselt;
}

BOOL Game_is_running(void) {
    HANDLE Mutex = NULL;
    Mutex = CreateMutexA(NULL, FALSE, GAME_NAME "_Hamad Game");
    
        if (GetLastError() == ERROR_ALREADY_EXISTS) {
            return TRUE;
        
        }
        else
        {
            return FALSE;
        }


}