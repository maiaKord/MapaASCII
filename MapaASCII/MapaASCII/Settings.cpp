#include "Settings.h"

void Settings::load()
{
	size_t pos = 0;
	for (int x = 0; x < 6; x++)
	{
		pos = _config.find("\n");

		switch (x)
		{
		case 0:
			_superiorLatitude = _config.substr(0, pos);
			break;
		case 1:
			_inferiorLatitude = _config.substr(0, pos);
			break;
		case 2:
			_leftLongitude = _config.substr(0, pos);
			break;
		case 3:
			_rightLongitude = _config.substr(0, pos);
			break;
		case 4:
			_screenHeight = _config.substr(0, pos);
			break;
		case 5:
			_screenWidth = _config.substr(0, pos);
			break;
		default:
			break;
		}

		_config = _config.substr(pos + 1);
	}
}

// *************************
// encapsule

std::string Settings::getFilePath()
{
	return _filePath;
}
void Settings::setFilePath(std::string value)
{
	_filePath = value;
}

std::string Settings::getFileName()
{
	return _fileName;
}
void Settings::setFileName(std::string value)
{
	_fileName = value;
}

std::string Settings::getFullPath()
{
	return _fullPath;
}
void Settings::setFullPath(std::string value)
{
	_fullPath = value;
}

std::string Settings::getConfig()
{
	return _config;
}
void Settings::setConfig(std::string value)
{
	_config = value;
}

std::string Settings::getSuperiorLatitude()
{
	return _superiorLatitude;
}
void Settings::setSuperiorLatitude(std::string value)
{
	_superiorLatitude = value;
}

std::string Settings::getInferiorLatitude()
{
	return _inferiorLatitude;
}
void Settings::setInferiorLatitude(std::string value)
{
	_inferiorLatitude = value;
}

std::string Settings::getLeftLongitude()
{
	return _leftLongitude;
}
void Settings::setLeftLongitude(std::string value)
{
	_leftLongitude = value;
}

std::string Settings::getRightLongitude()
{
	return _rightLongitude;
}
void Settings::setRightLongitude(std::string value)
{
	_rightLongitude = value;
}

int Settings::getScreenHeight()
{
	int value = std::stoi(_screenHeight);
	return value;
}
void Settings::setScreenHeight(std::string value)
{
	_screenHeight = value;
}

int Settings::getScreenWidth()
{
	int value = std::stoi(_screenWidth);
	return value;
}
void Settings::setScreenWidth(std::string value)
{
	_screenWidth = value;
}