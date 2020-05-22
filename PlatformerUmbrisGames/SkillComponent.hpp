#pragma once

class SkillComponent
{
private:
	class Skill
	{
	private:
		int level;
		int levelCap;
		int exp;
		int expNext;

	public:
		Skill()	
		{
			this->level = 1;
			this->levelCap = 99;
			this->exp = 0;
			this->expNext = 100;
		}

		~Skill() {}

		//Accessors
		inline const int& getLevel() const { return this->level; }
		inline const int& getExp() const { return this->exp; }
		inline const int& getExpNext() const { return this->expNext; }

		//Modifiers
		inline void setLevel(const int level) { this->level = level; }
		inline void setLevelCap(const int level_cap) { this->levelCap = level_cap; }

		//Functions
		void gainExp(const int exp)
		{ 
			this->exp += exp;
			this->updateLevel(); 
		}

		void loseExp(const int exp)
		{
			this->exp -= exp;
		}

		void updateLevel(const bool up = true)
		{
			/*
			Either the level needs to be updated to a higher level (up = true) or the 
			skill level needs to get lowered (up = false)
			*/
			if (up)
			{
				if (this->level < this->levelCap)
				{
					while (this->exp >= this->expNext)
					{
						if (this->level < this->levelCap)
						{
							this->level++;
							
							this->expNext = std::pow(this->level, 2) + this->level * 12;
						}
						else this->exp = 0;
					}
				}
			}
			else
			{
				if (this->level > 0)
				{
					while (this->exp < 0)
					{
						if (this->level > 0)
						{
							this->level--;
							this->expNext = std::pow(this->level, 2) + this->level * 12;
						}
						else this->exp = 0;
					}
				}
			}
		}

		void update()
		{
			
		}
	};

public:
	SkillComponent();
	virtual ~SkillComponent();
};

