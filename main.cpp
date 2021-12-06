#include <stdio.h>
//#pragma warning(push,0)
#include <Windows.h>
#include <winbase.h>
//#pragma warning(pop)



LRESULT CALLBACK MainWndProc(HWND WindowHandle, UINT Message, WPARAM WParam, LPARAM LParam);


DWORD CreateMainGameWindow(HANDLE Instance);

// HINSTANCE hInstance : handle memory address input function to the main address
//PSTR pointer to string long comand line
int WinMain(
    _In_ HANDLE Instance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd
)
    
{
    if (CreateMainGameWindow(Instance) != ERROR_SUCCESS) {

        goto Exit;
    }

    // this recive message 

  

    MSG Message;

    while (GetMessageA(&Message, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Message);
        DispatchMessageA(&Message);
    }
Exit:
    return 0;
}


LRESULT CALLBACK MainWndProc(HWND WindowHandle, UINT Message, WPARAM WParam, LPARAM LParam)
{

    LRESULT Ruselt = 0; 
    switch (Message)
    {

    default:
         Ruselt = DefWindowProc(WindowHandle, Message, WParam, LParam);
    }
    return Ruselt;
}


DWORD CreateMainGameWindow(HANDLE Instance) {
    DWORD Ruselt = ERROR_SUCCESS;

    WNDCLASSEXA WindowClass;
    memset(&WindowClass, 0, sizeof(WindowClass));

    HWND WindowHandle = 0;


    WindowClass.cbSize = sizeof(WNDCLASSEXA);

    WindowClass.style = 0;

    WindowClass.lpfnWndProc = MainWndProc; // long pointer proc

    WindowClass.cbClsExtra = 0;

    WindowClass.cbWndExtra = 0;

    WindowClass.hInstance = Instance; // is same of "hInstance"

    WindowClass.hIcon = LoadIconA(NULL, IDI_APPLICATION);

    WindowClass.hIconSm = LoadIconA(NULL, IDI_APPLICATION);

    WindowClass.hCursor = LoadCursorA(NULL, IDC_ARROW);

    WindowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    WindowClass.lpszMenuName = NULL;

    WindowClass.lpszClassName = "Hamad_Game_WIDOWCLASS";



    if (!RegisterClassExA(&WindowClass)) // if fails it will be return 0;
    {
        Ruselt = GetLastError();
        MessageBoxA(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        goto Exit;
    }

    WindowHandle = CreateWindowExA(WS_EX_CLIENTEDGE, WindowClass.lpszClassName, "The window Title", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 240, 120, NULL, NULL, Instance, NULL);

    if (WindowHandle == NULL) //if fails it will be return 0;
    {
        Ruselt = GetLastError();
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        goto Exit;
    }
Exit:
    return Ruselt;
}