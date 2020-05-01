#pragma once

#include "Tile.hpp"

class TileMap
{
private:
	//Variables
	sf::Vector2u mapMaxSize;
	unsigned gridSizeU;
	unsigned layers;
	std::vector<std::vector<std::vector<Tile>>> map; // x, y and z (z voor layer)
	

public:
	//Constructor/Destructor
	TileMap();
	virtual ~TileMap();

	//Functions
};

