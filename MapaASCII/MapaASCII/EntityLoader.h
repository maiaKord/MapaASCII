#pragma once
#include <string>
#include "Utils.h"
#include "Map.h"
#include "Entity.h"

class EntityLoader 
{

public:
	void load( std::string vFullPath, std::vector<Entity*>& listEntity);

	void parseEntity(std::string line, Entity** entity);
	void parseIdentifier(std::string identifier, Entity** _entity);
	void parsePolygon(std::string line, EntityPolygon* _entity);
	void parseCircle(std::string line, EntityCircle* _entity);
};