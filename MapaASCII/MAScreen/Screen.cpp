#include "Screen.h"

Screen::Screen()
{
	_settingsVP.load();
	_backBufferHeight = _settingsVP.getScreenHeight();
	_backBufferWidth = _settingsVP.getScreenWidth();

	SVector2Df cameraF = Utils::convertGeoToMeters(SVector2Df(_settingsVP.getLeftLongitude(), _settingsVP.getSuperiorLatitude()));
	_camera.x = (int)cameraF.x;
	_camera.z = (int)cameraF.z;

	_pixels = (char*)malloc(_backBufferHeight * _backBufferWidth);
}

Screen::~Screen()
{
	if(_pixels)
		free(_pixels);
}

//**************************
// encapsulamiento

int Screen::getBackBufferWidth()
{
	return _backBufferWidth;
}

int Screen::getBackBufferHeight()
{
	return _backBufferHeight;
}

char* Screen::getPixels()
{
	return _pixels;
}

SVector2D& Screen::getCamera()
{
	return _camera;
}