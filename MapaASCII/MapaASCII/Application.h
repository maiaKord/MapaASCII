#pragma once
#include <algorithm>
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
		y = std::min(y, maxHeight - 1);
		y = std::max(y, 0);

		x = std::min(x, maxWidth - 1);
		x = std::max(x, 0);
	}
};

struct Application
{
	Cursor _cursor;
	SettingsViewPort _settingsVP;
	Screen* _screen = nullptr;
	SVector2D _camera = { 0,0 };
	
	Map<char>* _mapTile = nullptr;
	std::vector<Entity*> _entityList;
	
	EntityRenderer* _eRender = nullptr;
	
	Application() { }

	~Application()
	{
		if (_screen)
			delete(_screen);
		if (_mapTile)
			delete(_mapTile);
		if (_eRender)
			delete(_eRender);
		
		for(Entity* e : _entityList)
			delete(e);
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

		SVector2Df cameraF = Utils::convertGeoToMeters(SVector2Df(_settingsVP.getLeftLongitude(), _settingsVP.getSuperiorLatitude()));
		_camera.x = cameraF.x;
		_camera.z = cameraF.z;
		
		_eRender->init(_entityList, *_mapTile);
	}

	void update()
	{
		int _screenWidth = _screen->getBackBufferWidth();
		int _screenHeight = _screen->getBackBufferHeight();

		_mapTile->print(_screen->getPixels(), _screenWidth, _screenHeight * _screenWidth, _camera);

		// move the cursor in base of the keys up, down, right and left
		if (GetAsyncKeyState(VK_UP))
			_cursor.y -= 1;

		if (GetAsyncKeyState(VK_DOWN))
			_cursor.y += 1;

		if (GetAsyncKeyState(VK_RIGHT))
			_cursor.x += 1;

		if (GetAsyncKeyState(VK_LEFT))
			_cursor.x -= 1;

		// move the camera
		if( GetAsyncKeyState('W') )
			_camera.y -= 1;

		if (GetAsyncKeyState('S'))
			_camera.y += 1;

		if (GetAsyncKeyState('D'))
			_camera.x += 1;

		if (GetAsyncKeyState('A'))
			_camera.x -= 1;

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
