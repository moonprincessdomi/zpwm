#include <string>
#include <Windows.h>
#include "res.h"
#include<string>
#pragma comment(lib, "winmm.lib")
#include <math.h>
#include<iostream>
#define PI 3.141592

bool isGameOn = false;
bool isFirstPlayerTurn = true;
bool isSecondPlayerTurn = false;
int iter = 0;
char tabl[9];

void graj() {
	//DZWIEK
	int min = 1;
	int max = 40;

	WAVEFORMATEX pcmWaveFormat;

	pcmWaveFormat.wFormatTag = WAVE_FORMAT_PCM;
	pcmWaveFormat.nChannels = 1;
	pcmWaveFormat.nSamplesPerSec = 44100L;
	pcmWaveFormat.wBitsPerSample = 8;
	pcmWaveFormat.nAvgBytesPerSec = pcmWaveFormat.nSamplesPerSec*pcmWaveFormat.wBitsPerSample / 8;
	pcmWaveFormat.nBlockAlign = 1;
	pcmWaveFormat.cbSize = 0;

	MMRESULT mmResult;
	HWAVEOUT hwo = 0;
	UINT devId;

	for (devId = 0; devId < waveOutGetNumDevs(); devId++)
	{
		mmResult = waveOutOpen(&hwo, devId, &pcmWaveFormat, 0, 0, CALLBACK_NULL);

		if (mmResult == MMSYSERR_NOERROR)break;
	}

	if (mmResult != MMSYSERR_NOERROR)
	{
		MessageBox(0, TEXT("Nie znaleziono karty"), TEXT("ERROR"), MB_OK);
		//return mmResult;
	}

	BYTE* pBufferForAudio = new BYTE[1 * pcmWaveFormat.nAvgBytesPerSec];

	float f = 1000;

	for (int i = 0; i < 1 * pcmWaveFormat.nAvgBytesPerSec; i++)
	{
		float t = i / (float)pcmWaveFormat.nSamplesPerSec;
		pBufferForAudio[i] = 128 * sin(2 * PI*f*t) + 128;
	}

	WAVEHDR whdr;
	ZeroMemory(&whdr, sizeof(WAVEHDR));
	whdr.lpData = (LPSTR)pBufferForAudio;
	whdr.dwBufferLength = 0.5 * pcmWaveFormat.nAvgBytesPerSec;

	float fC = 261.626;//do
	float fD = 293.7;//re
	float fE = 329.628;//mi
	float fF = 349.228;//fa
	float fG = 391.9;//sol
	float fA = 444.00;//la
	float fH = 493.880;//si
	float fc = 523.2;//do

	int i = 0;

	std::string p = "EF";
	std::string piosenka = p;
	std::string pdlugoscd = "85";
	std::string dlugoscdzwiekow = pdlugoscd;

	if (piosenka.length() != dlugoscdzwiekow.length())return;

	for (int j = 0; j < piosenka.length(); j++)
	{
		if (piosenka[j] == 'C')
		{
			for (int i = 0; i <(int(dlugoscdzwiekow[j]) - '0')*0.1* pcmWaveFormat.nAvgBytesPerSec; i++)
			{
				float t = i / (float)pcmWaveFormat.nSamplesPerSec;
				f = fC;
				pBufferForAudio[i] = 128 * sin(2 * PI*f*t) + 128;
			}
			mmResult = waveOutPrepareHeader(hwo, &whdr, sizeof(WAVEHDR));
			mmResult = waveOutWrite(hwo, &whdr, sizeof(WAVEHDR));

			while ((whdr.dwFlags & WHDR_DONE) != WHDR_DONE) Sleep(100);
		}
		if (piosenka[j] == 'D')
		{
			for (int i = 0; i <(int(dlugoscdzwiekow[j]) - '0')*0.1* pcmWaveFormat.nAvgBytesPerSec; i++)
			{
				float t = i / (float)pcmWaveFormat.nSamplesPerSec;
				f = fD;
				pBufferForAudio[i] = 128 * sin(2 * PI*f*t) + 128;
			}
			mmResult = waveOutPrepareHeader(hwo, &whdr, sizeof(WAVEHDR));
			mmResult = waveOutWrite(hwo, &whdr, sizeof(WAVEHDR));

			while ((whdr.dwFlags & WHDR_DONE) != WHDR_DONE) Sleep(100);
		}
		if (piosenka[j] == 'E')
		{
			for (int i = 0; i <(int(dlugoscdzwiekow[j]) - '0')*0.1* pcmWaveFormat.nAvgBytesPerSec; i++)
			{
				float t = i / (float)pcmWaveFormat.nSamplesPerSec;
				f = fE;
				pBufferForAudio[i] = 128 * sin(2 * PI*f*t) + 128;
			}
			mmResult = waveOutPrepareHeader(hwo, &whdr, sizeof(WAVEHDR));
			mmResult = waveOutWrite(hwo, &whdr, sizeof(WAVEHDR));

			while ((whdr.dwFlags & WHDR_DONE) != WHDR_DONE) Sleep(100);
		}
		if (piosenka[j] == 'F')
		{
			for (int i = 0; i < (int(dlugoscdzwiekow[j]) - '0')*0.1* pcmWaveFormat.nAvgBytesPerSec; i++)
			{
				float t = i / (float)pcmWaveFormat.nSamplesPerSec;
				f = fF;
				pBufferForAudio[i] = 128 * sin(2 * PI*f*t) + 128;
			}
			mmResult = waveOutPrepareHeader(hwo, &whdr, sizeof(WAVEHDR));
			mmResult = waveOutWrite(hwo, &whdr, sizeof(WAVEHDR));

			while ((whdr.dwFlags & WHDR_DONE) != WHDR_DONE) Sleep(100);
		}
		if (piosenka[j] == 'G')
		{
			for (int i = 0; i <(int(dlugoscdzwiekow[j]) - '0')*0.1* pcmWaveFormat.nAvgBytesPerSec; i++)
			{
				float t = i / (float)pcmWaveFormat.nSamplesPerSec;
				f = fG;
				pBufferForAudio[i] = 128 * sin(2 * PI*f*t) + 128;
			}
			mmResult = waveOutPrepareHeader(hwo, &whdr, sizeof(WAVEHDR));
			mmResult = waveOutWrite(hwo, &whdr, sizeof(WAVEHDR));

			while ((whdr.dwFlags & WHDR_DONE) != WHDR_DONE) Sleep(100);
		}
		if (piosenka[j] == 'A')
		{
			for (int i = 0; i < (int(dlugoscdzwiekow[j]) - '0')*0.1* pcmWaveFormat.nAvgBytesPerSec; i++)
			{
				float t = i / (float)pcmWaveFormat.nSamplesPerSec;
				f = fA;
				pBufferForAudio[i] = 128 * sin(2 * PI*f*t) + 128;
			}
			mmResult = waveOutPrepareHeader(hwo, &whdr, sizeof(WAVEHDR));
			mmResult = waveOutWrite(hwo, &whdr, sizeof(WAVEHDR));

			while ((whdr.dwFlags & WHDR_DONE) != WHDR_DONE) Sleep(100);
		}
		if (piosenka[j] == 'H')
		{
			for (int i = 0; i < (int(dlugoscdzwiekow[j]) - '0')*0.1* pcmWaveFormat.nAvgBytesPerSec; i++)
			{
				float t = i / (float)pcmWaveFormat.nSamplesPerSec;
				f = fH;
				pBufferForAudio[i] = 128 * sin(2 * PI*f*t) + 128;
			}
			mmResult = waveOutPrepareHeader(hwo, &whdr, sizeof(WAVEHDR));
			mmResult = waveOutWrite(hwo, &whdr, sizeof(WAVEHDR));

			while ((whdr.dwFlags & WHDR_DONE) != WHDR_DONE) Sleep(100);
		}
		if (piosenka[j] == 'c')
		{
			for (int i = 0; i < (int(dlugoscdzwiekow[j]) - '0')*0.1* pcmWaveFormat.nAvgBytesPerSec; i++)
			{
				float t = i / (float)pcmWaveFormat.nSamplesPerSec;
				f = fc;
				pBufferForAudio[i] = 128 * sin(2 * PI*f*t) + 128;
			}
			mmResult = waveOutPrepareHeader(hwo, &whdr, sizeof(WAVEHDR));
			mmResult = waveOutWrite(hwo, &whdr, sizeof(WAVEHDR));

			while ((whdr.dwFlags & WHDR_DONE) != WHDR_DONE) Sleep(100);
		}
		if (piosenka[j] == ' ')
		{
			for (int i = 0; i < (int(dlugoscdzwiekow[j]) - '0')*0.1* pcmWaveFormat.nAvgBytesPerSec; i++)
			{
				float t = i / (float)pcmWaveFormat.nSamplesPerSec;
				f = fc;
				pBufferForAudio[i] = 128 * sin(2 * PI*f*t) + 128;
			}
			mmResult = waveOutPrepareHeader(hwo, &whdr, sizeof(WAVEHDR));
			mmResult = waveOutWrite(hwo, &whdr, sizeof(WAVEHDR));

			while ((whdr.dwFlags & WHDR_DONE) != WHDR_DONE) Sleep(100);
		}
	}
	mmResult = waveOutClose(hwo);
	delete[] pBufferForAudio;
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
				graj();
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

	//GRA

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
