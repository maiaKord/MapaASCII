#pragma once
#include <vector>
#include "Tile.h"
#include "Vector.h"
#include "Region.h"

// define the layers counts on memory 16*16
#define MAP_WIDTH 16
#define MAP_HEIGHT 16

// map going to be rendering in base of mapLayer 
template<typename _tileType>class Map
{
	std::vector<Region<_tileType>*> regions;
	int _height = 0;
	int _width = 0;
	SVector2D _positionViewPort = {0,0};

public:
	Map() {}

	~Map()
	{
		for(Region<_tileType>* r : regions)
			delete(r);
	}

	void init( int height, int width )
	{
		_height = height;
		_width = width;

		for (Region<_tileType>* r : regions)
			delete(r);

		regions.clear();
		
	}

	int print(char* pixels, int maxWidth, int maxPixels, SVector2D position)
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

	// ***************************
	// encapsule

	_tileType getTile(int x, int z)
	{
		TileCoords tc(x, z);
		_tileType tile = '~';

		for (Region<_tileType>* r : regions)
		{
			if (r->position == tc.region)
			{
				if ( r->layers[tc.layer.x][tc.layer.z] )
				{
					tile = r->layers[tc.layer.z][tc.layer.x]->tiles[tc.tile.z][tc.tile.x];
				}
				break;
			}
		}

		return tile;
	}

	void setTile(int x, int z, _tileType type)
	{
		TileCoords tc(x, z);
		Region<_tileType>* region = nullptr;

		for(Region<_tileType>* r : regions) 
		{
			if ( r->position == tc.region)
			{
				region = r;
				break;				
			}
		}

		// if region don't exist
		if ( !region )
		{
			regions.push_back( new Region<_tileType>( tc.region.x, tc.region.z ));	
			region = regions[regions.size() - 1];	
		}

		// if layer region don't exist
		if ( region->layers[tc.layer.z][tc.layer.x]  == nullptr ) 
			region->layers[tc.layer.z][tc.layer.x] = new MapLayer<_tileType>();

		// assign new value
		region->layers[tc.layer.z][tc.layer.x]->tiles[tc.tile.z][tc.tile.x] = type;
	}

	int getWidth()
	{
		return _width;
	}

	void setWidth(int width)
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

private:
	
	void saveMap()
	{
		std::string _filePath = "./";
		std::string _fileName = "map1.bin";
		std::string _fullPath = _filePath + _fileName;

		std::ofstream file(fullPath, ios::out | ios::binary);

		if (file.is_open())
		{
			/*for (MapLayer<_tileType> layer : _layers) 
			{
				layer.write(file);
			}*/
		}

		file.close();
	}

	void readBinary(std::string fullPath, MapLayer<_tileType>*& layer)
	{
		streampos size;
		MapLayer<_tileType>* mapLayer = nullptr;

		ifstream file(fullPath, ios::in | ios::binary | ios::ate);

		if (file.is_open())
		{
			size = file.tellg();
			file.seekg(0, ios::beg);

			/*for( int z = 0; z < MAP_HEIGHT; z++ )
			{
				for ( int x = 0; x < MAP_WIDTH; x++ )
				{
					mapLayer = new MapLayer<_tileType>();
					file.read(mapLayer, size);

					if (layer[z / 16][x / 16])
					{
						if ( layer[z / 16][x / 16] != mapLayer)
						{
							layer[z / 16][x / 16] = mapLayer;
						}	
					}
				}
			}*/
			file.close();

			return memblock;
		}
	}

};
