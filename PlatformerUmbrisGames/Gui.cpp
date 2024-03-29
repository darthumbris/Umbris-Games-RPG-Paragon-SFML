#include "stdafx.h"
#include "Gui.hpp"

using namespace gui;

const float gui::p2pX(const float percentage, const sf::VideoMode& vm)
{
	// percentage to pixel conversion for the x coordinate relative to current resolution
	return std::floor(static_cast<float>(vm.width) * (percentage / 100.f));
}

const float gui::p2pY(const float percentage, const sf::VideoMode& vm)
{
	// percentage to pixel conversion for the y coordinate relative to current resolution
	return std::floor(static_cast<float>(vm.height) * (percentage / 100.f));
}

const unsigned gui::calcCharSize(const sf::VideoMode& vm, const unsigned modifier)
{
	//Calculates the charactersize of text using the current resolution and a constant
	return static_cast<unsigned>((vm.width + vm.height) / modifier);
}

Button::Button(float x, float y, float width, float height, 
	sf::Font* font,	std::string text, unsigned character_size,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color, 
	sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
	sf::Color outline_idle_color, sf::Color outline_hover_color, sf::Color outline_active_color,
	short unsigned id)
{
	this->buttonState = BTN_IDLE;
	this->id = id;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(idle_color);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(outline_idle_color);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(text_idle_color);
	this->text.setCharacterSize(character_size);
	//int (x) en int(y) voorkomt blurry text
	/*this->text.setPosition(
		static_cast<int>(this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f),
		static_cast<int>(this->shape.getPosition().y )
	);*/

	// centre alignment id = 0
	if (this->id == 0)
	{
		this->text.setPosition(
			this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
			this->shape.getPosition().y
		);
	}
	else if(this->id == 1)
	{
		this->text.setPosition(
			this->shape.getPosition().x , this->shape.getPosition().y);
	}
	else
	{
		this->text.setPosition(
			this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
			this->shape.getPosition().y
		);
	}
	

	

	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textActiveColor = text_active_color;

	this->idleColor = idle_color;
	this->hoverColor = hover_color;
	this->activeColor = active_color;

	this->outlineIdleColor = outline_idle_color;
	this->outlineHoverColor = outline_hover_color;
	this->outlineActiveColor = outline_active_color;

	
}

Button::~Button()
{

}


//Accessors
const bool Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
		return true;

	return false;
}

const std::string gui::Button::getText() const
{
	return this->text.getString();
}

const short unsigned& gui::Button::getId() const
{
	return this->id;
}


//Modifier
void gui::Button::setText(const std::string text)
{
	this->text.setString(text);
}

void gui::Button::setId(const short unsigned id)
{
	this->id = id;
}

//Functions
void Button::update(const sf::Vector2i& mousePosWindow)
{
	/*update the booleans for hover and pressed/active */
	
	//Idle
	this->buttonState = BTN_IDLE;

	//Hover
	if (this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
	{
		this->buttonState = BTN_HOVER;

		//Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}

	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		this->text.setFillColor(this->textIdleColor);
		this->shape.setOutlineColor(this->outlineIdleColor);
		break;

	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->textHoverColor);
		this->shape.setOutlineColor(this->outlineHoverColor);
		break;

	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->text.setFillColor(this->textActiveColor);
		this->shape.setOutlineColor(this->outlineActiveColor);
		break;

	default:
		//Als er een Error is
		this->shape.setFillColor(sf::Color::Red);
		this->text.setFillColor(sf::Color::Blue);
		this->shape.setOutlineColor(sf::Color::Green);
		break;
	}
}

void Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);

}


//DropDownList===========================================================================================

//Constructor/Destructor
DropDownList::DropDownList(float x, float y, float width, float height , unsigned char_size, 
	sf::Font& font, std::string list[], 
	unsigned nrOfElements, unsigned default_index)
	: font(font) , showList(false) , inputTimeMax(1.f), inputTime(0.f)
{
	//Unsigned nrOfElements = sizeof(list) / sizeof(std::string);

	this->activeElement = new Button(x, y, width, height,
		&this->font, list[default_index], char_size,
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(120, 120, 120, 50),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
		sf::Color(20, 20, 20, 200), sf::Color(100, 100, 100, 200), sf::Color(120, 120, 120, 200)
		);

	for (unsigned i = 0; i < nrOfElements; i++)
	{
		short unsigned id_temp = static_cast<short unsigned>(i);
		this->list.push_back(
			new Button(
				x, y + ((i+1) * height), width, height,
				&this->font, list[i], char_size,
				sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 255), sf::Color(120, 120, 120, 50),
				sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
				sf::Color(20, 20, 20, 0), sf::Color(100, 100, 100, 200), sf::Color(120, 120, 120, 0),
				id_temp
			)
		);
	}
}

DropDownList::~DropDownList()
{
	delete this->activeElement;

	for (size_t i = 0; i < this->list.size(); i++)
	{
		delete this->list[i];
	}
		
}

//Accessor
const bool gui::DropDownList::getInputTime()
{
	if (this->inputTime >= this->inputTimeMax)
	{
		this->inputTime = 0.f;
		return true;
	}
	return false;
}

const unsigned short& gui::DropDownList::getActiveElementId() const
{
	return this->activeElement->getId();
}

//Functions


void gui::DropDownList::updateInputTime(const float& deltaTime)
{
	if (this->inputTime < this->inputTimeMax)
		this->inputTime += 10.f * deltaTime;
}

