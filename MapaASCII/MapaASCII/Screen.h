#pragma once
#include <Windows.h>

// This class manage the drawn space

class Screen
{
	int _backBufferWidth = 0;
	int _backBufferHeight = 0;
	char* _pixels = nullptr;
	HANDLE _hConsoleOut = nullptr;

public:
	Screen(int screenWidth, int screenHeight);
	~Screen();

	void init();
	void print();

	// encapsulamiento

	int getBackBufferWidth();
	int getBackBufferHeight();
	char* getPixels();
};
