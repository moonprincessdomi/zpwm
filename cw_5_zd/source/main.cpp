#include <string>
#include <Windows.h>
#include "res.h"
#include <stdio.h>

bool isGameOn = false;
bool isFirstPlayerTurn = true;
bool isSecondPlayerTurn = false;
int iter = 0;
char tabl[9];

HBITMAP hBitMapX;
//hBitMapX = (HBITMAP)LoadImage(NULL, "F:\EiT\sem6\zpwm\dobre\cw_4\resources\o.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

HBITMAP hBitMapO;
//hBitMapO = (HBITMAP)LoadImage(NULL, "F:\EiT\sem6\zpwm\dobre\cw_4\resources\xb.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

HBITMAP hBitMapGameBoard;
//hBitMapGameBoard = (HBITMAP)LoadImage(NULL, "F:\EiT\sem6\zpwm\dobre\cw_4\resources\siatka.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

HBITMAP hBitMapStart;

HINSTANCE hInst;

LRESULT CALLBACK ButtonWndProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_PAINT:
		//paint area
	{
		HDC hdc = GetDC(hwnd);
		HDC hdcBitmap = CreateCompatibleDC(hdc);
		SelectObject(hdcBitmap, hBitMapStart);
		BitBlt(hdc, 500, 200, 200, 100, hdcBitmap, 0, 0, SRCCOPY);
		DeleteDC(hdcBitmap);
		return 0;
	}
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

void DrawBoard(HDC hdc)
{
	HDC hDCBitmap = CreateCompatibleDC(hdc);
	SelectObject(hDCBitmap, hBitMapGameBoard);
	BitBlt(hdc, 0, 0, 500, 321, hDCBitmap, 0, 0, SRCCOPY);
	DeleteDC(hDCBitmap);
}

void DrawX(HDC hdc, int x, int y)
{
	HDC hDCBitmap = CreateCompatibleDC(hdc);
	SelectObject(hDCBitmap, hBitMapX);
	BitBlt(hdc, x, y, 100, 100, hDCBitmap, 0, 0, SRCCOPY);
	DeleteDC(hDCBitmap);
}

void DrawO(HDC hdc, int x, int y)
{
	HDC hDCBitmap = CreateCompatibleDC(hdc);
	SelectObject(hDCBitmap, hBitMapO);
	BitBlt(hdc, x, y, 100, 100, hDCBitmap, 0, 0, SRCCOPY);
	DeleteDC(hDCBitmap);
}

