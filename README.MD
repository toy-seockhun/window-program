# Window Programming

**REF LINK** : [The Pentamollis Project - YouTube](https://www.youtube.com/channel/UCjsG1HaLXHytO8bG3_TIakQ)

```c++
// WNDCLASSW : WINDOW CLASS, Initiate window program.
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
    wc.hbrBackground = (BRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"Program Name";
    wc.lpfnWndProc = WindowProcedure; // Callback function Name
    
    CreateWindow(L"Program Name",
                L"My Window",
                WS_OVERLAPPEDWINDOW | WS_VISIBLE
                100, 100, 500, 500,
                NULL, NULL, NULL, NULL);
    
    MSG msg = { 0 };
    while( GetMessage(&msg), NULL, NULL, NULL) ){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProcW(hWnd, msg, wp, lp);
    }
}
```

Above script is code to organize base template of *Window Program*. All of the function and constants are derived at <windows.h> header.

You can add menus and controls with **AppendMenu** and **CreateWindowW** function. Pleases read script on <u>*menu-control-basis*</u> branch

