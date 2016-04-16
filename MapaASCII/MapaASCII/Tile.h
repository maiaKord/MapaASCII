#pragma once
#include <string>
#include "MapObject.h"

struct Tile : MapObject
{
	char character = ' ';
	static const Tile defaults[256];
	
	Tile(){}

	Tile(char vCharacter, std::string vIdentifier, std::string vDescription)
		:MapObject(vIdentifier, vDescription)
	{
		character = vCharacter;
	}
};
