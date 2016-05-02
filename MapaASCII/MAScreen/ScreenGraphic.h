#pragma once
#include <windows.h>
#include "Screen.h"

static const wchar_t sClassName[] = L"MapaASCII";
static HINSTANCE zhInstance = NULL;

class ScreenGraphic : public Screen
{
	WNDCLASSEX WndClass;
	HWND hwnd;
	MSG Msg;
	
public:

	ScreenGraphic();

	int init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);

	void update();
	
	void print();
	void printText(int x, int y, const char* text);

	void clear();
};