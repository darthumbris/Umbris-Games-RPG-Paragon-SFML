#pragma once

#include "Tile.hpp"
#include "Entity.hpp"

class Tile;
class Entity;

class TileMap
{
private:
	//Functions
	void clear();

	//Variables
	float gridSizeF;
	sf::Vector2i maxSizeWorldGrid;
	sf::Vector2f maxSizeWorldF;
	int gridSizeI;
	int layers;
	std::vector< std::vector< std::vector< std::vector< Tile*> > > > map; // x, y and z (z voor layer)
	std::stack<Tile*> deferredRenderStack;
	std::string textureFile;
	sf::Texture tileSheet;
	sf::RectangleShape collisionBox; // To display the collision box of an entity

	//Culling
	int fromX;
	int toX;
	int fromY;
	int toY;
	int layer;

public:
	//Constructor/Destructor
	TileMap(float gridSize, int width, int height, std::string texture_file);
	TileMap(const std::string file_name);
	virtual ~TileMap();

	//Accessors
	const bool tileEmpty(const int x, const int y, const int z) const;
	const sf::Texture* getTileSheet() const;
	const int getLayerSize(const int x, const int y, const int layer) const; 
	const sf::Vector2i& getMaxSizeGrid() const;
	const sf::Vector2f& getMaxSizeGridF() const;

	//Functions
	void addTile(const int x, const int y, const int z,
		const sf::IntRect& texture_rect, const bool& collision, const short& type);
	void removeTile(const int x, const int y, const int z);
	void saveToFile(const std::string file_name);
	void loadFromFile(const std::string file_name);

	void updateCollision(Entity* entity, const float& delatTime);

	void update();
	void render(
		sf::RenderTarget& target, const sf::Vector2i& gridPosition, 
		sf::Shader* shader = nullptr, const sf::Vector2f playerPos = sf::Vector2f(), 
		const bool show_hitbox = false);
	void renderDeferred(
		sf::RenderTarget& target, sf::Shader* shader = nullptr, 
		const sf::Vector2f playerPos = sf::Vector2f());
};

