#pragma once
#include <string>
#include <vector>
#include "Vector.h"
#include "MapObject.h"

// types of tiles
enum ENTITY_SHAPE
{
	ENTITY_SHAPE_POLYGON,
	ENTITY_SHAPE_CIRCLE,
	ENTITY_SHAPE_SQUARE,
	ENTITY_SHAPE_TRIANGLE,
	ENTITY_SHAPE_NONE
};

struct Entity : MapObject
{
	ENTITY_SHAPE shape = ENTITY_SHAPE_NONE;
	std::vector<SVector2D> _pointList;

	Entity(){}

	Entity(ENTITY_SHAPE vShape, std::string vIdentifier, std::string vDescription)
		:MapObject(vIdentifier, vDescription)
	{
		shape = vShape;
	}
};
