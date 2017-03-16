#include<string>
#include <Windows.h>

void bigger_smaller(int a, int b) {
	int c = (a + b) / 2;

	char txt[100];

	if (a == b) {
		sprintf_s(txt, "Znaleziona liczba to  %d", c);
		MessageBox(0, txt, "Wygralem!", MB_OK);
		return;
	}

	sprintf_s(txt, "Czy twoja liczba jest wieksza %d", c);
	int odp = MessageBox(0, txt,"I tak wygram", MB_YESNO);

	if (odp == IDYES) {
		bigger_smaller(c + 1, b);
	}
	else {
		bigger_smaller(a, c);
	}
	return;
}

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
	int min = 1;
	int max = 40;
	MessageBox(0, "Wybierz liczbê od 1-40", "Witaj!", MB_OK);
	bigger_smaller(min, max);
	return 0;
}