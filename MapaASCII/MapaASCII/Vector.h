#pragma once
#include <string>

struct SVector2D
{
	int x;
	union
	{
		int z;
		int y;
	};
	
	SVector2D()
	{
		x = 0;
		z = 0;
	}

	SVector2D(int vX, int vZ)
	{
		x = vX;
		z = vZ;
	}

	bool operator == (SVector2D v )
	{
		return (x == v.x && z == v.z);
	}
};

struct SVector2Df
{
	float x = 0;
	union
	{
		float z;
		float y;
	};

	SVector2Df(){}

	SVector2Df(float vX, float vZ)
	{
		x = vX;
		z = vZ;
	}

	SVector2Df(int vX, int vZ)
	{
		x = (float)vX;
		z = (float)vZ;
	}

	SVector2Df(std::string vX, std::string vZ)
	{
		x = std::stof(vX);
		z = std::stof(vZ);
	}

	float sqlength()
	{
		float sqlength = x*x + z*z;

		return sqlength;
	}

	float lenght()
	{
		float l = 0;
		float sql = sqlength();
		
		if (sql > 0 )
			l = sqrt(sql);

		return l;
	}

	float distance( SVector2Df p)
	{
		SVector2Df vd = p - *this;
		float d = vd.lenght();

		return d;
	}
	
	SVector2Df operator + (SVector2Df v )
	{
		SVector2Df r;

		r.x = x + v.x;
		r.z = z + v.z;

		return r;
	}
	
	SVector2Df operator - (SVector2Df v)
	{
		SVector2Df r;

		r.x = x - v.x;
		r.z = z - v.z;

		return r;
	}
};

struct BoundingSquare
{
	SVector2Df _pointMin;
	SVector2Df _pointMax;
};