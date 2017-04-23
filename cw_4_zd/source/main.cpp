#include <string>
#include <Windows.h>
#include "res.h"

bool isGameOn = false;
bool isFirstPlayerTurn = true;
bool isSecondPlayerTurn = false;
int iter = 0;
char tabl[9];
char gracz;

bool win(char tab[]) {
	for (int i = 0; i <= 6; i += 3) {
		if (
			((tab[i] == tab[i + 1] && tab[i + 2] == tab[i + 1]) && (tab[i] == 'X' || tab[i] == 'O'))
			||
			(((tab[0] == tab[4] && tab[4] == tab[8]) || (tab[2] == tab[4] && tab[4] == tab[6])) && (tab[4] == 'X' || tab[4] == 'O'))
			||
			((((tab[0] == tab[3] && tab[3] == tab[6]) && (tab[3] == 'X' || tab[3] == 'O')) || ((tab[1] == tab[4] && tab[4] == tab[7]) && (tab[4] == 'X' || tab[4] == 'O')) || ((tab[2] == tab[5] && tab[5] == tab[8]) && (tab[5] == 'X' || tab[5] == 'O'))))
			)
		{
			return true;
		}
	}
	return false;
}

bool remis(char tab[]) {
	int i = 0;
	while (i < 9)
	{
		if (tab[i] == ' ')
		{
			break;
		}
		else
		{
			i++;
		}
		if (i == 8) {
			return true;
		}
	}
	return false;
}

int minmax(char gracz, char tab[])
{
	int m, mmx;
	char tablc[9];
	for (int i = 0; i < 9; i++) {
		tablc[i] = tab[i];
	}

	if (win(tablc)) return (gracz == 'O') ? 1 : -1;
	if (remis(tablc)) return 0;
	gracz = (gracz == 'O') ? 'X' : 'O';
	mmx = (gracz == 'X') ? 10 : -10;

	for (int i = 0; i < 9; i++)
		if (tablc[i] == ' ')
		{
			tablc[i] = gracz;
			m = minmax(gracz, tablc);
			tablc[i] = ' ';
			if (((gracz == 'X') && (m < mmx)) || ((gracz == 'O') && (m > mmx))) mmx = m;
		}
	return mmx;
}



int computer()
{
	int ruch, m, mmx;
	mmx = -10;
	for (int i = 0; i < 9; i++)
	{
		if (tabl[i] == ' ')
		{
			//tabl[i] = 'X';
			char tablc[9];
			for (int j = 0; j < 9; j++) {
				tablc[j] = tabl[j];
			}
			tablc[i] = 'O';
			m = minmax('O', tablc);
			//tabl[i] = ' ';
			if (m > mmx)
			{
				mmx = m; ruch = i;
			}
		}
	}
	return ruch;
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
				HWND hwndButton = (HWND)lParam;

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
				if (GetWindowTextLength(hwndButton) == 0) 
					{
						if (isFirstPlayerTurn == true)
						{
							wsprintf(szText, "X");
							tabl[iter] = 'X';
							gracz = 'X';
							SetWindowText(hwndButton, szText);
						}
						
						bool w1=win(tabl);
						bool r1=remis(tabl);

						if (w1 || r1) {
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
							if(w1)MessageBox(0, "Wygral X", "Wygral X", MB_OK);
							if(r1)MessageBox(0, "REMIS", "REMIS", MB_OK);
						}

						//isFirstPlayerTurn = !isFirstPlayerTurn;

						int ruch = computer();
						tabl[ruch] = 'O';
						HWND hwndButtoncomp = GetDlgItem(hwndDIg, IDC_BUTTON2 + ruch);
						char szTextcopm[10];
						wsprintf(szTextcopm, "O");
						SetWindowText(hwndButtoncomp, szTextcopm);

						bool w2 = win(tabl);
						bool r2 = remis(tabl);

						if (w2 || r2) {
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
							if(w1)MessageBox(0, "Wygral O", "Wygral O", MB_OK);
							if(r2)MessageBox(0, "REMIS", "REMIS", MB_OK);
						}
						iter = 0;

						//isFirstPlayerTurn = !isFirstPlayerTurn;
					}
					return TRUE;
				}
			return FALSE;
			case IDC_BUTTON1:
				if (isGameOn == false)
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