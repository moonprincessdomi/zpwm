#include<Windows.h>
#include<stdio.h>
#include "res.h"
#include <math.h>
#define ID_TIMER_REDRAW 10
HANDLE hFile;
BYTE* ImageBuferY ;
BYTE* ImageBuferU ;
BYTE* ImageBuferV;
BYTE* ImageBuferRGBA;
__int64 iEnd, iStart;
__int64 max=0;


INT_PTR CALLBACK DialogProc(HWND hwndDig, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg)
  {
  case WM_INITDIALOG:
  {
    hFile = CreateFile("..//res//claire.cif", GENERIC_READ, 0, (LPSECURITY_ATTRIBUTES)0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, (HANDLE)NULL); // otwieramy istniejacy plik
    ImageBuferY = (BYTE*)malloc(352 * 288);//luma
    ImageBuferU = (BYTE*)malloc(352 * 288 >> 2);//chroma
    ImageBuferV = (BYTE*)malloc(352 * 288 >> 2);//chroma
    ImageBuferRGBA = (BYTE*)malloc(352 * 288 << 2);

    return FALSE;
  }

  case WM_COMMAND:
    switch (HIWORD(wParam))
    {
    case BN_CLICKED:
      switch (LOWORD(wParam))
      {
      case IDC_BUTTON2:

        return TRUE;
      }
      return FALSE;
    }
  case WM_CLOSE:

    free(ImageBuferU);//zwalniamy buffory 
    free(ImageBuferY);
    free(ImageBuferV);
    free(ImageBuferRGBA);
    CloseHandle(hFile);// zamykamy plik t¹ funkcj¹, zamyka ona plik z uchwytu
    DestroyWindow(hwndDig);//zniszczenie okienka
    PostQuitMessage(0);//umieszczenie w petli komunikatow polecenia zakonczenia aplikacji 
    return TRUE;
  case WM_PAINT:
  {
    HDC hDc = GetDC(hwndDig);
    HDC hdcMemDc;

    hdcMemDc = CreateCompatibleDC(hDc);
    HBITMAP hBmp;
    hBmp = CreateCompatibleBitmap(hDc, 352, 288);
    SelectObject(hdcMemDc, hBmp);

    //wczytanie obrazka
    BITMAPINFOHEADER bi;
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = 352;
    bi.biHeight = 288;//mozna -288 wtedy odwrotnie 
    bi.biPlanes = 1;
    bi.biBitCount = 24;//g³êbia 8bitów/kana³ *3kana³y
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 101376;//352 * 288;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    SetDIBits(hdcMemDc, hBmp, 0, 288, ImageBuferRGBA, (BITMAPINFO*)&bi, DIB_RGB_COLORS);

    BitBlt(hDc, 0, 0, 352, 288, hdcMemDc, 0, 0, SRCCOPY);

    static int x = 10;
	static int y = 10;
    char text[255];
	wsprintf(text, "%d [us]", iEnd - iStart);
    TextOut(hDc, x, y, text, strlen(text));
    // = x + 0;
    ReleaseDC(hwndDig, hDc);
    return FALSE;
  }
  case WM_TIMER:
  {
    switch (wParam)
    {
    case ID_TIMER_REDRAW:

      if (!hFile)break;//sprawdzamy czy plik otwarty
      DWORD ret;

	  int x1 = 352 * 288;

      ReadFile(hFile, ImageBuferY, x1, &ret, NULL);
      ReadFile(hFile, ImageBuferU, x1/4, &ret, NULL);
      ReadFile(hFile, ImageBuferV, x1/4, &ret, NULL);

      //konwersja z YUV na RGB

      //iStart = GetTickCount();
      QueryPerformanceCounter((LARGE_INTEGER*)&iStart);

      for (int y = 0; y < 288; ++y)
      {
        for (int x = 0; x < 352; ++x)
        {
		 //pobranie probek
			int x2 = y / 2 * 352 / 2 + x / 2;
			int Y = ImageBuferY[(y * 352) + x];
			int U = ImageBuferU[x2] - 128;
			int V = ImageBuferV[x2] - 128;   //odczytanie wartosci probek

			int r = ((256 * static_cast<int> (1.40200))*V + 256 * Y) / 256;
			int g = ((256 * static_cast<int> (-0.34414))*U + (256 * -0.71414)*V + 256 * Y) / 256;
			int b = ((256 * static_cast<int> (1.77200))*U + 256 * Y) / 256;

			auto nr = 3 * ((287 - y) * 352 + x);
			ImageBuferRGBA[nr + 0] = b;
			ImageBuferRGBA[nr + 1] = g;
			ImageBuferRGBA[nr + 2] = r;
        }
      }
      QueryPerformanceCounter((LARGE_INTEGER*)&iEnd);
      if ((iEnd - iStart) > max) max = (iEnd - iStart);
      RECT rc;
      GetClientRect(hwndDig, &rc);//pobieramy okienko
      InvalidateRect(hwndDig, NULL, false);//przygotuj do odrysowania
      RedrawWindow(hwndDig, &rc, NULL, RDW_ERASE);//odrysuj okienko

      return FALSE;
    }

    return FALSE;
  }
  }
  return FALSE;
}


int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevinstance, PSTR szCmdLIne, int iCmdShow)
{
  HWND hwndMainWindow = CreateDialog(hinstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, DialogProc);
  ShowWindow(hwndMainWindow, iCmdShow);

  SetTimer(hwndMainWindow, ID_TIMER_REDRAW, 100, NULL); // co 200 ms zamiast null mozna funkcje

  MSG msg = {};

  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return 0;
}