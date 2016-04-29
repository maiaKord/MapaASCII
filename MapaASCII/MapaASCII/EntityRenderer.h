#pragma once

#include <vector>
#include "Entity.h"
#include "Map.h"

struct EntityRenderer 
{
	void renderPolygon( std::vector<SVector2Df>& listPoints, Map<char>& map, char character);
	void renderCircle( SVector2Df point, float ratio, Map<char>& map, char character);
	void renderPoints ( std::vector<SVector2Df>& listPoints, Map<char>& map, char character);
	void renderLines ( std::vector<SVector2Df>& listPoints, Map<char>& map, char character);

	void render( std::vector<Entity*>& listEntity, Map<char>& map);
};
