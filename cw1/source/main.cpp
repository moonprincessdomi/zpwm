#include<string>
//#include <iostream>
#include <Windows.h>

void bigger_smaller(int a, int b) {
	int c = (a + b + 1) / 2;

	char txt[100];

	if (a == b) {
		sprintf_s(txt, "Znaleziona liczba to  %d", c);
		MessageBox(0, txt, "Wygralem!", MB_OK);
		return;
	}
	//std::string txt = "Czy twoja liczba jest wieksza badz rowna " + c;
	sprintf_s(txt, "Czy twoja liczba jest wieksza badz rowna %d", c);
	int odp = MessageBox(0, txt,"I tak wygram", MB_YESNO);

	if (odp == IDYES) {
		bigger_smaller(c, b);
	}
	else {
		bigger_smaller(a, c - 1);
	}
	return;
}

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
	int min = 0;
	int max = 40;
	bigger_smaller(min, max);
	return 0;
}