#include "stdafx.h"
#include "TileMap.hpp"

void TileMap::clear()
{
	if (!this->map.empty())
	{
		for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
		{
			for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
			{
				for (int z = 0; z < this->layers; z++)
				{
					for (size_t k = 0; k < this->map[x][y][z].size(); k++)
					{
						delete this->map[x][y][z][k];
						this->map[x][y][z][k] = nullptr;
					}
					this->map[x][y][z].clear();
				}
				this->map[x][y].clear();
			}
			this->map[x].clear();
		}
		this->map.clear();
	}
}

//Constructor/Destructor
TileMap::TileMap(float gridSize, int width, int height, std::string texture_file)
{
	this->gridSizeF = gridSize;
	this->gridSizeI = static_cast<int>(this->gridSizeF);
	this->maxSizeWorldGrid.x = width;
	this->maxSizeWorldGrid.y = height;
	this->maxSizeWorldF.x = static_cast<float>(width) * gridSize;
	this->maxSizeWorldF.y = static_cast<float>(height) * gridSize;
	this->layers = 1;
	this->textureFile = texture_file;
	//this->deferredRenderStack = nullptr;
	

	//culling variables initializen
	this->fromX = 0;
	this->toX = 0;
	this->fromY = 0;
	this->toY = 0;
	this->layer = 0;

	this->map.resize(this->maxSizeWorldGrid.x, std::vector< std::vector< std::vector< Tile*> > >());
	for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
	{
		for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
		{
			this->map[x].resize(this->maxSizeWorldGrid.y, std::vector< std::vector<Tile*> >());
			for (int z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers, std::vector<Tile*>());
			}
		}
	}

	if(!this->tileSheet.loadFromFile(texture_file))
		std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILE TEXTURESHEET FILENAME: " << texture_file << "\n";

	this->collisionBox.setSize(sf::Vector2f(gridSize, gridSize));
	this->collisionBox.setFillColor(sf::Color(255, 0, 0, 20));
	this->collisionBox.setOutlineColor(sf::Color::Red);
	this->collisionBox.setOutlineThickness(1.f);
}

TileMap::TileMap(const std::string file_name)
{
	//culling variables initializen
	this->fromX = 0;
	this->toX = 0;
	this->fromY = 0;
	this->toY = 0;
	this->layer = 0;

	this->loadFromFile(file_name);

	this->collisionBox.setSize(sf::Vector2f(this->gridSizeF, this->gridSizeF));
	this->collisionBox.setFillColor(sf::Color(255, 0, 0, 20));
	this->collisionBox.setOutlineColor(sf::Color::Red);
	this->collisionBox.setOutlineThickness(1.f);
}

TileMap::~TileMap()
{
	this->clear();
}

const bool TileMap::tileEmpty(const int x, const int y, const int z) const
{
	if (x >= 0 && x < this->maxSizeWorldGrid.x &&
		y >= 0 && y < this->maxSizeWorldGrid.y &&
		z >= 0 && z < this->layers)
	{
		return this->map[x][y][z].empty();
	}

	return false;
}

//Accessors
const sf::Texture* TileMap::getTileSheet() const
{
	return &this->tileSheet;
}

const int TileMap::getLayerSize(const int x, const int y, const int layer) const
{
	//Gives the amount of tiles in this position (because you can layer tiles now)
	if (x >= 0 && x < static_cast<int>(this->map.size()))
	{
		if (y >= 0 && y < static_cast<int>(this->map[x].size()))
		{
			if (layer >= 0 && layer < static_cast<int>(this->map[x][y].size()))
			{
				return this->map[x][y][layer].size();
			}
		}
	}
	return -1;
	
}

const sf::Vector2i& TileMap::getMaxSizeGrid() const
{
	return this->maxSizeWorldGrid;
}

const sf::Vector2f& TileMap::getMaxSizeGridF() const
{
	return this->maxSizeWorldF;
}

