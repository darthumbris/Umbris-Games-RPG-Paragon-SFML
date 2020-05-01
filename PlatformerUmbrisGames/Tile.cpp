#include "stdafx.h"
#include "Tile.hpp"


//Constructor/Destructor
Tile::Tile()
{
}

Tile::Tile(float x, float y, float gridSizeF)
{
	this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	this->shape.setFillColor(sf::Color::Green);
	this->shape.setPosition(x, y);
}

Tile::~Tile()
{

}

//Functions
void Tile::update()
{

}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
