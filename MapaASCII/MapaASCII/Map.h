#pragma once

#include <string>
#include <vector>

// define the layers counts on memory 16*16
#define MAP_WIDTH 16
#define MAP_HEIGHT 16

// define the amongs of tiles
#define LAYER_WIDTH 16
#define LAYER_HEIGHT 16

// types of tiles
enum TILE_SHAPE 
{
	TILE_SHAPE_POLYGON, 
	TILE_SHAPE_CIRCLE, 
	TILE_SHAPE_SQUARE, 
	TILE_SHAPE_TRIANGLE,
	TILE_SHAPE_NONE
};

struct Tile
{
	std::string identifier = "";
	std::string description = "";
	char character = ' ';
	TILE_SHAPE shape = TILE_SHAPE_NONE;

	Tile() 
	{ }
	
	Tile( std::string vIdentifier, std::string vDescription, char vCharacter, TILE_SHAPE vShape)
	{
		identifier = vIdentifier;
		description = vDescription;
		character = vCharacter;
		shape = vShape;
	}
};

struct Vector
{
	int x = 0;
	int z = 0;

	Vector( int vX, int vZ )
	{
		x = vX;
		z = vZ;
	}
};

// mapLayer is the data map
template<typename _tileType> struct MapLayer 
{
	_tileType tiles[LAYER_HEIGHT][LAYER_WIDTH];
	
};

// map going to be rendering in base of mapLayer data
template<typename _tileType>class Map
{
	MapLayer<_tileType> *_layers[MAP_HEIGHT][MAP_WIDTH];
	int _height = 0;
	int _width = 0;
	Vector _positionViewPort = {0,0};

	std::vector<Tile> _listTiles;

public:
	Map()
	{
		for (int z = 0; z < MAP_HEIGHT; z++)
		{
			for (int x = 0; x < MAP_WIDTH; x++)
			{
				_layers[z][x] = nullptr;
			}
		}
	}

	void init( int height, int width )
	{
		_height = height;
		_width = width;

		for (int z = 0; z < MAP_HEIGHT; z++)
		{
			for (int x = 0; x < MAP_WIDTH; x++)
			{
				if ( _layers[z][x] )
				{
					delete(_layers[z][x]);
					_layers[z][x] = nullptr;
				}
			}
		}

		initTiles();
	}
	
	void initTiles()
	{
		Tile t;

		t = Tile(
			"manza",
			"Elemento básico en la definición de un mapa de ciudad, permite ubicar edificaciones, parques y árboles en el mapa.",
			'm',
			TILE_SHAPE_POLYGON);

		_listTiles.push_back(t);

		t = Tile(
			"boulevard",
			"Se encuentra en distintas calles como divisor entre carriles pudiendo contener",
			'b',
			TILE_SHAPE_POLYGON);

		_listTiles.push_back(t);

		t = Tile(
			"edificio-­privado​",
			"Contempla una estructura edilicia privada o pública. No se posee información sobre los interiores de la edificación sino sobre los límites inscriptos en el catastro local.Los edificios públicos tienen una particularidad : poseen nombre que debe ser impreso al usuario a modo de leyenda para su ubicación.",
			'e',
			TILE_SHAPE_POLYGON);

		_listTiles.push_back(t);

		t = Tile(
			"edificio-­publico",
			"Contempla una estructura edilicia privada o pública. No se posee información sobre los interiores de la edificación sino sobre los límites inscriptos en el catastro local.Los edificios públicos tienen una particularidad : poseen nombre que debe ser impreso al usuario a modo de leyenda para su ubicación.",
			'A',
			TILE_SHAPE_POLYGON);

		_listTiles.push_back(t);

		t = Tile(
			"arbol",
			"Representa distintos elementos de vegetación que se pueden encontrar en las manzanas o boulevares.",
			'@',
			TILE_SHAPE_CIRCLE);

		_listTiles.push_back(t);

		t = Tile(
			"semaforo",
			"Descripción: Se trata de los señalizadores de tránsito que se pueden encontrar tanto en manzanas como en boulevares o colgantes en las calles.",
			'#',
			TILE_SHAPE_CIRCLE);

		_listTiles.push_back(t);

		t = Tile(
			"agua",
			"Representa mares, ríos, arroyos, lagunas o cualquier afluente que merezca ser tratado por los mapas en desarrollo.No puede coexistir en una misma ubicación con ningún otro tipo de elemento.",
			'-',
			TILE_SHAPE_POLYGON);

		_listTiles.push_back(t);

		t = Tile(
			"No definido",
			"Se asume que es el elemento base para definir un mapa. No es necesario indicarlo en la estructura de objetos de una ciudad sino que se asumirá que todo punto del mapa que no tuviera algún elemento posicionado se trata de una calle.No será necesario agregar nombres a las calles ni ningún caracter particular ya que se imprimirán como espacios.",
			' ',
			TILE_SHAPE_NONE);

		_listTiles.push_back(t);
	}

	// ***************************
	// encapsulation

	_tileType getTile(int x, int z)
	{
		MapLayer<_tileType>* capa = _layers[z / 16][x / 16];

		if ( capa == 0 )
		{
			return '~';
		}

		// transform input coordinates to layer space
		return capa->tiles[z % 16][x % 16];
	}

	void setTile(int x, int z, _tileType type)
	{	
		if ( _layers[z / 16][x / 16] == 0)
		{
			// if not exists, create it
			_layers[z / 16][x / 16] = new MapLayer<_tileType>();
		}
		
		// if exists, change it
		_layers[z / 16][x / 16]->tiles[z % 16][x % 16] = type;
	}

	int getWidth()
	{
		return _width;
	}

	void setWidth( int width)
	{
		_width = width;
	}

	int getHeight()
	{
		return _height;
	}

	void setHeight(int height)
	{
		_height = height;
	}

	// ***************************
	// methods

	int print(char* pixels, int maxWidth, int maxPixels, Vector position)
	{
		int height = maxPixels / maxWidth;
		 
		// go over the screen
		for (int z = 0; z < height; z++)
		{
			for (int x = 0; x < maxWidth; x++)
			{
				// convert 1D from 2D
				pixels[z * maxWidth + x] = getTile( x - position.x , z - position.z );
			}
		}

		return 0;
	}

	

};
