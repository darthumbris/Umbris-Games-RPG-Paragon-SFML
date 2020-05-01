#include "stdafx.h"
#include "TileMap.hpp"

//Constructor/Destructor
TileMap::TileMap()
{
	this->gridSizeF = 50.f;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->mapMaxSize.x = 26;
	this->mapMaxSize.y = 20;
	this->layers = 1;

	this->map.resize(this->mapMaxSize.x);
	for (size_t x = 0; x < this->mapMaxSize.x; x++)
	{
		this->map.push_back(std::vector<std::vector<Tile>>());

		for (size_t y = 0; y < this->mapMaxSize.y; y++)
		{
			this->map[x].resize(this->mapMaxSize.y);
			this->map[x].push_back(std::vector<Tile>());

			for (size_t i = 0; i < this->layers; i++)
			{
				this->map[x][y].resize(this->layers);
				this->map[x][y].push_back(Tile(x * this->gridSizeF, 
					y * this->gridSizeF, 
					this->gridSizeF));
			}
		}
	}
}

TileMap::~TileMap()
{

}

//Functions
void TileMap::update()
{

}

void TileMap::render(sf::RenderTarget& target)
{
	for (auto& x : this->map)
	{
		for (auto& y : x)
		{
			for (auto& z : y)
			{
				z.render(target);
			}
		}
	}
}


