#include "MapLoader.h"


// *************************
// encapsule

std::string MapLoader::getFilePath()
{
	return _filePath;
}
void MapLoader::setFilePath(std::string value)
{
	_filePath = value;
}

std::string MapLoader::getFileName()
{
	return _fileName;
}
void MapLoader::setFileName(std::string value)
{
	_fileName = value;
}

std::string MapLoader::getFullPath()
{
	return _fullPath;
}
void MapLoader::setFullPath(std::string value)
{
	_fullPath = value;
}