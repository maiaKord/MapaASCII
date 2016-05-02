#include "Application.h"
#include "ScreenConsole.h"
#include "ScreenGraphic.h"

#define UP_LINES 4
#define ALL_LINES (4 + UP_LINES)
#define VELOCITY_MOVE 4

Application::Application() 
{
	_cursor = {1,1};
	_screen = nullptr;
	_mapTile = nullptr;
	_eRender = nullptr;
}

Application::~Application()
{
	if (_screen)
		delete(_screen);
	if (_mapTile)
		delete(_mapTile);
	if (_eRender)
		delete(_eRender);

	for (Entity* e : _entityList)
		delete(e);
}

void Application::init()
{
	ScreenConsole* _screenConsole = new ScreenConsole();
	_screenConsole->init();
	_screen = _screenConsole;

	load();
}

void Application::init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ScreenGraphic* _screenGraphic = new ScreenGraphic();
	_screenGraphic->init(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	_screen = _screenGraphic;

	load();
}

void Application::load()
{
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

	_eRender = new EntityRenderer();
	_eRender->render(_entityList, *_mapTile);
}

void Application::update()
{
	int _screenWidth = _screen->getBackBufferWidth();
	int _screenHeight = _screen->getBackBufferHeight();

	_screen->clear();
	_screen->printText(1, 1, "Move the camera using 'W' 'A' 'S' 'D' keys ");
	_mapTile->print( (_screen->getPixels() + (_screenWidth * UP_LINES)), _screenWidth, (_screenHeight - ALL_LINES) * _screenWidth, _screen->getCamera());

	// move the cursor in base of the keys up, down, right and left
	if (GetAsyncKeyState(VK_UP))
		_cursor.y -= 1;

	if (GetAsyncKeyState(VK_DOWN))
		_cursor.y += 1;

	if (GetAsyncKeyState(VK_RIGHT))
		_cursor.x += 1;

	if (GetAsyncKeyState(VK_LEFT))
		_cursor.x -= 1;

	// scale the camera
	if (GetAsyncKeyState(VK_ADD))
	{ 
		_screen->getCamera().scale.y += 1;
		_screen->getCamera().scale.x += 1;
	}

	if (GetAsyncKeyState(VK_SUBTRACT))
	{ 
		_screen->getCamera().scale.y -= 1;
		_screen->getCamera().scale.x -= 1;
	}

	// move the camera
	if (GetAsyncKeyState('W'))
		_screen->getCamera().position.y -= VELOCITY_MOVE;

	if (GetAsyncKeyState('S'))
		_screen->getCamera().position.y += VELOCITY_MOVE;

	if (GetAsyncKeyState('D'))
		_screen->getCamera().position.x += VELOCITY_MOVE;

	if (GetAsyncKeyState('A'))
		_screen->getCamera().position.x -= VELOCITY_MOVE;

	// check the limit and fix the position
	_cursor.fixPosition(_screenWidth, _screenHeight);

	// draw the cursor
	_screen->getPixels()[_cursor.y * _screenWidth + _cursor.x] = '#';

	// draw the screen
	_screen->print();

	// this is necesary to don't see tearing. This happent because we don't write directly in the console
	Sleep(70);
}