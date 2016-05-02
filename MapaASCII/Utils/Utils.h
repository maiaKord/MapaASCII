#pragma once

#include <string>
#include <fstream>
#include <vector>
#include "Vector.h"

namespace Utils
{
	std::string readTextFile(const char *fileName);

	double measure(SVector2Df point1, SVector2Df point2);
	SVector2Df convertGeoToMeters( SVector2Df p1 );
	void convertGeoToMeters(const std::vector<SVector2Df>& listPointsGeo, std::vector<SVector2Df>& listPointsMeters);
	
	BoundingSquare calculateBoundingSquare(std::vector<SVector2Df> listPoints);
	BoundingSquare calculateBoundingSquare(SVector2Df point, float radio);
	bool isPointInPath(SVector2Df point, std::vector<SVector2Df> listPoints);
}