const char* TileMap::getMapTypes(MapTypes::Types e)
{
	const std::map<MapTypes::Types, const char*> TypeStrings{
		{MapTypes::Types::FOREST, "Forest"},
		{MapTypes::Types::OVERWORLD, "Overworld"},
		{MapTypes::Types::MOUNTAIN, "Mountain"},
		{MapTypes::Types::PLAINS, "Plains"},
		{MapTypes::Types::RIVER, "River"},
		{MapTypes::Types::SEA, "Sea"},
		{MapTypes::Types::DESERT, "Desert"},
	};
	auto it = TypeStrings.find(e);
	return it == TypeStrings.end() ? "Out of range" : it->second;
}

//Functions
void TileMap::addTile(const int x, const int y, const int z,
	const sf::IntRect& texture_rect, const bool& collision, const short& type)
{
	/*Take two indices from the mouse position (and the layer position) in the grid and add a
	tile to that position if the internal tilemap array allows it*/

	//in the bounds
	if (x < this->maxSizeWorldGrid.x && x >= 0 &&
		y < this->maxSizeWorldGrid.y && y >= 0 &&
		z <= this->layers && z >= 0)
	{
		// If the Currently Selected Element is not empty:
		if (!tileEmpty(x, y, z))
		{
			// Only add if it's NOT the Same Texture (checks the passed in rect):
			if (this->map[x][y][z][map[x][y][z].size() - 1]->getRect() != texture_rect)
			{
				this->map[x][y][z].push_back(new Tile(x, y, this->gridSizeF, this->tileSheet, texture_rect, collision, type));
				std::cout << "debug: Added a Tile in filled location" << "\n";
			}
		}
		// Or if empty -> just Add a Tile:
		else
		{
			this->map[x][y][z].push_back(new Tile(x, y, this->gridSizeF, this->tileSheet, texture_rect, collision, type));
			std::cout << "debug: Added a Tile in empty location" << "\n";
		}
	}
}

void TileMap::removeTile(const int x, const int y, const int z)
{
	/*Take two indices from the mouse position (and the layer position) in the grid and remove a
	tile in that position if the internal tilemap array allows it*/

	//in the bounds
	if (x < this->maxSizeWorldGrid.x && x >= 0 &&
		y < this->maxSizeWorldGrid.y && y >= 0 &&
		z <= this->layers && z >= 0)
	{
		if (!this->map[x][y][z].empty())
		{
			// Ok to remove a tile
			delete this->map[x][y][z][this->map[x][y][z].size() - 1];
			this->map[x][y][z].pop_back();
			std::cout << "debug: Removed a Tile" << "\n";
		}
	}
}


void TileMap::saveToFile(const std::string file_name)
{
	/*Saves the entire tilemap to a text file
	Format: 
	Basic:
	Size x y
	gridSize
	layers (amount of)
	texture tilesheet file

	All tiles:
	gridPos x y z(layer), Texture rect x y(specific texture in the tilesheet), collision ,type 
	*/

	std::ofstream out_file;

	out_file.open(file_name);

	if (out_file.is_open())
	{
		out_file << this->maxSizeWorldGrid.x << " " << this->maxSizeWorldGrid.y << "\n"
		<< this->gridSizeI << "\n"
		<< this->layers << "\n"
		<< this->textureFile << "\n";

		for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
		{
			for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
			{
				for (int z = 0; z < this->layers; z++)
				{
					if (!this->map[x][y][z].empty())
					{
						for (size_t k = 0; k < this->map[x][y][z].size(); k++)
						{
							out_file << x << " " << y << " " << z << " " <<
								this->map[x][y][z][k]->getAsString()
								<< " "; // Make sure this last space is not saved
						}
						
					}
				}
			}
		}
	}
	else
	{
		std::cout << "ERROR::TILEMAP::COULD NOT SAVE TO FILE::FILENAME: " << file_name << "\n";
	}

	out_file.close();
	std::cout << "saved the map" << "\n";
}

