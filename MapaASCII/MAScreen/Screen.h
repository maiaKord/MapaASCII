#pragma once
#include <Windows.h>
#include "SettingsViewPort.h"
#include "Camera.h"

// This class manage the drawn space

static const wchar_t appName[] = L"MapaASCII";

class Screen
{
	SettingsViewPort _settingsVP;
	Camera _camera;

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
	Camera& getCamera();
	char* getPixels();
};
