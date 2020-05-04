#include "stdafx.h"
#include "TileMap.hpp"

void TileMap::clear()
{
	for (size_t x = 0; x < this->mapMaxSize.x; x++)
	{
		for (size_t y = 0; y < this->mapMaxSize.y; y++)
		{
			for (size_t z = 0; z < this->layers; z++)
			{
				delete this->map[x][y][z];
				this->map[x][y][z] = nullptr;
			}
			this->map[x][y].clear();
		}
		this->map[x].clear();
	}
	this->map.clear();
}

//Constructor/Destructor
TileMap::TileMap(float gridSize, unsigned width, unsigned height, std::string texture_file)
{
	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->mapMaxSize.x = width;
	this->mapMaxSize.y = height;
	this->layers = 1;
	this->textureFile = texture_file;

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

	if(!this->tileSheet.loadFromFile(texture_file))
		std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILE TEXTURESHEET FILENAME: " << texture_file << "\n";


}

TileMap::~TileMap()
{
	this->clear();
}

//Accessors
const sf::Texture* TileMap::getTileSheet() const
{
	return &this->tileSheet;
}

//Functions
void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z, 
	const sf::IntRect& texture_rect, const bool& collision, const short& type)
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
			this->map[x][y][z] = new Tile(x, y, this->gridSizeF, this->tileSheet, texture_rect, collision, type);
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
		out_file << this->mapMaxSize.x << " " << this->mapMaxSize.y << "\n"
		<< this->gridSizeU << "\n"
		<< this->layers << "\n"
		<< this->textureFile << "\n";

		for (size_t x = 0; x < this->mapMaxSize.x; x++)
		{
			for (size_t y = 0; y < this->mapMaxSize.y; y++)
			{
				for (size_t z = 0; z < this->layers; z++)
				{
					if(this->map[x][y][z])
						out_file << x << " " << y << " " << z << " " << 
						this->map[x][y][z]->getAsString() 
						<< " "; // Make sure this last space is not saved
				}
			}
		}
	}
	else
	{
		std::cout << "ERROR::TILEMAP::COULD NOT SAVE TO FILE::FILENAME: " << file_name << "\n";
	}

	out_file.close();
}

void TileMap::loadFromFile(const std::string file_name)
{
	std::ifstream in_file;

	in_file.open(file_name);

	if (in_file.is_open())
	{
		sf::Vector2u size;
		unsigned gridSize = 0;
		unsigned layers = 0;
		std::string texture_file = "";
		unsigned x = 0;
		unsigned y = 0;
		unsigned z = 0;
		unsigned trX = 0; //(texture rect x)
		unsigned trY = 0;
		bool collision = false;
		short type = 0;

		//Basics
		in_file >> size.x >> size.y >> gridSize >> layers >> texture_file;
		
		//Tiles
		this->gridSizeF = static_cast<float>(gridSize);
		this->gridSizeU = gridSize;
		this->mapMaxSize.x = size.x;
		this->mapMaxSize.y = size.y;
		this->layers = layers;
		this->textureFile = texture_file;

		this->clear();

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

		if (!this->tileSheet.loadFromFile(texture_file))
			std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILE TEXTURESHEET FILENAME: " << texture_file << "\n";

		//Load all Tiles
		while (in_file >> x >> y >> z >> trX >> trY >> collision >> type)
		{
			this->map[x][y][z] = new Tile(
				x, y, 
				this->gridSizeF, 
				this->tileSheet, 
				sf::IntRect(trX, trY, this->gridSizeU, this->gridSizeU), 
				collision, 
				type
				);
		}
	}
	else
	{
		std::cout << "ERROR::TILEMAP::COULD NOT LOAD FROM FILE::FILENAME: " << file_name << "\n";
	}

	in_file.close();
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
			for (auto* z : y)
			{
				if (z != nullptr)
					z->render(target);
			}
		}
	}
}