void TileMap::loadFromFile(const std::string file_name)
{
	std::ifstream in_file;

	in_file.open(file_name);

	if (in_file.is_open())
	{
		sf::Vector2u size;
		int gridSize = 0;
		int layers = 0;
		std::string texture_file = "";
		int x = 0;
		int y = 0;
		int z = 0;
		int trX = 0; //(texture rect x)
		int trY = 0;
		bool collision = false;
		short type = 0;

		//Basics
		in_file >> size.x >> size.y >> gridSize >> layers >> texture_file;
		
		//Tiles
		this->gridSizeF = static_cast<float>(gridSize);
		this->gridSizeI = gridSize;
		this->maxSizeWorldGrid.x = size.x;
		this->maxSizeWorldGrid.y = size.y;
		this->maxSizeWorldF.x = static_cast<float>(size.x * gridSize);
		this->maxSizeWorldF.y = static_cast<float>(size.y * gridSize);
		this->layers = layers;
		this->textureFile = texture_file;

		this->clear();

		this->map.resize(this->maxSizeWorldGrid.x, std::vector< std::vector< std::vector< Tile*> > >());
		for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
		{
			for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
			{
				this->map[x].resize(this->maxSizeWorldGrid.y, std::vector< std::vector< Tile*> >());
				for (int z = 0; z < this->layers; z++)
				{
					this->map[x][y].resize(this->layers, std::vector<Tile*>());
				}
			}
		}

		if (!this->tileSheet.loadFromFile(texture_file))
			std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILE TEXTURESHEET FILENAME: " << texture_file << "\n";

		//Load all Tiles
		while (in_file >> x >> y >> z >> trX >> trY >> collision >> type)
		{
			this->map[x][y][z].push_back(new Tile(
				x, y, 
				this->gridSizeF, 
				this->tileSheet, 
				sf::IntRect(trX, trY, this->gridSizeI, this->gridSizeI), 
				collision, 
				type
				));
		}
	}
	else
	{
		std::cout << "ERROR::TILEMAP::COULD NOT LOAD FROM FILE::FILENAME: " << file_name << "\n";
	}

	in_file.close();

	std::cout << "loaded the map" << "\n";
}

void TileMap::setMapType(const std::string map_type)
{
	this->mapType = map_type;
}

void TileMap::updateCollision(Entity* entity, const float& delatTime)
{
	//Checking collision of world bounds
	if (entity->getPosition().x < 0.f)
	{
		entity->setPosition(0.f, entity->getPosition().y);
		entity->stopVelocityX();
	}
	else if (entity->getPosition().x + entity->getGlobalBounds().width > this->maxSizeWorldF.x)
	{
		entity->setPosition(this->maxSizeWorldF.x - entity->getGlobalBounds().width, entity->getPosition().y);
		entity->stopVelocityX();
	}
	if (entity->getPosition().y < 0.f)
	{
		entity->setPosition(entity->getPosition().x, 0.f);
		entity->stopVelocityY();
	}
	else if (entity->getPosition().y + entity->getGlobalBounds().height > this->maxSizeWorldF.y)
	{
		entity->setPosition(entity->getPosition().x, this->maxSizeWorldF.y - entity->getGlobalBounds().height);
		entity->stopVelocityY();
	}

	//Checking collision with tiles using culling (only tiles around player)
	this->layer = 0;

	this->fromX = entity->getGridPosition(this->gridSizeI).x - 1;
	if (this->fromX < 0)
		this->fromX = 0;
	else if (this->fromX > this->maxSizeWorldGrid.x)
		this->fromX = maxSizeWorldGrid.x;

	this->toX = entity->getGridPosition(this->gridSizeI).x + 3;
	if (this->toX < 0)
		this->toX = 0;
	else if (this->toX > this->maxSizeWorldGrid.x)
		this->toX = maxSizeWorldGrid.x;

	this->fromY = entity->getGridPosition(this->gridSizeI).y - 1;
	if (this->fromY < 0)
		this->fromY = 0;
	else if (this->fromY > this->maxSizeWorldGrid.y)
		this->fromY = maxSizeWorldGrid.y;

	this->toY = entity->getGridPosition(this->gridSizeI).y + 3;
	if (this->toY < 0)
		this->toY = 0;
	else if (this->toY > this->maxSizeWorldGrid.y)
		this->toY = maxSizeWorldGrid.y;

	for (int x = this->fromX; x < this->toX; x++)
	{
		for (int y = this->fromY; y < this->toY; y++)
		{
			for (size_t k = 0; k < this->map[x][y][this->layer].size(); k++)
			{
				sf::FloatRect playerBounds = entity->getGlobalBounds();
				sf::FloatRect wallBounds = this->map[x][y][this->layer][k]->getGlobalBounds();
				sf::FloatRect nextPositionBounds = entity->getNextPositionBounds(delatTime);

				if (this->map[x][y][this->layer][k]->getCollision() &&
					this->map[x][y][this->layer][k]->intersects(nextPositionBounds))
				{

					////Bottom collision
					if (playerBounds.top < wallBounds.top
						&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
						&& playerBounds.left < wallBounds.left + wallBounds.width
						&& playerBounds.left + playerBounds.width > wallBounds.left)
					{
						entity->stopVelocityY();
						entity->setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
					}
					//Top collision
					else if (playerBounds.top > wallBounds.top
						&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
						&& playerBounds.left < wallBounds.left + wallBounds.width
						&& playerBounds.left + playerBounds.width > wallBounds.left)
					{
						entity->stopVelocityY();
						entity->setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
					}
					//Right collision
					if (playerBounds.left < wallBounds.left
						&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
						&& playerBounds.top < wallBounds.top + wallBounds.height
						&& playerBounds.top + playerBounds.height > wallBounds.top)
					{
						entity->stopVelocityX();
						entity->setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
					}
					//Left collision
					else if (playerBounds.left > wallBounds.left
						&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
						&& playerBounds.top < wallBounds.top + wallBounds.height
						&& playerBounds.top + playerBounds.height > wallBounds.top)
					{
						entity->stopVelocityX();
						entity->setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
					}
				}
			}
			
			
		}
	}
}

