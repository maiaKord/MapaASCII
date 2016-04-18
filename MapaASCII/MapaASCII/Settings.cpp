#include "SettingsViewPort.h"

void SettingsViewPort::load()
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

std::string SettingsViewPort::getFilePath()
{
	return _filePath;
}
void SettingsViewPort::setFilePath(std::string value)
{
	_filePath = value;
}

std::string SettingsViewPort::getFileName()
{
	return _fileName;
}
void SettingsViewPort::setFileName(std::string value)
{
	_fileName = value;
}

std::string SettingsViewPort::getFullPath()
{
	return _fullPath;
}
void SettingsViewPort::setFullPath(std::string value)
{
	_fullPath = value;
}

std::string SettingsViewPort::getConfig()
{
	return _config;
}
void SettingsViewPort::setConfig(std::string value)
{
	_config = value;
}

std::string SettingsViewPort::getSuperiorLatitude()
{
	return _superiorLatitude;
}
void SettingsViewPort::setSuperiorLatitude(std::string value)
{
	_superiorLatitude = value;
}

std::string SettingsViewPort::getInferiorLatitude()
{
	return _inferiorLatitude;
}
void SettingsViewPort::setInferiorLatitude(std::string value)
{
	_inferiorLatitude = value;
}

std::string SettingsViewPort::getLeftLongitude()
{
	return _leftLongitude;
}
void SettingsViewPort::setLeftLongitude(std::string value)
{
	_leftLongitude = value;
}

std::string SettingsViewPort::getRightLongitude()
{
	return _rightLongitude;
}
void SettingsViewPort::setRightLongitude(std::string value)
{
	_rightLongitude = value;
}

int SettingsViewPort::getScreenHeight()
{
	int value = std::stoi(_screenHeight);
	return value;
}
void SettingsViewPort::setScreenHeight(std::string value)
{
	_screenHeight = value;
}

int SettingsViewPort::getScreenWidth()
{
	int value = std::stoi(_screenWidth);
	return value;
}
void SettingsViewPort::setScreenWidth(std::string value)
{
	_screenWidth = value;
}