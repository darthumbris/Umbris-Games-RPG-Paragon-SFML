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
	int strength; // damage modifier
	int vitality; // health modifier
	int dexterity; // speed of weapons and accuracy
	int agility; // speed of character
	int intelligence; // magic modifier
	/* myabe wisdom and charisma too?*/

	//Stats
	int hp;
	int hpMax;
	int physicalDamageMin;
	int physicalDamageMax;
	int magicalDamageMin;
	int magicalDamageMax;
	int accuracy;
	int defence;
	int luck; //magic accuracy basically

	//Constructor/Destructor
	AttributeComponent(unsigned level);
	virtual ~AttributeComponent();

	//Functions
	std::string debugPrint() const;

	void gainXp(const unsigned exp);

	void updateStats(const bool reset);
	void UpdateLevel();

	void update();
};

