#pragma once

#define NOMINMAX

#include <algorithm>
#include "Map.h"
#include "Screen.h"
#include "Utils.h"
#include "SettingsViewPort.h"
#include "EntityLoader.h"
#include "EntityRenderer.h"

struct Cursor
{
	int x;
	int y;

	Cursor(){}

	Cursor(int vX, int vY)
	{
		x = vX;
		y = vY;
	}

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
	Screen* _screen;
	SVector2D _camera;
	Map<char>* _mapTile;
	std::vector<Entity*> _entityList;
	EntityRenderer* _eRender;
	
	Application();
	~Application();

	void init ();

	void update();

};
