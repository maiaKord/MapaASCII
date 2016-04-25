#pragma once

#define REGION_WIDTH 16
#define REGION_HEIGHT 16

// define the amongs of tiles
#define LAYER_WIDTH 16
#define LAYER_HEIGHT 16

struct TileCoords
{
	SVector2D tile = { 0,0 };
	SVector2D layer = { 0,0 };
	SVector2D region = { 0,0 }; 

	TileCoords(int x, int z)
	{
		set( x, z);
	}

	void set(int x, int z)
	{
		setX( x );
		setZ( z );
	}

	void setX(int x)
	{
		tile.x = x % LAYER_WIDTH;
		layer.x = x / LAYER_WIDTH;
		region.x = layer.x / REGION_WIDTH;
		layer.x %= REGION_WIDTH;

		if ( x < 0 )
		{
			tile.x = LAYER_WIDTH - tile.x;
			layer.x  = REGION_WIDTH - layer.x;
		}
	}

	void setZ(int z)
	{
		tile.z = z % LAYER_HEIGHT;
		layer.z = z / LAYER_HEIGHT;
		region.z = layer.z / REGION_HEIGHT;
		layer.z %= REGION_HEIGHT;
		
		if ( z < 0 )
		{
			tile.z = LAYER_HEIGHT - tile.z;
			layer.z = REGION_HEIGHT - layer.z;
		}
	}
};

// mapLayer is the data map
template<typename _tileType> struct MapLayer
{
	_tileType tiles[LAYER_HEIGHT][LAYER_WIDTH];

	void write(std::ofstream& file)
	{
		if (file.is_open())
		{
			file.write(&tiles[0][0], LAYER_HEIGHT * LAYER_WIDTH);
		}
	}
};

template<typename _tileType> struct Region
{
	SVector2D position = {0,0};
	MapLayer<_tileType>* layers[REGION_HEIGHT][REGION_WIDTH];

	Region( int vX, int vZ)
	{
		position.x = vX;
		position.z = vZ;

		for (int z = 0; z < REGION_HEIGHT; z++)
		{
			for (int x = 0; x < REGION_WIDTH; x++)
				layers[z][x] = nullptr;
		}
	}

	Region()
	{
		for (int z = 0; z < REGION_HEIGHT; z++)
		{
			for (int x = 0; x < REGION_WIDTH; x++)
				layers[z][x] = nullptr;
		}
	}

	~Region()
	{
		for (int z = 0; z < REGION_HEIGHT; z++)
		{
			for (int x = 0; x < REGION_WIDTH; x++)
				delete(layers[z][x]);
		}
	}

	void init()
	{
		for (int z = 0; z < REGION_HEIGHT; z++)
		{
			for (int x = 0; x < REGION_WIDTH; x++)
			{
				if (layers[z][x])
				{
					delete(layers[z][x]);
					layers[z][x] = nullptr;
				}
			}
		}
	}

};
