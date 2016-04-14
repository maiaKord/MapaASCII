#pragma once
#include <string>
#include "Utils.h"

class Settings
{
	std::string _filePath = "./";
	std::string _fileName = "settings.txt";
	std::string _fullPath = _filePath + _fileName;

	std::string _config = Utils::readTextFile(_fullPath.c_str());

	std::string _superiorLatitude = "";
	std::string _inferiorLatitude = "";
	std::string _leftLongitude = "";
	std::string _rightLongitude = "";
	std::string _screenHeight = "";
	std::string _screenWidth = "";

	public:

	void load() 
	{
		size_t pos = 0;
		for (int x = 0; x < 6; x++)
		{
			pos = _config.find("\n");

			switch (x)
			{
			case 1:
				_superiorLatitude = _config.substr(0, pos);
				break;
			case 2:
				_inferiorLatitude = _config.substr(0, pos);
				break;
			case 3:
				_leftLongitude = _config.substr(0, pos);
				break;
			case 4:
				_rightLongitude = _config.substr(0, pos);
				break;
			case 5:
				_screenHeight = _config.substr(0, pos);
				break;
			case 6:
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

	std::string getFilePath()
	{
		return _filePath;
	}
	void setFilePath(std::string value)
	{
		_filePath = value;
	}

	std::string getFileName()
	{
		return _fileName;
	}
	void setFileName(std::string value)
	{
		_fileName = value;
	}

	std::string getFullPath()
	{
		return _fullPath;
	}
	void setFullPath(std::string value)
	{
		_fullPath = value;
	}

	std::string getConfig()
	{
		return _config;
	}
	void setConfig(std::string value)
	{
		_config = value;
	}

	std::string getSuperiorLatitude()
	{
		return _superiorLatitude;
	}
	void setSuperiorLatitude(std::string value)
	{
		_superiorLatitude = value;
	}

	std::string getInferiorLatitude()
	{
		return _inferiorLatitude;
	}
	void setInferiorLatitude(std::string value)
	{
		_inferiorLatitude = value;
	}
	
	std::string getLeftLongitude()
	{
		return _leftLongitude;
	}
	void setLeftLongitude(std::string value)
	{
		_leftLongitude = value;
	}

	std::string getRightLongitude()
	{
		return _rightLongitude;
	}
	void setRightLongitude(std::string value)
	{
		_rightLongitude = value;
	}

	std::string getScreenHeight()
	{
		return _screenHeight;
	}
	void setScreenHeight(std::string value)
	{
		_screenHeight = value;
	}

	std::string getScreenWidth()
	{
		return _screenWidth;
	}
	void setScreenWidth(std::string value)
	{
		_screenWidth = value;
	}
};
