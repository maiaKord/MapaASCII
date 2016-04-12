#include <cstdio>
#include <Windows.h>


#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define BACKBUFFER_WIDTH 80
#define BACKBUFFER_HEIGHT 24

struct Screen
{
	char pixels [BACKBUFFER_HEIGHT][BACKBUFFER_WIDTH];

	Screen()
	{
		char* pixelsLineal = (char*)pixels;
		for(int i=0; i < (BACKBUFFER_HEIGHT * BACKBUFFER_WIDTH); i++) 
		{
			pixelsLineal[i] = ' ';
		}

		for (int y = 0 ; y < BACKBUFFER_HEIGHT ; y++)
		{
			pixels[y][BACKBUFFER_WIDTH - 1] = '\n';
		}

		pixels[BACKBUFFER_HEIGHT-1][BACKBUFFER_WIDTH-1] = 0;
	}

	void print()
	{
		printf("%s", pixels);
	}
};

struct Map
{
	char data [MAP_HEIGHT][MAP_WIDTH];

	Map( )
	{
		char* dataLineal = (char*)data;
		for(int i=0; i < (MAP_HEIGHT * MAP_WIDTH); i++)
		{
			dataLineal[i] = ' ';
		}
	}

	void init()
	{
		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			for (int x = 0; x < MAP_WIDTH; x++)
			{
				if ( x == 0 || x == (MAP_WIDTH - 1) )
				{
					data[y][x] = '|';
				}
				
				if ( y == 0 || y == (MAP_HEIGHT - 1) )
				{
					data[y][x] = '-';
				}
			}
		}
	}

	int print( Screen* screen, int maxHeight, int minWidth )
	{
		for (int y = 0; y < MAP_HEIGHT; y++)
		{
			for (int x = 0; x < MAP_WIDTH; x++)
			{
				screen->pixels[y][x] = data[y][x];
			}
		}

		return 0;
	}

};

void main()
{
	Screen _screen;
	Map _map;
	bool _running = true;

	while (_running)
	{
		_map.init();

		_map.print(&_screen, BACKBUFFER_HEIGHT, BACKBUFFER_WIDTH);
		_screen.print();

		Sleep(100);

		if ( GetAsyncKeyState(VK_ESCAPE) )
		{
			_running = false;
		}
	}
}