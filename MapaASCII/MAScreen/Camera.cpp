#include "Camera.h"

Camera::Camera()
{
	position = { 0,0 };
	scale = { 1,1 };
}

Camera::Camera(SVector2D cameraPos, SVector2D cameraScale)
{
	position = cameraPos;
	scale = cameraScale;
}

Camera::Camera(SVector2Df cameraPos, SVector2Df cameraScale)
	:Camera(cameraPos.x, cameraPos.y, cameraScale.x, cameraScale.y)
{
}

Camera::Camera(int xPosition, int yPosition, int xScale, int yScale)
{
	position.x = xPosition;
	position.y = yPosition;

	scale.x = xScale;
	scale.y = yScale;
}

Camera::Camera(float xPosition, float yPosition, float xScale, float yScale)
{
	position.x = (int)xPosition;
	position.y = (int)yPosition;

	scale.x = (int)xScale;
	scale.y = (int)yScale;
}