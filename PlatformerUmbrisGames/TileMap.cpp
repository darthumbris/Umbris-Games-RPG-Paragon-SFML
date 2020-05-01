#include "stdafx.h"
#include "TileMap.hpp"

//Constructor/Destructor
TileMap::TileMap()
{
	this->gridSizeU = 50;
	this->mapMaxSize.x = 5000;
	this->mapMaxSize.y = 5000;
	this->layers = 5;

	
	for (size_t x = 0; x < this->mapMaxSize.x; x++)
	{
		this->map.push_back(std::vector<std::vector<Tile>>());

		for (size_t y = 0; y < this->mapMaxSize.y; y++)
		{
			this->map[x].push_back(std::vector<Tile>());

			for (size_t i = 0; i < this->layers; i++)
			{
				this->map[x][y].push_back(Tile());
			}
		}
	}
}

TileMap::~TileMap()
{

}

//Functions
