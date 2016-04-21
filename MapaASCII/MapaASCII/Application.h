#pragma once
#include "Map.h"
#include "Screen.h"
#include "Utils.h"
#include "SettingsViewPort.h"
#include "EntityLoader.h"
#include "EntityRenderer.h"

struct Cursor
{
	int x = 1;
	int y = 1;

	void fixPosition(int maxWidth, int maxHeight)
	{
		y = min(y, maxHeight - 1);
		y = max(y, 0);

		x = min(x, maxWidth - 1);
		x = max(x, 0);
	}
};

struct Application
{
	Cursor _cursor;
	SVector2D _screenPosition = { 0,0 };
	SettingsViewPort _settingsVP;
	Screen* _screen = nullptr;
	Map<char>* _mapTile = nullptr;
	
	Application() { }

	~Application()
	{
		if (_screen)
			delete(_screen);
		if (_mapTile)
			delete(_mapTile);
	}

	void init () 
	{
		_settingsVP.load();

		_screen = new Screen(_settingsVP.getScreenWidth(), _settingsVP.getScreenHeight());
		_screen->init();

		_mapTile = new Map<char>;	// Tile represent the terrain material
		_mapTile->init(1920, 1980);

		std::string _filePath = "./";
		std::string _fileName = "map1.txt";
		std::string _fullPath = _filePath + _fileName;

		std::vector<Entity*> _entityList;

		EntityLoader _entityLoader;
		_entityLoader.load(_fullPath, _entityList);

		EntityPolygon* ep;
		EntityCircle* ec;

		for (Entity* e : _entityList)
		{
			switch (e->shape)
			{
			case ENTITY_SHAPE_POLYGON:
			case ENTITY_SHAPE_SQUARE:
			case ENTITY_SHAPE_TRIANGLE:
				ep = dynamic_cast<EntityPolygon*>(e);
				Utils::convertGeoToMeters(ep->_pointListGeo, ep->_pointListMeters);
				break;
			case ENTITY_SHAPE_CIRCLE:
				ec = dynamic_cast<EntityCircle*>(e);
				ec->circlePositionMeters = Utils::convertGeoToMeters(ec->circlePositionGeo);
				break;
			}
		}

	}

	void update()
	{
		int _screenWidth = _screen->getBackBufferWidth();
		int _screenHeight = _screen->getBackBufferHeight();

		_mapTile->print(_screen->getPixels(), _screenWidth, _screenHeight * _screenWidth, _screenPosition);

		// move the cursor in base of the keys up, down, right and left
		if (GetAsyncKeyState(VK_UP))
			_cursor.y -= 1;

		if (GetAsyncKeyState(VK_DOWN))
			_cursor.y += 1;

		if (GetAsyncKeyState(VK_RIGHT))
			_cursor.x += 1;

		if (GetAsyncKeyState(VK_LEFT))
			_cursor.x -= 1;

		// check the limit and fix the position
		_cursor.fixPosition(_screenWidth, _screenHeight);

		// draw the cursor
		_screen->getPixels()[_cursor.y * _screenWidth + _cursor.x] = '#';

		// draw the screen
		_screen->print();

		// this is necesary to don't see tearing. This happent because we don't write directly in the console
		Sleep(70);
	}


};
