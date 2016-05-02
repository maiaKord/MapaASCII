#pragma once
#include "Vector.h"

struct Camera
{
	SVector2D position;
	SVector2D scale;

	Camera();
	Camera ( SVector2D cameraPos, SVector2D cameraScale);
	Camera( SVector2Df cameraPos, SVector2Df cameraScale);
	Camera(int xPosition, int yPosition, int xScale, int yScale);
	Camera(float xPosition, float yPosition, float xScale, float yScale);

};