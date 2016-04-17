#pragma once
#include <string>
#include <vector>
#include "Vector.h"
#include "Tile.h"

// types of tiles
enum ENTITY_SHAPE
{
	ENTITY_SHAPE_POLYGON,
	ENTITY_SHAPE_CIRCLE,
	ENTITY_SHAPE_SQUARE,
	ENTITY_SHAPE_TRIANGLE,
	ENTITY_SHAPE_NONE
};

struct Entity
{
	const Tile* tile = nullptr;
	ENTITY_SHAPE shape = ENTITY_SHAPE_NONE;
	
	Entity(){}

	Entity(ENTITY_SHAPE vShape, Tile* vTile)
	{
		shape = vShape;
		tile = vTile;
	}
	virtual ~Entity(){}
};

struct EntityCircle : Entity
{
	SVector2Df circlePosition;
	float circleRadius;

	EntityCircle(){}
};

struct EntityPolygon : Entity
{
	std::vector<SVector2Df> _pointList;

	EntityPolygon() {}
};