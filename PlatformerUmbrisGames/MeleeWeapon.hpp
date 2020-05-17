#pragma once

#include "Item.hpp"
class Item;

class MeleeWeapon :
	public Item
{
private:

protected:
	sf::Sprite weaponSprite;
	sf::Texture weaponTexture;

	int damageMin;
	int damageMax;

public:
	MeleeWeapon();
	virtual ~MeleeWeapon();

	//functions
	virtual void update(const sf::Vector2f mouse_pos_view, const sf::Vector2f center) = 0;
	virtual void render(sf::RenderTarget& target, sf::Shader* shader) = 0;
};

