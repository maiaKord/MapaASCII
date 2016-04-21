#include "EntityLoader.h"

void EntityLoader::load(std::string vFullPath, std::vector<Entity*>& listEntity)
{
	std::string _outputMap = Utils::readTextFile(vFullPath.c_str());
	size_t pos = 0;

	while ( _outputMap.length() )
	{
		pos = _outputMap.find("\n");
		Entity* entity = nullptr;
		parseEntity( _outputMap.substr(0, pos), &entity);
		_outputMap = _outputMap.substr(pos + 1);
		
		listEntity.push_back(entity);
	}
}

void EntityLoader::parseEntity(std::string line, Entity** entity)
{
	Entity* _entity = nullptr;
	size_t pos = 0;
	
	pos = line.find(",");
	std::string identifier = line.substr(0,pos);
	line = line.substr(pos + 1);

	parseIdentifier( identifier, &_entity );
	
	switch (_entity->shape)
	{
		case ENTITY_SHAPE_POLYGON:
		case ENTITY_SHAPE_SQUARE:
		case ENTITY_SHAPE_TRIANGLE:
			if ( _entity->tile->identifier.compare("edificio­publico") )
			{
				pos = line.find(",");
				std::string name = line.substr(0, pos);
				line = line.substr(pos + 1);
				_entity->name = name;
			}
			parsePolygon(line, dynamic_cast<EntityPolygon*>(_entity));
		break;
		case ENTITY_SHAPE_CIRCLE:
			parseCircle(line, dynamic_cast<EntityCircle*>(_entity));
			break;
	}

	*entity = _entity;
}

void EntityLoader::parseIdentifier( std::string identifier, Entity** _entity)
{
	for ( int x = 0; x < TILE_COUNT; x++)
	{
		if ( Tile::defaults[x].character == 0 )
			break;

		if ( identifier.compare(Tile::defaults[x].identifier) == 0 )
		{
			if (identifier.compare("manzana") || identifier.compare("boulevard") || identifier.compare("edificio-privado") || identifier.compare("edificio-publico") || identifier.compare("agua"))
			{
				*_entity = new EntityPolygon();
				(*_entity)->shape = ENTITY_SHAPE_POLYGON;
			}
			else if (identifier.compare("arbol") || identifier.compare("semaforo"))
			{
				*_entity = new EntityCircle();
				(*_entity)->shape = ENTITY_SHAPE_CIRCLE;
			}
			else if (identifier.compare("No definido"))
			{
				*_entity = new Entity();
				(*_entity)->shape = ENTITY_SHAPE_NONE;
			}

			(*_entity)->tile = &Tile::defaults[x];
					
			break;
		}
	}
	
}

void EntityLoader::parsePolygon( std::string line, EntityPolygon* _entity )
{		
	size_t pos = 0;

	while (line.length())
	{
		pos = line.find(",");
		std::string latitude = line.substr(0, pos);
		line = line.substr(pos + 1);

		pos = line.find(",");
		std::string longitude = line.substr(0, pos);
		line = line.substr(pos + 1);

		_entity->_pointListGeo.push_back(SVector2Df(latitude, longitude));

		if ( pos == std::string::npos )
		{
			break;
		}
	}
}

void EntityLoader::parseCircle(std::string line, EntityCircle* _entity)
{
	size_t pos = 0;

	pos = line.find(",");
	std::string latitude = line.substr(0, pos);
	line = line.substr(pos + 1);

	pos = line.find(",");
	std::string longitude = line.substr(0, pos);
	line = line.substr(pos + 1);

	pos = line.find(",");
	std::string radius = line.substr(0, pos);
	line = line.substr(pos + 1);
	
	_entity->circlePositionGeo = SVector2Df(latitude, longitude);
	_entity->circleRadiusMeters = std::stof(radius);

}