#pragma once

#include <vector>
#include "Entity.h"
#include "Map.h"

struct EntityRenderer 
{
	void init( std::vector<Entity*>& listEntity, Map<char>& map);
};
