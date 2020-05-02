#include "stdafx.h"
#include "TileMap.hpp"

//Constructor/Destructor
TileMap::TileMap(float gridSize, unsigned width, unsigned height)
{
	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->mapMaxSize.x = width;
	this->mapMaxSize.y = height;
	this->layers = 1;

	this->map.resize(this->mapMaxSize.x);
	for (size_t x = 0; x < this->mapMaxSize.x; x++)
	{
		this->map.push_back(std::vector<std::vector<Tile*>>());

		for (size_t y = 0; y < this->mapMaxSize.y; y++)
		{
			this->map[x].resize(this->mapMaxSize.y);
			this->map[x].push_back(std::vector<Tile*>());

			for (size_t z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers);
				this->map[x][y].push_back(nullptr);
			}
		}
	}
}

TileMap::~TileMap()
{
	for (size_t x = 0; x < this->mapMaxSize.x; x++)
	{
		for (size_t y = 0; y < this->mapMaxSize.y; y++)
		{
			for (size_t z = 0; z < this->layers; z++)
			{
				delete this->map[x][y][z];
			}
		}
	}
}

//Functions
void TileMap::addTile()
{

}

void TileMap::removeTile()
{

}


void TileMap::update()
{

}

void TileMap::render(sf::RenderTarget& target)
{
	for (auto& x : this->map)
	{
		for (auto& y : x)
		{
			for (auto  *z : y)
			{
				if(z != nullptr)
				z->render(target);
			}
		}
	}
}


