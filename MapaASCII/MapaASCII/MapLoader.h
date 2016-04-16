#pragma once
#include <string>
#include "Utils.h"

class MapLoader 
{
	std::string _filePath = "./";
	std::string _fileName = "settings.txt";
	std::string _fullPath = _filePath + _fileName;

	std::string _config = Utils::readTextFile(_fullPath.c_str());



public:

	std::string getFilePath();
	void setFilePath(std::string value);

	std::string getFileName();
	void setFileName(std::string value);

	std::string getFullPath();
	void setFullPath(std::string value);

};