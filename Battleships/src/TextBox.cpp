#include "TextBox.h"

TextBox::TextBox(void) :
	mDrawnText(),
	mEnteredText(),
	mMaxSymbols(0)
{

}

TextBox::TextBox(sf::Vector2f position, float boxWidth, unsigned int fontSize, const sf::Font &font, uint8_t maxSymbols) :
	mDrawnText(),
	mEnteredText(),
	mMaxSymbols(maxSymbols)
{
	mDrawnText.setFont(font);
	mDrawnText.setCharacterSize(fontSize);
	mDrawnText.setPosition(position);
	mDrawnText.setFillColor(sf::Color::Black);
}

TextBox::~TextBox(void)
{

}

void TextBox::enter_symbol(char symbol)
{
	if (mEnteredText.length() <= mMaxSymbols)
	{
		mEnteredText += symbol;
		mDrawnText.setString(mEnteredText);
	}
}

void TextBox::delete_symbol(void)
{
	if (mEnteredText.length() > 0)
	{
		mEnteredText.erase(mEnteredText.length() - 1, 1);
		mDrawnText.setString(mEnteredText);
	}
}

void TextBox::draw(sf::RenderWindow *window) const
{
	window->draw(mDrawnText);
}