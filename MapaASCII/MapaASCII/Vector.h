#pragma once

struct SVector2D
{
	int x = 0;
	int z = 0;

	SVector2D(int vX, int vZ)
	{
		x = vX;
		z = vZ;
	}
};

struct SVector2Df
{
	float x = 0;
	float z = 0;

	SVector2Df(){}

	SVector2Df(float vX, float vZ)
	{
		x = vX;
		z = vZ;
	}

	SVector2Df(std::string vX, std::string vZ)
	{
		x = std::stof(vX);
		z = std::stof(vZ);
	}
};