void TileMap::update()
{
	 
}

void TileMap::render(sf::RenderTarget& target, const sf::Vector2i& gridPosition,
	sf::Shader* shader, const sf::Vector2f playerPos, const bool show_hitbox)
{
	this->layer = 0;

	this->fromX = gridPosition.x - 19;
	if (this->fromX < 0)
		this->fromX = 0;
	else if (this->fromX > this->maxSizeWorldGrid.x)
		this->fromX = maxSizeWorldGrid.x;

	this->toX = gridPosition.x + 20;
	if (this->toX < 0)
		this->toX = 0;
	else if (this->toX > this->maxSizeWorldGrid.x)
		this->toX = maxSizeWorldGrid.x;

	this->fromY = gridPosition.y - 11;
	if (this->fromY < 0)
		this->fromY = 0;
	else if (this->fromY > this->maxSizeWorldGrid.y)
		this->fromY = maxSizeWorldGrid.y;

	this->toY = gridPosition.y + 12;
	if (this->toY < 0)
		this->toY = 0;
	else if (this->toY > this->maxSizeWorldGrid.y)
		this->toY = maxSizeWorldGrid.y;


	for (int x = this->fromX; x < this->toX; x++)
	{
		for (int y = this->fromY; y < this->toY; y++)
		{
			for (size_t k = 0; k < this->map[x][y][this->layer].size(); k++)
			{
				//If the tile should be on top (for example a tree or something)
				if (this->map[x][y][this->layer][k]->getType() == TileTypes::ONTOP) 
				{
					this->deferredRenderStack.push(this->map[x][y][this->layer][k]);
				}
				else 
				{
					if(shader)
						this->map[x][y][this->layer][k]->render(target, shader, playerPos);
					else
						this->map[x][y][this->layer][k]->render(target);
				}
				
				if (this->map[x][y][this->layer][k]->getCollision())
				{
					this->collisionBox.setPosition(this->map[x][y][this->layer][k]->getPosition());
					if(show_hitbox)
						target.draw(this->collisionBox);
				}
			}
				
		}
	}
}

void TileMap::renderDeferred(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f playerPos)
{
	while (!this->deferredRenderStack.empty())
	{
		if(shader)
			deferredRenderStack.top()->render(target, shader, playerPos);
		else
			deferredRenderStack.top()->render(target);
		deferredRenderStack.pop();
	}
}

