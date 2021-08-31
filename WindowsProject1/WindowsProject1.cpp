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
void loadImages();

HWND hName, hAge, hOut, hLogo;
HMENU hMenu;
HBITMAP hLogoImage, hGenerateImage;

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

	MSG msg = { 0 };

	while ( GetMessage((&msg), NULL, NULL, NULL) ){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	int val;
	switch (msg) {
	case WM_COMMAND:
		switch (wp) {
		case FILE_MENU_EXIT:
			val = MessageBoxW(hWnd, L"Are you sure?", L"Wait!", MB_YESNO | MB_ICONEXCLAMATION);
			if (val == IDYES)
			{
				DestroyWindow(hWnd);
			}
			// DestroyWindow(hWnd);
			break;
		case FILE_MENU_NEW:
			MessageBeep(MB_ICONINFORMATION);
			break;
		case GENERATE_BUTTON:
			wchar_t name[30], age[10], out[50];

			GetWindowText(hName, name, 30);
			GetWindowText(hAge, age, 10);

			if (wcscmp(name, L"") == 0 || wcscmp(age, L"") == 0) {
				val = MessageBoxW(hWnd, L"You did not enter anything !", NULL, MB_ABORTRETRYIGNORE | MB_ICONERROR);
				switch (val)
				{
				case IDABORT:
					DestroyWindow(hWnd);
					break;
				case IDRETRY:
					return 0;
				case IDIGNORE:
					break;
				}
;			}

			wcscpy(out, name);
			wcscat(out, L" is ");
			wcscat(out, age);
			wcscat(out, L" years old.");

			SetWindowText(hOut, out);

			break;
		}
		break; 
	case WM_CREATE:
		loadImages();
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

	HWND hBut = CreateWindowW(L"button", NULL,
		WS_VISIBLE | WS_CHILD | BS_BITMAP,
		150, 140, 98, 38, hWnd,
		(HMENU)GENERATE_BUTTON, NULL, NULL); 
	SendMessageW(hBut, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hGenerateImage);

	hOut = CreateWindowW(L"edit", L"",
		WS_VISIBLE | WS_CHILD | WS_BORDER,
		100, 200, 300, 200, hWnd,
		NULL, NULL, NULL);

	hLogo = CreateWindowW(L"static", NULL,
		WS_VISIBLE | WS_CHILD | SS_BITMAP,
		350, 60, 100, 100, hWnd,
		NULL, NULL, NULL);
	SendMessageW(hLogo, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) hLogoImage);
}

void loadImages(){
	hLogoImage = (HBITMAP)LoadImageW(NULL, L"blob640.bmp", IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
	hGenerateImage = (HBITMAP)LoadImageW(NULL, L"universe640.bmp", IMAGE_BITMAP, 98, 38, LR_LOADFROMFILE);
}