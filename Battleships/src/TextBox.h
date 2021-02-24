#pragma once

#include <string>

#include <SFML/Graphics.hpp>

class TextBox
{
private:
	sf::RectangleShape mHitBox;
	sf::Text mDrawnText;
	sf::Vector2f mBoxSize;

private:
	bool mIsFocused = false;
	std::string mEnteredText;
	uint8_t mMaxSymbols;

	//TODO(rm): Blinking cursor

public:
	TextBox(void);
	TextBox(sf::Vector2f position, sf::Vector2f size, const sf::Font &font, uint8_t maxSymbols);
	~TextBox(void);

	void enter_symbol(char symbol);
	void delete_symbol(void);
	void on_click(sf::Vector2i mousePosition);
	bool is_focused(void) const;
	std::string get_text(void) const;
	void draw(sf::RenderWindow *window) const;
};