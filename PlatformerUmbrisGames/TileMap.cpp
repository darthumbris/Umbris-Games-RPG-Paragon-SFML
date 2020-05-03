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

	//Reserve instead of resize?
	this->map.resize(this->mapMaxSize.x, std::vector<std::vector<Tile*>>());
	for (size_t x = 0; x < this->mapMaxSize.x; x++)
	{
		for (size_t y = 0; y < this->mapMaxSize.y; y++)
		{
			this->map[x].resize(this->mapMaxSize.y, std::vector<Tile*>());
			for (size_t z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers, nullptr);
			}
		}
	}

	if(!this->tileTextureSheet.loadFromFile("Resources/Images/Tiles/tilesheet1.png"))
		std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILE TEXTURE SHEET" << "\n";
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
void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect)
{
	/*Take two indices from the mouse position (and the layer position) in the grid and add a
	tile to that position if the internal tilemap array allows it*/

	//in the bounds
	if (x < this->mapMaxSize.x && x >= 0 &&
		y < this->mapMaxSize.y && y >= 0 &&
		z <= this->layers && z >= 0)
	{
		if (this->map[x][y][z] == nullptr) 
		{
			// Ok to add a tile
			this->map[x][y][z] = new Tile(
				x * this->gridSizeF, y * this->gridSizeF, 
				this->gridSizeF, this->tileTextureSheet, texture_rect);
			std::cout << "debug: Added a Tile" << "\n";
		}
	}
}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z)
{
	/*Take two indices from the mouse position (and the layer position) in the grid and remove a
	tile in that position if the internal tilemap array allows it*/

	//in the bounds
	if (x < this->mapMaxSize.x && x >= 0 &&
		y < this->mapMaxSize.y && y >= 0 &&
		z <= this->layers && z >= 0)
	{
		if (this->map[x][y][z] != nullptr)
		{
			// Ok to remove a tile
			delete this->map[x][y][z];
			this->map[x][y][z] = nullptr;
			std::cout << "debug: Removed a Tile" << "\n";
		}
	}
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