bool wygrana(HWND hwndDig)
{
	for (int i = 0; i <= 6; i += 3) {
		if (
			((tabl[i] == tabl[i + 1] && tabl[i + 2] == tabl[i + 1]) && (tabl[i] == 'X' || tabl[i] == 'O'))
			||
			(((tabl[0] == tabl[4] && tabl[4] == tabl[8]) || (tabl[2] == tabl[4] && tabl[4] == tabl[6])) && (tabl[4] == 'X' || tabl[4] == 'O'))
			||
			((((tabl[0] == tabl[3] && tabl[3] == tabl[6]) && (tabl[3] == 'X' || tabl[3] == 'O')) || ((tabl[1] == tabl[4] && tabl[4] == tabl[7]) && (tabl[4] == 'X' || tabl[4] == 'O')) || ((tabl[2] == tabl[5] && tabl[5] == tabl[8]) && (tabl[5] == 'X' || tabl[5] == 'O'))))
			)
		{
			/*if (isFirstPlayerTurn == true) MessageBox(0, "Wygral X", "Wygral X", MB_OK);
			else MessageBox(0, "Wygral O", "Wygral O", MB_OK);
			for (int j = 0; j < 9; j++) {
				HWND hwndButton = GetDlgItem(hwndDIg, IDC_BUTTON2 + j);
				CHAR szText1[500];
				wsprintf(szText1, "");
				SetWindowText(hwndButton, szText1);
			}
			for (int z = 0; z < 9; z++)
			{
				tabl[z] = ' ';
			}
			isFirstPlayerTurn = false;
			break;*/
		}
	}
		return false;
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
				/*HWND hwndButton = (HWND)lParam;

				for (int i = 0; i <= 10; i++) 
				{
					HWND hwndButtonx = GetDlgItem(hwndDIg, IDC_BUTTON2 + i);
					if (hwndButtonx == hwndButton)
					{
						break;
					}
					iter++;
				}

				CHAR szText[500];
				int TextLenght = 1;
				if (GetWindowTextLength(hwndButton) == 0) {
					if (isFirstPlayerTurn == true)
					{
						wsprintf(szText, "X");
						tabl[iter] = 'X';
					}
					else
					{
						wsprintf(szText, "O");
						tabl[iter] = 'O';
					}

					SetWindowText(hwndButton, szText);

					for (int i = 0; i <= 6; i += 3) {
						if (
							((tabl[i] == tabl[i + 1] && tabl[i + 2] == tabl[i + 1]) && (tabl[i] == 'X' || tabl[i] == 'O'))
							||
							(((tabl[0] == tabl[4] && tabl[4] == tabl[8]) || (tabl[2] == tabl[4] && tabl[4] == tabl[6])) && (tabl[4] == 'X' || tabl[4] == 'O'))
							||
							//((i == 0 || i == 1 || i == 2 ) && (tabl[i] == tabl[i + 3] && tabl[i+3] == tabl[i + 6]) && (tabl[i] == 'X' || tabl[i] == 'O'))
							((((tabl[0] == tabl[3] && tabl[3] == tabl [6]) && (tabl[3] == 'X' || tabl[3] == 'O')) || ((tabl[1] == tabl[4] && tabl[4] == tabl[7]) && (tabl[4] == 'X' || tabl[4] == 'O'))|| ((tabl[2] == tabl[5] && tabl[5] == tabl[8]) && (tabl[5] == 'X' || tabl[5] == 'O'))))
							) 
						{
							if (isFirstPlayerTurn == true) MessageBox(0, "Wygral X", "Wygral X", MB_OK);
							else MessageBox(0, "Wygral O", "Wygral O", MB_OK);
							for (int j = 0; j < 9; j++) {
								HWND hwndButton = GetDlgItem(hwndDIg, IDC_BUTTON2 + j);
								CHAR szText1[500];
								wsprintf(szText1, "");
								SetWindowText(hwndButton, szText1);
							}
							for (int z = 0; z < 9; z++)
							{
								tabl[z] = ' ';
							}
							isFirstPlayerTurn = false;
							break;
						}
					}
					int i = 0;
					while(i < 9)
					{
						if (tabl[i] == ' ')
						{
							break;
						}
						else
						{
							i++;
						}
						if (i == 8) {
							MessageBox(0, "REMIS", "REMIS", MB_OK);
							for (int j = 0; j < 9; j++) {
								HWND hwndButton = GetDlgItem(hwndDIg, IDC_BUTTON2 + j);
								CHAR szText1[500];
								wsprintf(szText1, "");
								SetWindowText(hwndButton, szText1);
							}
							for (int z = 0; z < 9; z++)
							{
								tabl[z] = ' ';
							}
							isFirstPlayerTurn = false;
							break;
						}
					}
					iter = 0;
					isFirstPlayerTurn = !isFirstPlayerTurn;
				}*/
				return TRUE;
			}
			return FALSE;
			case IDC_BUTTON1:
				/*if (isGameOn == false)
				{
					for (int i = 0; i < 9; i++)
					{
						tabl[i] = ' ';
					}
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
					for (int i = 0; i < 9; i++)
					{
						tabl[i] = ' ';
					}
					isGameOn = false;
					HWND hwndStatic = GetDlgItem(hwndDIg, IDC_STATIC);
					CHAR szText[500];
					wsprintf(szText, "Gra sie zakoczyla");
					SetWindowText(hwndStatic, szText);
					HWND hwndButton1 = GetDlgItem(hwndDIg, IDC_BUTTON1);
					CHAR szText2[500];
					wsprintf(szText2, "Start");
					SetWindowText(hwndButton1, szText2);	
				}*/
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

	int odp;

	for (int i = 0; i < 9; i++)
	{
		tabl[i] = ' ';
	}

	do
	{
		HWND hwndMainWindow = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, DialogProc);
		ShowWindow(hwndMainWindow, iCmdShow);

		MSG msg = {};
		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		odp = MessageBox(0, "Jeszcze raz ?", "Zagraj ponownie." , MB_YESNO);
	} while (odp == IDYES);


	return 0;
}

