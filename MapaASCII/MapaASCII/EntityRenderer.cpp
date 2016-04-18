#include "EntityRenderer.h"
#include "Vector.h"
#include <math.h>

# define M_PI           3.14159265358979323846  /* pi */

// generally used geo measurement function
void measure(SVector2Df point1, SVector2Df point2 )
{
	// Radius of earth in KM
	float R = 6378.137; 

	float dLat = (point1.x - point2.x) * M_PI / 180;
	float dLon = (point1.z - point2.z) * M_PI / 180;
	float a = sin(dLat / 2) * sin(dLat / 2) + cos(point1.x * M_PI / 180) * cos(point2.x * M_PI / 180) * sin(dLon / 2) * sin(dLon / 2);
	float c = 2 * atan2(sqrt(a), sqrt(1 - a));
	float d = R * c;

	//convert to meters
	float meters = d * 1000;  
}
