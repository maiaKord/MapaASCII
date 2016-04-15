#include <cstdio>
#include <Windows.h>
#include "Map.h"
#include "Screen.h"
#include "Utils.h"
#include "Settings.h"

struct Cursor 
{
	int x = 1;
	int y = 1;
};

void main()
{
	bool _running = true;
	
	Settings _settings;
	_settings.load();

	Screen* _screen = new Screen( _settings.getScreenWidth(), _settings.getScreenHeight() );
	_screen->init();
	
	Map<char> _mapTile;
	//Map<int> _mapEntityStatic;
	//Map<int> _mapEntityDynamic;

	Cursor _cursor;
	Vector _screenPosition = {0,0};

	// Tile represent the terrain material
	_mapTile.init(1920, 1980);

	// Entity Static represent different objects that can't move like a building, flowers, others
	//_mapEntityStatic.init(1920, 1980);

	// Entity Dynamic represent different objects that can move like a cat, cars, others
	//_mapEntityDynamic.init(1920, 1980);

	while (_running)
	{
		int _screenWidth = _screen->getBackBufferWidth();
		int _screenHeight = _screen->getBackBufferHeight();

		_mapTile.print(_screen->getPixels(), _screenWidth, (_screenHeight - 1) * _screenWidth, _screenPosition);
		//_mapEntityStatic.print(&_screen.pixels[0][0], BACKBUFFER_WIDTH, (BACKBUFFER_HEIGHT-1)*BACKBUFFER_WIDTH, _screenPosition);
		//_mapEntityDynamic.print(&_screen.pixels[0][0], BACKBUFFER_WIDTH, (BACKBUFFER_HEIGHT - 1)*BACKBUFFER_WIDTH, _screenPosition);


		//**********************
		// move the cursor in base of the keys up, down, right and left
		if (GetAsyncKeyState(VK_UP))
		{
			_cursor.y -= 1;
		}

		if (GetAsyncKeyState(VK_DOWN))
		{
			_cursor.y += 1;
		}

		if (GetAsyncKeyState(VK_RIGHT))
		{
			_cursor.x += 1;
		}

		if (GetAsyncKeyState(VK_LEFT))
		{
			_cursor.x -= 1;
		}

		// check the limit and fix the position

		if ( _cursor.y >= _screenHeight - 1)
			_cursor.y = _screenHeight - 2;

		if (_cursor.y < 0 )
			_cursor.y = 0;

		if (_cursor.x >= _screenWidth)
			_cursor.x = _screenWidth - 1;

		if (_cursor.x < 0)
			_cursor.x = 0;

		// draw the cursor
		_screen->getPixels() [_cursor.y * _screenWidth + _cursor.x] = '#';
				
		// draw the screen
		_screen->print();
				
		// this is necesary to don't see tearing. This happent because we don't write directly in the console
		Sleep(20);

		// press the scape key to exit
		if ( GetAsyncKeyState(VK_ESCAPE) )
		{
			_running = false;
		}
	}
}