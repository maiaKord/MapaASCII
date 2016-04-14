#pragma once
#define BACKBUFFER_WIDTH 132
#define BACKBUFFER_HEIGHT 50

struct Screen
{
	char pixels[BACKBUFFER_HEIGHT][BACKBUFFER_WIDTH];
	
	Screen()
	{
		char* pixelsLineal = (char*)pixels;
		for (int i = 0; i < (BACKBUFFER_HEIGHT * BACKBUFFER_WIDTH); i++)
		{
			pixelsLineal[i] = ' ';
		}

		for (int y = 0; y < BACKBUFFER_HEIGHT; y++)
		{
			pixels[y][BACKBUFFER_WIDTH - 1] = '\n';
		}

		pixels[BACKBUFFER_HEIGHT - 1][BACKBUFFER_WIDTH - 1] = 0;
	}

	void init( int screenWidth, int screenHeight)
	{
		HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFOEX csbiInfo = {};
		GetConsoleScreenBufferInfoEx(hConsoleOut, &csbiInfo);

		//csbiInfo.dwCursorPosition.Y = csbiInfo.dwSize.Y-1;
		csbiInfo.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);

		//csbiInfo.wAttributes
		csbiInfo.dwSize.X = screenWidth;
		csbiInfo.dwSize.Y = screenHeight;
		csbiInfo.dwMaximumWindowSize.X = screenWidth;
		csbiInfo.dwMaximumWindowSize.Y = screenHeight;
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

		SetConsoleScreenBufferInfoEx(hConsoleOut, &csbiInfo);
	}

	void print()
	{
		printf("%s", pixels);
	}
};
