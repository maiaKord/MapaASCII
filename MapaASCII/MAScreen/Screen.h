#pragma once
#include <Windows.h>
#include "SettingsViewPort.h"

// This class manage the drawn space

class Screen
{
	SettingsViewPort _settingsVP;
	SVector2D _camera = { 0,0 };

protected:
	int _backBufferWidth = 0;
	int _backBufferHeight = 0;
	char* _pixels = nullptr;

public:
	Screen();
	~Screen();

	virtual void print() = 0;
	virtual void printText(int x, int y, const char* text) = 0;

	virtual void clear() = 0;

	// encapsulamiento
	int getBackBufferWidth();
	int getBackBufferHeight();
	SVector2D& getCamera();
	virtual char* getPixels();
};
