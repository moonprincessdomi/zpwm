#include<string>
#include <Windows.h>
#pragma comment(lib, "winmm.lib")
#include <math.h>
#include<iostream>
#define PI 3.141592

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
	int min = 1;
	int max = 40;

	//HWND hwnd = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, DialogProc);
	//ShowWindow(hwnd, iCmdShow);

	//MessageBox(0, "Wybierz liczbê od 1-40", "Witaj!", MB_OK);
	WAVEFORMATEX pcmWaveFormat;

	pcmWaveFormat.wFormatTag = WAVE_FORMAT_PCM;
	pcmWaveFormat.nChannels = 1;
	pcmWaveFormat.nSamplesPerSec = 44100L;
	pcmWaveFormat.wBitsPerSample = 8;
	pcmWaveFormat.nAvgBytesPerSec = pcmWaveFormat.nSamplesPerSec*pcmWaveFormat.wBitsPerSample / 8;
	pcmWaveFormat.nBlockAlign = 1;
	pcmWaveFormat.cbSize = 0;

	MMRESULT mmResult;
	HWAVEOUT hwo=0;
	UINT devId;

	for (devId = 0; devId < waveOutGetNumDevs();devId++)
	{
		mmResult = waveOutOpen(&hwo, devId, &pcmWaveFormat, 0, 0, CALLBACK_NULL);

		if (mmResult == MMSYSERR_NOERROR)break;
	}

	if (mmResult != MMSYSERR_NOERROR)
	{
		MessageBox(0, TEXT("Nie znaleziono karty"),TEXT("ERROR"),MB_OK);
		return mmResult;
	}

	BYTE* pBufferForAudio = new BYTE[1 * pcmWaveFormat.nAvgBytesPerSec];

	float f = 1000;

	for (int i = 0; i < 1 * pcmWaveFormat.nAvgBytesPerSec; i++)
	{
		float t = i / (float)pcmWaveFormat.nSamplesPerSec;
		pBufferForAudio[i] =128* sin(2*PI*f*t) + 128;
	}

	WAVEHDR whdr;
	ZeroMemory(&whdr, sizeof(WAVEHDR));
	whdr.lpData = (LPSTR)pBufferForAudio;
	whdr.dwBufferLength = 0.5 * pcmWaveFormat.nAvgBytesPerSec;

	//mmResult = waveOutPrepareHeader(hwo, &whdr, sizeof(WAVEHDR));
	//mmResult = waveOutWrite(hwo, &whdr, sizeof(WAVEHDR));

	//while ((whdr.dwFlags & WHDR_DONE) != WHDR_DONE) Sleep(100);

	//mmResult = waveOutUnprepareHeader(hwo, &whdr, sizeof(WAVEHDR));
	
	//bigger_smaller(min, max);
	/*
	float f1 = 440;
	float f2 = 880;

	for (int i = 0; i < 1 * pcmWaveFormat.nAvgBytesPerSec; i++)
	{
		float t = i / (float)pcmWaveFormat.nSamplesPerSec;
		f = f1 + (f2 - f1)*t;
		pBufferForAudio[i] = 128 * sin(2 *PI*f*t) + 128;
	}

	mmResult = waveOutPrepareHeader(hwo, &whdr, sizeof(WAVEHDR));
	mmResult = waveOutWrite(hwo, &whdr, sizeof(WAVEHDR));

	while ((whdr.dwFlags & WHDR_DONE) != WHDR_DONE) Sleep(100);

	mmResult = waveOutUnprepareHeader(hwo, &whdr, sizeof(WAVEHDR));
	*/
	//MELODIA

	float fC = 261.626;//do
	float fD = 293.7;//re
	float fE = 329.628;//mi
	float fF = 349.228;//fa
	float fG = 391.9;//sol
	float fA = 444.00;//la
	float fH = 493.880;//si
	float fc = 523.2;//do


	int i = 0;
	
	std::string lulajzejezuniudzwieki = "EEEGFEFDDFAGEEEGFEFDGFFEGGcHAAGFFAAGEEEGFEFDGFFE";
	std::string hallelujah = "EGGGGAAA EGGGGGAA AGAAAAAG EFGGEGGG GAAH GCCACCD CDDDDEEEDDCC EGAAAGEE EGAAAGEFEDCC";
	std::string piosenka = hallelujah;
	std::string lulaljzejeziuniudlugoscd = "8885555548885555548885555554888855554555548885555488855555555545555555548855555555";
	std::string hallelujahdlugoscd = "88866668886666668886666668886666668886666668886666668886666668886666668886666666666";
	std::string dlugoscdzwiekow = hallelujahdlugoscd;

	if (piosenka.length() != dlugoscdzwiekow.length())return 0;

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
			for (int i = 0; i <(int(dlugoscdzwiekow[j])-'0')*0.1* pcmWaveFormat.nAvgBytesPerSec; i++)
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
	return 0;
}