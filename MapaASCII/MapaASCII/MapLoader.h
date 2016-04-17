#pragma once
#include <string>
#include "Utils.h"
#include "Map.h"
#include "Entity.h"

class MapLoader 
{

public:
	void load( std::string vFullPath, Map<char>* vMap );

	void parseEntity(std::string line, Entity** entity);
	void parseIdentifier(std::string identifier, Entity** _entity);
	void parsePolygon(std::string line, EntityPolygon* _entity);
	void parseCircle(std::string line, EntityCircle* _entity);
};