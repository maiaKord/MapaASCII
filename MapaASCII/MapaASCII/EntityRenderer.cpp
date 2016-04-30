#include "EntityRenderer.h"
#include "Utils.h"

void EntityRenderer::renderPolygon(std::vector<SVector2Df>& listPoints, Map<char>& map, char character)
{
	BoundingSquare boundingSquare = Utils::calculateBoundingSquare(listPoints);
	SVector2Df pMin = boundingSquare._pointMin;
	SVector2Df pMax = boundingSquare._pointMax;

	for (int z = (int)pMin.z; z < pMax.z; z++)
	{
		for (int x = (int)pMin.x; x < pMax.x; x++)
		{
			if (Utils::isPointInPath(SVector2Df(x, z), listPoints))
			{
				map.setTile(x, z, character);
			}
		}
	}
}

void EntityRenderer::renderCircle(SVector2Df point, float ratio, Map<char>& map, char character)
{
	BoundingSquare boundingSquare = Utils::calculateBoundingSquare(point, ratio);
	SVector2Df pMin = boundingSquare._pointMin;
	SVector2Df pMax = boundingSquare._pointMax;

	for (int z = (int)pMin.z; z < pMax.z; z++)
	{
		for (int x = (int)pMin.x; x < pMax.x; x++)
		{
			if (SVector2Df(x, z).distance(point) <= ratio)
			{
				map.setTile(x, z, character);
			}
		}
	}
}
void EntityRenderer::renderPoints(std::vector<SVector2Df>& listPoints, Map<char>& map, char character)
{
	for (SVector2Df p : listPoints)
	{
		map.setTile((int)p.x, (int)p.z, character);
	}
}

void EntityRenderer::renderLines(std::vector<SVector2Df>& listPoints, Map<char>& map, char character)
{
	// WIP
}

void EntityRenderer::render( std::vector<Entity*>& listEntity, Map<char>& map)
{
	for ( Entity* e : listEntity )
	{
		EntityPolygon* ep = nullptr;
		EntityCircle* ec = nullptr;

		if ( !e ) 
			continue;

		switch (e->shape)
		{
			case ENTITY_SHAPE_POLYGON:
			case ENTITY_SHAPE_SQUARE:
			case ENTITY_SHAPE_TRIANGLE:
				ep = dynamic_cast<EntityPolygon*>(e);
				break;
			case ENTITY_SHAPE_CIRCLE:
				ec = dynamic_cast<EntityCircle*>(e);
				break;
		}


		if ( ep )
			renderPolygon(ep->_pointListMeters, map, ep->tile->character);

		if (ec)
			renderCircle(ec->circlePositionMeters, ec->circleRadiusMeters, map, ec->tile->character );
	
	}
}