void DropDownList::update(const sf::Vector2i& mousePosWindow, const float& deltaTime)
{
	this->updateInputTime(deltaTime);

	this->activeElement->update(mousePosWindow);

	//Show and Hide the list
	if (this->activeElement->isPressed() && this->getInputTime())
	{
		if (this->showList)
			this->showList = false;
		else
			this->showList = true;
	}

	if (this->showList)
	{
		for (auto& i : this->list)
		{
			i->update(mousePosWindow);

			if (i->isPressed() && this->getInputTime())
			{
				this->showList = false;
				this->activeElement->setText(i->getText());
				this->activeElement->setId(i->getId());
			}
		}
	}
}

void DropDownList::render(sf::RenderTarget& target)
{
	this->activeElement->render(target);
	
	if (this->showList)
	{
		for (auto& i : this->list)
		{
			i->render(target);
		}
	}
}

//Texture Selector===============================================================================


//Constructor/Destructor
TextureSelector::TextureSelector(float x, float y, float width, float height, float gridSize, 
	const sf::Texture* texture_sheet, sf::Font& font, std::string text, sf::VideoMode vm)
	: inputTimeMax(2.f), inputTime(0.f)
{
	this->active = false;
	this->gridSize = gridSize;
	this->hidden = false;
	float offset = gridSize;
	
	this->bounds.setSize(sf::Vector2f(width, height));
	this->bounds.setPosition(x + offset, y);
	this->bounds.setFillColor(sf::Color(50, 50, 50, 100));
	this->bounds.setOutlineThickness(1.f);
	this->bounds.setOutlineColor(sf::Color(255, 255, 255, 200));

	this->sheet.setTexture(*texture_sheet);
	this->sheet.setPosition(x + offset, y);

	//make sure that the texture doesn't get outside of the bounds
	if (this->sheet.getGlobalBounds().width > this->bounds.getGlobalBounds().width)
	{
		this->sheet.setTextureRect(sf::IntRect(0, 0,
			static_cast<int>(this->bounds.getGlobalBounds().width), static_cast<int>(this->sheet.getGlobalBounds().height)));
	}
	if (this->sheet.getGlobalBounds().height > this->bounds.getGlobalBounds().height)
	{
		this->sheet.setTextureRect(sf::IntRect(0, 0,
			static_cast<int>(this->sheet.getGlobalBounds().width), static_cast<int>(this->bounds.getGlobalBounds().height)));
	}

	this->selector.setPosition(x + offset, y);
	this->selector.setSize(sf::Vector2f(gridSize, gridSize));
	this->selector.setFillColor(sf::Color::Transparent);
	this->selector.setOutlineThickness(1.f);
	this->selector.setOutlineColor(sf::Color::Red);

	this->textureRect.width = static_cast<int>(gridSize);
	this->textureRect.height = static_cast<int>(gridSize);

	

	this->hide_btn = new gui::Button(
		gui::p2pX(.78f, vm), y, gui::p2pX(3.125f, vm), gui::p2pY(5.56f, vm),
		&font, text, gui::calcCharSize(vm, 80),
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(120, 120, 120, 50),
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 200), sf::Color(20, 20, 20, 50),
		sf::Color(170, 170, 170, 200), sf::Color(200, 200, 200, 200), sf::Color(20, 20, 20, 50));
}

TextureSelector::~TextureSelector()
{
	delete this->hide_btn;
}

//Accessors
const bool& gui::TextureSelector::getActive() const
{
	return this->active;
}

const sf::IntRect& gui::TextureSelector::getTextureRect() const
{
	return this->textureRect;
}

const bool gui::TextureSelector::getInputTime()
{
	if (this->inputTime >= this->inputTimeMax)
	{
		this->inputTime = 0.f;
		return true;
	}
	return false;
}


//Functions
void gui::TextureSelector::updateInputTime(const float& deltaTime)
{
	if (this->inputTime < this->inputTimeMax)
		this->inputTime += 10.f * deltaTime;
}

void gui::TextureSelector::update(const sf::Vector2i& mousePosWindow, const float& deltaTime)
{
	updateInputTime(deltaTime);
	this->hide_btn->update(mousePosWindow);

	if (this->hide_btn->isPressed() && this->getInputTime())
	{
		if (this->hidden)
			this->hidden = false;
		else
			this->hidden = true;
	}
	
	if (!this->hidden)
	{
		if (this->bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
			this->active = true;
		else
			this->active = false;

		if (this->active)
		{
			this->mousePosGrid.x = (mousePosWindow.x - static_cast<int>(this->bounds.getPosition().x)) / static_cast<unsigned>(this->gridSize);
			this->mousePosGrid.y = (mousePosWindow.y - static_cast<int>(this->bounds.getPosition().y)) / static_cast<unsigned>(this->gridSize);

			this->selector.setPosition(
				this->bounds.getPosition().x + this->mousePosGrid.x * this->gridSize,
				this->bounds.getPosition().y + this->mousePosGrid.y * this->gridSize
			);

			//Update texture rectangle
			this->textureRect.left = static_cast<int>(this->selector.getPosition().x - this->bounds.getPosition().x);
			this->textureRect.top = static_cast<int>(this->selector.getPosition().y - this->bounds.getPosition().y);
		}
	}
}

void gui::TextureSelector::render(sf::RenderTarget& target)
{
	if (!this->hidden)
	{
		target.draw(this->bounds);
		target.draw(this->sheet);

		if (this->active)
			target.draw(this->selector);
	}
	this->hide_btn->render(target);
}
