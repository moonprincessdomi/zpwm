#include<string>
#include <Windows.h>
#include "res.h"

bool isGameOn = false;
bool isFirstPlayerTurn = true;
bool isSecondPlayerTurn = false;

INT_PTR CALLBACK DialogProc(HWND hwndDIg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) 
	{
	case WM_COMMAND:
		switch (HIWORD(wParam)) 
		{
		case BN_CLICKED:
			switch (LOWORD(wParam)) 
			{
			case IDC_BUTTON2:
			case IDC_BUTTON3:
			case IDC_BUTTON4:
			case IDC_BUTTON5:
			case IDC_BUTTON6:
			case IDC_BUTTON7:
			case IDC_BUTTON8:
			case IDC_BUTTON9:
			case IDC_BUTTON10:
			{
				HWND hwndButton = (HWND)lParam;
				if (GetWindowTextLength(hwndButton) == 0)
				{
					CHAR szText[500];

					if (isFirstPlayerTurn == true) {
						wsprintf(szText, "X");
					}
					else {
						wsprintf(szText, "O");
					}
					SetWindowText(hwndButton, szText);
					isFirstPlayerTurn = !isFirstPlayerTurn;
				}
				return TRUE;
			}
			case IDC_BUTTON1:
				if (isGameOn = false)
				{
					isGameOn = true;
					HWND hwndStatic = GetDlgItem(hwndDIg, IDC_STATIC);
					CHAR szText[500];
					wsprintf(szText, "Gra sie rozpoczela");
					SetWindowText(hwndStatic, szText);
					for (int i = 0; i < 9; i++) {
						HWND hwndButton = GetDlgItem(hwndDIg, IDC_BUTTON2 + i);
						CHAR szText1[500];
						wsprintf(szText1, "");
						SetWindowText(hwndButton, szText1);
					}
					HWND hwndButton1 = GetDlgItem(hwndDIg, IDC_BUTTON1);
					CHAR szText2[500];
					wsprintf(szText2, "Stop");
					SetWindowText(hwndButton1, szText2);
				}
				else
				{
					isGameOn = false;
					HWND hwndStatic = GetDlgItem(hwndDIg, IDC_STATIC);
					CHAR szText[500];
					wsprintf(szText, "Gra sie zakoczyla");
					SetWindowText(hwndStatic, szText);
					HWND hwndButton1 = GetDlgItem(hwndDIg, IDC_BUTTON1);
					CHAR szText2[500];
					wsprintf(szText2, "Start");
					SetWindowText(hwndButton1, szText2);	
				}
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