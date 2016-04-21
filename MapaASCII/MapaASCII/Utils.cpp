#include "Utils.h"
#include <math.h>
#include <algorithm>

# define M_PI 3.14159265358979323846  /* pi */

// generally used geo measurement function
float Utils::measure(SVector2Df point1, SVector2Df point2)
{
	// Radius of earth in KM
	float R = 6378.137f;

	float dLat = (point1.x - point2.x) * M_PI / 180;
	float dLon = (point1.z - point2.z) * M_PI / 180;
	float a = sin(dLat / 2) * sin(dLat / 2) + cos(point1.x * M_PI / 180) * cos(point2.x * M_PI / 180) * sin(dLon / 2) * sin(dLon / 2);
	float c = 2 * atan2(sqrt(a), sqrt(1 - a));
	float d = R * c;

	//convert to meters
	float meters = d * 1000;

	return meters;
}

SVector2Df Utils::convertGeoToMeters(SVector2Df p1)
{
	SVector2Df p2;
	SVector2Df result;
	
	// longitud
	p2 = p1;
	p2.x = 0;
	result.z = measure(SVector2Df(0, 0), p2 );

	//latitud
	result.x = measure(p2, p1);

	return result;
}

void Utils::convertGeoToMeters(const std::vector<SVector2Df>& listPointsGeo, std::vector<SVector2Df>& listPointsMeters)
{
	for (SVector2Df p : listPointsGeo)
	{
		listPointsMeters.push_back( convertGeoToMeters(p) );
	}
}

BoundingSquare Utils::calculateBoundingSquare(SVector2Df point, float radio)
{
	BoundingSquare bs;
	
	bs._pointMax = point + SVector2Df(radio,radio);
	bs._pointMin = point - SVector2Df(radio, radio);;

	return bs;
}

BoundingSquare Utils::calculateBoundingSquare(std::vector<SVector2Df> listPoints )
{
	BoundingSquare bs;
	bs._pointMax = {0,0};
	bs._pointMin = { 0,0 };

	if ( listPoints.size() )
	{
		bs._pointMax = listPoints[0];
		bs._pointMin = listPoints[0];

		for( SVector2Df p : listPoints )
		{
			bs._pointMax.x = std::max(p.x, bs._pointMax.x);
			bs._pointMax.z = std::max(p.z, bs._pointMax.z);

			bs._pointMin.x = std::min(p.x, bs._pointMin.x);
			bs._pointMin.z = std::min(p.z, bs._pointMin.z);
		}
	}

	return bs;
}

//Rasterizing a 2D polygon using even-odd rule (https://en.wikipedia.org/wiki/Even%E2%80%93odd_rule)
bool Utils::isPointInPath( SVector2Df point, std::vector<SVector2Df> listPoints)
{
	int num = listPoints.size();
	int i = 0;
	int j = num - 1;
	bool c = false;

	while( i < num )
	{
		if ( ( (listPoints[i].z > point.z) != (listPoints[j].z > point.z) )  
				&& (point.x < ( listPoints[j].x - listPoints[i].x ) * ( point.z - listPoints[i].z )  
				/ (listPoints[j].z - listPoints[i].z) + listPoints[i].x) )
			c = !c;
			
		j = i;
		i++;
	}

	return c;
}

std::string Utils::readTextFile(const char *fileName)
{
	std::string fileContent;
	std::ifstream fileStream(fileName, std::ios::in);

	if (!fileStream.is_open())
	{
		printf("File %s not found\n", fileName);
		return "";
	}

	std::string line = "";
	while (!fileStream.eof())
	{
		getline(fileStream, line);
		fileContent.append(line + "\n");
	}

	fileStream.close();
	return fileContent;
}
