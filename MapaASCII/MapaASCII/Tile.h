#pragma once
#include <string>

#define TILE_COUNT 255

struct Tile
{
	char character = 0;
	std::string identifier = "";
	std::string description = "";
	static const Tile defaults[TILE_COUNT];
	
	Tile(){}

	Tile(char vCharacter, std::string vIdentifier, std::string vDescription)
	{
		character = vCharacter;
		identifier = vIdentifier;
		description = vDescription;
	}
};
