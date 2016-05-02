#pragma once
#include "Screen.h"

class ScreenConsole : public Screen
{
	HANDLE _hConsoleOut = nullptr;

public:
	ScreenConsole();
	~ScreenConsole();

	void init();

	void print();
	void printText(int x, int y, const char* text);

	void clear();
};
