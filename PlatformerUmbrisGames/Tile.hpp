#pragma once

enum TileTypes {DEFAULT = 0, DAMAGING, SLOWING, ONTOP};

class Tile
{
private:

protected:
	sf::Sprite shape;
	sf::IntRect texRect;
	short type; //dissapearin/ slowing / damaging etc
	bool collision; // if a tile is pass through or not (ie air you can go through walls not)

public:
	//Constructor/Destructor
	Tile();
	Tile(int grid_x, int grid_y, float gridSizeF,
		const sf::Texture& texture, const sf::IntRect& texture_rect,
		bool collision = false, short type = TileTypes::DEFAULT);
	virtual ~Tile();

	//Accessors
	const bool getCollision() const;
	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	const short& getType() const;
	const sf::IntRect& getRect() const;

	//Functions
	const bool intersects(const sf::FloatRect bounds) const;
	const std::string getAsString() const;

	void update();
	void render(
		sf::RenderTarget& target, 
		sf::Shader* shader = nullptr, 
		const sf::Vector2f playerPos = sf::Vector2f());
};

