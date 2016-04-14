#pragma once
#include <string>

// types of tiles
enum TILE_SHAPE
{
	TILE_SHAPE_POLYGON,
	TILE_SHAPE_CIRCLE,
	TILE_SHAPE_SQUARE,
	TILE_SHAPE_TRIANGLE,
	TILE_SHAPE_NONE
};

struct Tile
{
	TILE_SHAPE shape = TILE_SHAPE_NONE;
	char character = ' ';
	std::string identifier = "";
	std::string description = "";

	static const Tile defaults[256];

	Tile()
	{}

	Tile(TILE_SHAPE vShape, char vCharacter, std::string vIdentifier, std::string vDescription)
	{
		identifier = vIdentifier;
		description = vDescription;
		character = vCharacter;
		shape = vShape;
	}
};
