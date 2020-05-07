#pragma once
class AttributeComponent
{
public:	
	//Leveling variables
	unsigned level; // current level
	unsigned exp; // amount of current xp
	unsigned expNext; // Amount of exp needed for next level
	unsigned attributePoints; //amount of AP to use the buy attributes

	//Attributes variables
	unsigned strength; // damage modifier
	unsigned vitality; // health modifier
	unsigned dexterity; // speed of weapons and accuracy
	unsigned agility; // speed of character
	unsigned intelligence; // magic modifier
	/* myabe wisdom and charisma too?*/

	//Stats
	unsigned health;

	//Constructor/Destructor
	AttributeComponent();
	virtual ~AttributeComponent();

	//Functions

};

