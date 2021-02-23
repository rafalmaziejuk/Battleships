#pragma once

#include <string>

#include <SFML/Graphics.hpp>

class TextBox
{
private:
	sf::Text mDrawnText;

private:
	std::string mEnteredText;
	uint8_t mMaxSymbols;

public:
	TextBox(void);
	TextBox(sf::Vector2f position, float boxWidth, unsigned int fontSize, const sf::Font &font, uint8_t maxSymbols);
	~TextBox(void);

	void enter_symbol(char symbol);
	void delete_symbol(void);
	void draw(sf::RenderWindow *window) const;
};