#include "EntityRenderer.h"
#include "Utils.h"

void EntityRenderer::init( std::vector<Entity*>& listEntity, Map<char>& map)
{
	for ( Entity* e : listEntity )
	{
		EntityPolygon* ep = nullptr;
		EntityCircle* ec = nullptr;

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
		{
			ep->boundingSquare = Utils::calculateBoundingSquare(ep->_pointListMeters);
			SVector2Df pMin = ep->boundingSquare._pointMin;
			SVector2Df pMax = ep->boundingSquare._pointMax;

			for ( int z = pMin.z; z < pMax.z; z++)
			{
				for ( int x = pMin.x; x < pMax.x; x++)
				{
					if ( Utils::isPointInPath(SVector2Df(x,z) , ep->_pointListMeters) )
					{
						map.setTile( x, z, ep->tile->character );
					}
				}
			}
		}

		if (ec)
		{
			ec->boundingSquare = Utils::calculateBoundingSquare(ec->circlePositionMeters, ec->circleRadiusMeters);
			SVector2Df pMin = ec->boundingSquare._pointMin;
			SVector2Df pMax = ec->boundingSquare._pointMax;

			for (int z = pMin.z; z < pMax.z; z++)
			{
				for (int x = pMin.x; x < pMax.x; x++)
				{
					if ( SVector2Df(x,z).distance(ec->circlePositionMeters ) <= ec->circleRadiusMeters )
					{
						map.setTile(x, z, ec->tile->character);
					}
				}
			}
			
		}
	
	}
}

