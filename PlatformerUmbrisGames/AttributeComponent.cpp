#include "stdafx.h"
#include "AttributeComponent.hpp"

AttributeComponent::AttributeComponent(int level)
{
	this->level = level;
	this->exp = 0;
	this->expNext = static_cast<int>((50 / 3) * (pow(this->level + 1, 3) - 6 * pow(this->level + 1, 2) + ((static_cast<double>(this->level) + 1) * 17) - 12) + 100);
	this->attributePoints = 4;

	this->vitality = 1;
	this->strength = 1;
	this->dexterity = 1;
	this->agility = 1;
	this->intelligence = 1;

	this->UpdateLevel();
	this->updateStats(true);
}

AttributeComponent::~AttributeComponent()
{
}


std::string AttributeComponent::debugPrint() const
{
	std::stringstream ss;

	ss << "Level: " << this->level << "\n"
		<< "Exp: " << this->exp << "\n"
		<< "Exp next: " << this->expNext << "\n"
		<< "Attributepoints: " << this->attributePoints << "\n";
	return ss.str();
}

void AttributeComponent::gainXp(const int exp)
{
	this->exp += exp;

	this->UpdateLevel();
}

//Functions
void AttributeComponent::updateStats(const bool reset)
{
	this->hpMax				= this->vitality * 5 + this->vitality;
	this->physicalDamageMin = this->strength * 2 + this->strength / 5;
	this->physicalDamageMax = this->strength * 2 + this->strength / 3;
	this->magicalDamageMin	= this->intelligence * 2 + this->strength / 5;
	this->magicalDamageMax	= this->intelligence * 2 + this->strength / 3;
	this->accuracy			= this->dexterity * 4 + this->dexterity / 2;
	this->defence			= this->agility * 2 + this->agility / 4 + this->strength;
	this->luck				= this->intelligence * 2 + this->intelligence / 5;

	if (reset)
	{
		this->hp = this->hpMax;
	}
	
}

void AttributeComponent::UpdateLevel()
{
	while (this->exp >= this->expNext)
	{
		++this->level;
		this->exp -= this->expNext;
		this->expNext = static_cast<int>((50 / 3) * (pow(this->level, 3) - 6 * pow(this->level, 2) + (static_cast<double>(this->level) * 17) - 12) + 100);
		++this->attributePoints;
	}
}

void AttributeComponent::update()
{
	//this->UpdateLevel();
}




