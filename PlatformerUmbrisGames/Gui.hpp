#pragma once


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

enum button_states{BTN_IDLE =0, BTN_HOVER, BTN_ACTIVE};

namespace gui
{
	class Button
	{
	private:
		//Variables
		short unsigned buttonState;

		sf::RectangleShape shape;
		sf::Font* font;
		sf::Text text;

		sf::Color textIdleColor;
		sf::Color textHoverColor;
		sf::Color textActiveColor;

		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;



	public:
		Button(float x, float y, float width, float height,
			sf::Font* font, std::string text, unsigned character_size,
			sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
			sf::Color idle_color, sf::Color hover_color, sf::Color active_color);
		~Button();

		//Accessors
		const bool isPressed() const;
		const std::string& getText() const;

		//Modifiers
		void setText(const std::string text);

		//Functions
		void update(const sf::Vector2f& mousePos);
		void render(sf::RenderTarget& target);
	};

	class DropDownList
	{
	private:
		float inputTime;
		float inputTimeMax;

		sf::Font& font;
		gui::Button* activeElement;
		std::vector<gui::Button*> list;
		bool showList;

	public:
		//Constructor destructor
		DropDownList(float x, float y, float width, float height, sf::Font& font, std::string list[], unsigned nrOfElements, unsigned default_index);
		~DropDownList();

		//Accessor
		const bool getInputTime();

		//Functions
		void updateInputTime(const float& deltaTime);
		void update(const sf::Vector2f& mousePos, const float& deltaTime);
		void render(sf::RenderTarget& target);
	};

}