#pragma once

#include "Tile.hpp"

class TileMap
{
private:
	//Variables
	float gridSizeF;
	sf::Vector2u mapMaxSize;
	unsigned gridSizeU;
	unsigned layers;
	std::vector<std::vector<std::vector<Tile*>>> map; // x, y and z (z voor layer)
	sf::Texture tileTextureSheet;

public:
	//Constructor/Destructor
	TileMap(float gridSize, unsigned width, unsigned height);
	virtual ~TileMap();

	//Functions
	void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect);
	void removeTile(const unsigned x, const unsigned y, const unsigned z);
	void update();
	void render(sf::RenderTarget& target);

	
};

