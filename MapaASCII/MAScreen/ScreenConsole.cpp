#include "ScreenConsole.h"

ScreenConsole::ScreenConsole()
{
	AllocConsole();
	AttachConsole(GetCurrentProcessId());

	FILE* fp = stdout;
	freopen_s(&fp, "CON", "w", stdout);
	SetConsoleTitle(appName);

	_hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
}

ScreenConsole::~ScreenConsole()
{
}

void ScreenConsole::init()
{
	CONSOLE_SCREEN_BUFFER_INFOEX csbiInfo = {};
	GetConsoleScreenBufferInfoEx(_hConsoleOut, &csbiInfo);

	//csbiInfo.dwCursorPosition.Y = csbiInfo.dwSize.Y-1;
	csbiInfo.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);

	//csbiInfo.wAttributes
	csbiInfo.dwSize.X = _backBufferWidth;
	csbiInfo.dwSize.Y = _backBufferHeight;
	csbiInfo.dwMaximumWindowSize.X = _backBufferWidth;
	csbiInfo.dwMaximumWindowSize.Y = _backBufferHeight;
	csbiInfo.bFullscreenSupported = TRUE;
	csbiInfo.srWindow.Top = 100;
	csbiInfo.srWindow.Left = 100;
	csbiInfo.srWindow.Right = 800;
	csbiInfo.srWindow.Bottom = 600;
	csbiInfo.ColorTable[0] = 0x00000000;
	csbiInfo.ColorTable[1] = 0x00FFFFFF;
	csbiInfo.ColorTable[2] = 0x00FF0000;
	csbiInfo.ColorTable[3] = 0x0000FF00;
	csbiInfo.ColorTable[4] = 0x000000FF;
	csbiInfo.ColorTable[5] = 0x00FFFFFF;//0x0000FFFF;
	csbiInfo.ColorTable[6] = 0x00FF00FF;
	csbiInfo.ColorTable[7] = 0x00FFFF00;
	csbiInfo.ColorTable[8] = 0x00000FFF;
	csbiInfo.ColorTable[9] = 0x0000FFF0;
	csbiInfo.ColorTable[10] = 0x000FFF00;
	csbiInfo.ColorTable[11] = 0x00FFF000;
	csbiInfo.ColorTable[12] = 0x00FF000F;
	csbiInfo.ColorTable[13] = 0x00F000FF;
	csbiInfo.ColorTable[14] = 0x0000F0F0;
	csbiInfo.ColorTable[15] = 0x00FFFFFF;//0x00F000F0;
	csbiInfo.wAttributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;

	SetConsoleScreenBufferInfoEx(_hConsoleOut, &csbiInfo);
}

void ScreenConsole::print()
{
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo = {};
	GetConsoleScreenBufferInfo(_hConsoleOut, &csbiInfo);
	COORD Coords = { 0, csbiInfo.dwSize.Y - (SHORT)_backBufferHeight };
	char* myLine = 0;
	DWORD dummy = 0;

	WriteConsoleOutputCharacterA(_hConsoleOut, _pixels, _backBufferWidth*_backBufferHeight, Coords, &dummy);
}

void ScreenConsole::printText(int x, int z, const char* text)
{
	int maxLen = strlen(text);
	int posInit = z * _backBufferWidth + x;

	if ((posInit + maxLen) > (_backBufferWidth * _backBufferHeight))
		maxLen = (_backBufferWidth * _backBufferHeight) - posInit;

	memcpy(&_pixels[posInit], text, maxLen);
}

void ScreenConsole::clear()
{
	memset(_pixels, 0, _backBufferHeight * _backBufferWidth);
}
