#pragma once
#include <string>

struct MapObject
{
	std::string identifier = "";
	std::string description = "";

	MapObject(){}

	MapObject(std::string vIdentifier, std::string vDescription)
	{
		identifier = vIdentifier;
		description = vDescription;
	}
};
