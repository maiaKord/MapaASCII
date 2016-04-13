#pragma once

// define the layers counts on memory 16*16
#define MAP_WIDTH 16
#define MAP_HEIGHT 16

// define the amongs of tiles
#define LAYER_WIDTH 16
#define LAYER_HEIGHT 16

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
