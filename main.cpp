#include <stdio.h>
//#pragma warning(push,0)
#include <Windows.h>
#include <winbase.h>
//#pragma warning(pop)



LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


// HINSTANCE hInstance : handle memory address input function to the main address
//PSTR pointer to string long comand line
int WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd
)
{


    // this recive message 

    WNDCLASSEXA WindowClass;
    memset(&WindowClass, 0, sizeof(WindowClass));

    HWND WindowHandle = 0;


    WindowClass.cbSize = sizeof(WNDCLASSEXA);

    WindowClass.style = 0;

    WindowClass.lpfnWndProc = MainWndProc; // long pointer proc

    WindowClass.cbClsExtra = 0;

    WindowClass.cbWndExtra = 0;

    WindowClass.hInstance = hInstance;

    WindowClass.hIcon = LoadIconA(NULL, IDI_APPLICATION);

    WindowClass.hCursor = LoadCursorA(NULL, IDC_ARROW);

    WindowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    WindowClass.lpszMenuName = NULL;

    WindowClass.lpszClassName = "Hamad_Game_WIDOWCLASS";

    WindowClass.hIconSm = LoadIconA(NULL, IDI_APPLICATION);

    if (!RegisterClassExA(&WindowClass)) // if fails it will be return 0;
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    WindowHandle = CreateWindowExA(WS_EX_CLIENTEDGE, WindowClass.lpszClassName,"The window Title", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 240, 120, NULL, NULL, hInstance, NULL);

    if (WindowHandle == NULL) //if fails it will be return 0;
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }


    MSG Message = { 0 };

    while (GetMessageA(&Message, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Message);
        DispatchMessageA(&Message);
    }
    return 0;
}


LRESULT CALLBACK MainWndProc(
    HWND hwnd,        // handle to window
    UINT uMsg,        // message identifier
    WPARAM wParam,    // first message parameter
    LPARAM lParam)    // second message parameter
{

    switch (uMsg)
    {
    case WM_CREATE:
        // Initialize the window. 
        return 0;

    case WM_PAINT:
        // Paint the window's client area. 
        return 0;

    case WM_SIZE:
        // Set the size and position of the window. 
        return 0;

    case WM_DESTROY:
        // Clean up window-specific data objects. 
        return 0;

        // 
        // Process other messages. 
        // 

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}