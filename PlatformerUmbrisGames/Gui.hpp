#pragma once

enum button_states{BTN_IDLE =0, BTN_HOVER, BTN_ACTIVE};

namespace gui
{
	const float p2pX(const float percentage, const sf::VideoMode& vm);
	const float p2pY(const float percentage, const sf::VideoMode& vm);
	const unsigned calcCharSize(const sf::VideoMode& vm, const unsigned modifier);

	class Button
	{
	private:
		//Variables
		short unsigned buttonState;
		short unsigned id;

		sf::RectangleShape shape;
		sf::Font* font;
		sf::Text text;

		sf::Color textIdleColor;
		sf::Color textHoverColor;
		sf::Color textActiveColor;

		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;

		sf::Color outlineIdleColor;
		sf::Color outlineHoverColor;
		sf::Color outlineActiveColor;

	public:
		Button(float x, float y, float width, float height,
			sf::Font* font, std::string text, unsigned character_size,
			sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
			sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
			sf::Color outline_idle_color = sf::Color::Transparent, sf::Color outline_hover_color = sf::Color::Transparent, sf::Color outline_active_color = sf::Color::Transparent,
			short unsigned id = 0);
		~Button();

		//Accessors
		const bool isPressed() const;
		const std::string getText() const;
		const short unsigned& getId() const;

		//Modifiers
		void setText(const std::string text);
		void setId(const short unsigned id);

		//Functions
		void update(const sf::Vector2i& mousePosWindow);
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
		DropDownList(float x, float y, float width, float height, unsigned char_size, sf::Font& font, std::string list[], unsigned nrOfElements, unsigned default_index);
		~DropDownList();

		//Accessor
		const bool getInputTime();
		const unsigned short& getActiveElementId() const;

		//Functions
		void updateInputTime(const float& deltaTime);
		void update(const sf::Vector2i& mousePosWindow, const float& deltaTime);
		void render(sf::RenderTarget& target);
	};

	class TextureSelector
	{
	private:
		//Variables
		float inputTime;
		const float inputTimeMax;
		float gridSize;

		bool active; // used to see if the mouse is within the selector bounds
		bool hidden;
		Button* hide_btn;

		sf::RectangleShape bounds; //Box where the texturesheet is showed in
		sf::Sprite sheet; //The tilesheet
		sf::RectangleShape selector; //displays what tile is selected within bounds
		sf::Vector2u mousePosGrid; //position of the mouse according to the grid
		sf::IntRect textureRect; // For determining what part of the texture gets selected

	public:
		TextureSelector(float x, float y, float width, float height, float gridSize, 
			const sf::Texture* texture_sheet, sf::Font& font, std::string text);
		~TextureSelector();

		//Accessors
		const bool& getActive() const;
		const sf::IntRect& getTextureRect() const;
		const bool getInputTime();

		//Functions
		void updateInputTime(const float& deltaTime);
		void update(const sf::Vector2i& mousePosWindow, const float& deltaTime);
		void render(sf::RenderTarget &target);
	};
}