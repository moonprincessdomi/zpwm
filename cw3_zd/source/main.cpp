#include<string>
#include <Windows.h>
#include "res.h"
#include <ctime>
#include <cstdlib>

int a = 0;

void bigger_smaller(int a, int b) {

	char txt[100];
	char txt1[100];
	sprintf_s(txt, "a = %d", a);
	sprintf_s(txt1, "b  = %d", b);
	MessageBox(0, txt1, txt, MB_OK);

	if (a == b) {
		MessageBox(0,"Wygrales" ,"Wygrales!", MB_OK);
	}
	else if (a > b) {
		MessageBox(0, "Moja liczba jest wieksza niz Twoja", "Jeszcze raz", MB_OK);
	}
	else {
		MessageBox(0, "Moja liczba jest mniejsza niz Twoja", "Jeszcze raz", MB_OK);
	}
	return;
}

INT_PTR CALLBACK DialogProc(HWND hwndDIg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) 
	{
	case WM_COMMAND:
		switch (HIWORD(wParam)) 
		{
		case BN_CLICKED:
			switch (LOWORD(wParam)) 
			{
			case IDC_BUTTON1:
				HWND hwndEditBox = GetDlgItem(hwndDIg, IDC_EDIT1);
					int iTextLenght = GetWindowTextLength(hwndEditBox);
				CHAR szText[500];
				GetWindowText(hwndEditBox, szText, iTextLenght + 1);
				int b = 0;
				int c = 1;

				for (int i = iTextLenght-1; i >= 0; i--)
				{
					int temp = szText[i] - '0';
					b = b + temp* c;
					c = c * 10;
				}
				c = 1;
				bigger_smaller(a, b);
				return TRUE;
			}
		}
		return FALSE;
	case WM_CLOSE:
		DestroyWindow(hwndDIg);
		PostQuitMessage(0);
		return TRUE;
	}
	return FALSE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
	srand(time(NULL));
	a = rand()%40 + 1;

	HWND hwndMainWindow = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, DialogProc);
	ShowWindow(hwndMainWindow, iCmdShow);

	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}