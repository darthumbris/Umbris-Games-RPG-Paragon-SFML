#include "AnimationComponent.hpp"


//Constructor/Destructor
AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet)
	: sprite(sprite), textureSheet(texture_sheet), lastAnimation(nullptr)
{

}

AnimationComponent::~AnimationComponent()
{
	for (auto& i : this->animations)
	{
		delete i.second;
	}
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

void AnimationComponent::play(const std::string key, const float& deltaTime)
{
	if (this->lastAnimation != this->animations[key])
	{
		if(this->lastAnimation == nullptr)
			this->lastAnimation = this->animations[key];
		else 
		{
			this->lastAnimation->reset();
			this->lastAnimation = this->animations[key];
		}
	}

	this->animations[key]->play(deltaTime);
}

void AnimationComponent::play(const std::string key, const float& deltaTime,
	const float& modifier, const float& modifier_max)
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

	this->animations[key]->play(deltaTime, abs(modifier / modifier_max));
}


