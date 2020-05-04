#pragma once

#include "Tile.hpp"

class TileMap
{
private:
	//Functions
	void clear();

	//Variables
	float gridSizeF;
	sf::Vector2u mapMaxSize;
	unsigned gridSizeU;
	unsigned layers;
	std::vector<std::vector<std::vector<Tile*>>> map; // x, y and z (z voor layer)
	std::string textureFile;
	sf::Texture tileSheet;

public:
	//Constructor/Destructor
	TileMap(float gridSize, unsigned width, unsigned height, std::string texture_file);
	virtual ~TileMap();

	//Accessors
	const sf::Texture* getTileSheet() const;

	//Functions
	void addTile(const unsigned x, const unsigned y, const unsigned z, 
		const sf::IntRect& texture_rect, const bool& collision, const short& type);
	void removeTile(const unsigned x, const unsigned y, const unsigned z);
	
	void saveToFile(const std::string file_name);
	void loadFromFile(const std::string file_name);

	void update();
	void render(sf::RenderTarget& target);
};

