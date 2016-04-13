#pragma once

#define BACKBUFFER_WIDTH 80
#define BACKBUFFER_HEIGHT 25

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

	void print()
	{
		printf("%s", pixels);
	}
};
