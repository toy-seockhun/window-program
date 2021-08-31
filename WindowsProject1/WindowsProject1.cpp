#include <windows.h>
#include<stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define GENERATE_BUTTON 4

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void AddMenus(HWND);
void AddControls(HWND);

HWND hName, hAge, hOut;
HMENU hMenu;
POINT p;

HHOOK _k_hook;
LRESULT __stdcall k_Callback1(int nCode, WPARAM wParam, LPARAM lParam)
{
	PKBDLLHOOKSTRUCT key = (PKBDLLHOOKSTRUCT)lParam;
	//a key was pressed
	if (wParam == WM_KEYDOWN && nCode == HC_ACTION)
	{
		wchar_t res[30];
		swprintf_s(res, L"0x%x pressed.", key->vkCode);
		SetWindowText(hOut, res);
	}

	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
	WNDCLASSW wc = { 0 };
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInst;
	wc.lpszClassName = L"myWindowClass";
	wc.lpfnWndProc = WindowProcedure;

	if (!RegisterClassW(&wc))
		return -1;

	CreateWindow(L"myWindowClass", L"My Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 500,
		NULL, NULL, NULL, NULL);
	
	_k_hook = SetWindowsHookEx(WH_KEYBOARD_LL, k_Callback1, NULL, 0);
	MSG msg = { 0 };

	while ( GetMessage((&msg), NULL, NULL, NULL) ){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	if (_k_hook)
		UnhookWindowsHookEx(_k_hook);

	return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg) {
	case WM_COMMAND:
		switch (wp) {
		case FILE_MENU_EXIT:
			DestroyWindow(hWnd);
			break;
		case FILE_MENU_NEW:
			MessageBeep(MB_ICONINFORMATION);
			break;
		case GENERATE_BUTTON:
			wchar_t name[30], age[10], out[50];

			GetWindowText(hName, name, 30);
			GetWindowText(hAge, age, 10);

			wcscpy(out, name);
			wcscat(out, L" is ");
			wcscat(out, age);
			wcscat(out, L" years old.");

			SetWindowText(hOut, out);

			break;
		}
		break; 
	case WM_CREATE:
		AddMenus(hWnd);
		AddControls(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProcW(hWnd, msg, wp, lp);
	}
}

void AddMenus(HWND hWnd) {
	hMenu = CreateMenu();
	HMENU hFileMenu = CreateMenu();
	HMENU hSubMenu = CreateMenu();

	AppendMenu(hSubMenu, MF_STRING, NULL, L"SubMenu Item");

	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_NEW, L"New");
	AppendMenu(hFileMenu, MF_POPUP, (UINT_PTR)hSubMenu, L"Open SubMenu");
	AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, L"Exit");

	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, L"File");
	AppendMenu(hMenu, MF_STRING, NULL, L"Help");

	SetMenu(hWnd, hMenu);
}

void AddControls(HWND hWnd) {
	CreateWindowW(L"static", L"Name :",
		WS_VISIBLE | WS_CHILD,
		100, 50, 98, 38, hWnd,
		NULL, NULL, NULL);  
	hName = CreateWindowW(L"edit", L"",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		200, 50, 98, 38, hWnd,
		NULL, NULL, NULL);

	CreateWindowW(L"static", L"Age :",
		WS_VISIBLE | WS_CHILD,
		100, 90, 98, 38, hWnd,
		NULL, NULL, NULL);
	hAge = CreateWindowW(L"edit", L"",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		200, 90, 98, 38, hWnd,
		NULL, NULL, NULL);

	CreateWindowW(L"button", L"Generate",
		WS_VISIBLE | WS_CHILD,
		150, 140, 98, 38, hWnd,
		(HMENU)GENERATE_BUTTON, NULL, NULL);

	hOut = CreateWindowW(L"edit", L"",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		100, 200, 300, 200, hWnd,
		NULL, NULL, NULL);
}