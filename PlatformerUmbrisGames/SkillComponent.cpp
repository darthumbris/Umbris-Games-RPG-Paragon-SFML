#include "stdafx.h"
#include "SkillComponent.hpp"

SkillComponent::SkillComponent()
{
	this->skills.push_back(Skill(SKILLS::HEALTH));
	this->skills.push_back(Skill(SKILLS::ATTACK));
	this->skills.push_back(Skill(SKILLS::ACCURACY));

	/*These are example skills for now, still have to determine which skills
	to use here*/
}

SkillComponent::~SkillComponent()
{

}

//Accessor
const int SkillComponent::getSkillLevel(const int skill) const
{
	if (this->skills.empty() || skill < 0 || skill >= static_cast<int>(this->skills.size()))
	{
		throw("ERROR::SKILL COMPONENT::GETSKILLLEVEL::SKILL DOES NOT EXIST: " + skill);
	}
	else
	{
		return this->skills[skill].getLevel();
	}
}

//Functions
const void SkillComponent::gainExp(const int skill, const int exp)
{
	if (this->skills.empty() || skill < 0 || skill >= static_cast<int>(this->skills.size()))
	{
		throw("ERROR::SKILL COMPONENT::GAINEXP::SKILL DOES NOT EXIST: " + skill);
	}
	else
	{
		this->skills[skill].gainExp(exp);
	}
}
