#include "Screen.h"

Screen::Screen()
{
	_settingsVP.load();
	_backBufferHeight = _settingsVP.getScreenHeight();
	_backBufferWidth = _settingsVP.getScreenWidth();
	
	SVector2Df cameraFpos = Utils::convertGeoToMeters(SVector2Df(_settingsVP.getLeftLongitude(), _settingsVP.getSuperiorLatitude()));
	SVector2Df cameraFpos2 = Utils::convertGeoToMeters(SVector2Df(_settingsVP.getRightLongitude(), _settingsVP.getInferiorLatitude()));
	SVector2Df cameraFscale = cameraFpos2 - cameraFpos;
	_camera = Camera(cameraFpos, cameraFscale);

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

Camera& Screen::getCamera()
{
	return _camera;
}