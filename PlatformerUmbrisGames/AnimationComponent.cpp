#include "stdafx.h"
#include "AnimationComponent.hpp"


//Constructor/Destructor
AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet)
	: sprite(sprite), textureSheet(texture_sheet), lastAnimation(nullptr), priorityAnimation(nullptr)
{

}

AnimationComponent::~AnimationComponent()
{
	for (auto& i : this->animations)
	{
		delete i.second;
	}
}

//Accessors
const bool& AnimationComponent::isDone(const std::string key) 
{
	return this->animations[key]->isDone();
}

//Functions
void AnimationComponent::addAnimation(
	const std::string key,
	float animation_timer,
	int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
{
	this->animations[key] = new Animation(
		this->sprite, this->textureSheet, 
		animation_timer, 
		start_frame_x, start_frame_y, frames_x, frames_y, width, height);
}

const bool& AnimationComponent::play(const std::string key, const float& deltaTime, const bool priority)
{
	if (this->priorityAnimation) // if there is a priority animation
	{
		if(this->priorityAnimation == this->animations[key])
		{
			if (this->lastAnimation != this->animations[key])
			{
				if (this->lastAnimation == nullptr)
					this->lastAnimation = this->animations[key];
				else
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}
			}

			//If the priority animation is done remove it
			if (this->animations[key]->play(deltaTime))
			{
				this->priorityAnimation = nullptr;
			}
		}
	}
	else //Play animation if no priority is set
	{
		//If this is a priority animation, set it
		if (priority)
		{
			this->priorityAnimation = this->animations[key];
		}

		if (this->lastAnimation != this->animations[key])
		{
			if (this->lastAnimation == nullptr)
				this->lastAnimation = this->animations[key];
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}
		}

		this->animations[key]->play(deltaTime);
	}
	
	return this->animations[key]->isDone();
}

const bool& AnimationComponent::play(const std::string key, const float& deltaTime,
	const float& modifier, const float& modifier_max, const bool priority)
{
	if (this->priorityAnimation) // if there is a priority animation
	{
		if (this->priorityAnimation == this->animations[key])
		{
			if (this->lastAnimation != this->animations[key])
			{
				if (this->lastAnimation == nullptr)
					this->lastAnimation = this->animations[key];
				else
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}
			}

			//If the priority animation is done remove it
			if (this->animations[key]->play(deltaTime, abs(modifier / modifier_max)))
			{
				this->priorityAnimation = nullptr;
			}
		}
	}
	else //Play animation if no priority is set
	{
		//If this is a priority animation, set it
		if (priority)
		{
			this->priorityAnimation = this->animations[key];
		}

		if (this->lastAnimation != this->animations[key])
		{
			if (this->lastAnimation == nullptr)
				this->lastAnimation = this->animations[key];
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}
		}

		this->animations[key]->play(deltaTime, abs(modifier / modifier_max));
	}

	return this->animations[key]->isDone();
}


