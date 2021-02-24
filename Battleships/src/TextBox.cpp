#include "TextBox.h"

TextBox::TextBox(void) :
	mHitBox(),
	mDrawnText(),
	mEnteredText(),
	mMaxSymbols(0)
{

}

TextBox::TextBox(sf::Vector2f position, sf::Vector2f size, const sf::Font &font, uint8_t maxSymbols) :
	mHitBox(),
	mDrawnText(),
	mBoxSize(size),
	mEnteredText(),
	mMaxSymbols(maxSymbols)
{
	mHitBox.setPosition(position);
	mHitBox.setSize(size);

	mDrawnText.setFont(font);
	mDrawnText.setCharacterSize(unsigned int(size.y * 0.6f));
	mDrawnText.setPosition(position + sf::Vector2f(5.0f, mHitBox.getSize().y * 0.1f));
	mDrawnText.setFillColor(sf::Color::Black);
}

TextBox::~TextBox(void)
{

}

void TextBox::set_entered_text(std::string text)
{
	mEnteredText = text;
	mDrawnText.setString(mEnteredText);
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

void TextBox::on_click(sf::Vector2i mousePosition)
{
	if (mousePosition.x > mHitBox.getPosition().x && mousePosition.x < mHitBox.getPosition().x + mHitBox.getSize().x &&
		mousePosition.y > mHitBox.getPosition().y && mousePosition.y < mHitBox.getPosition().y + mHitBox.getSize().y)
		mIsFocused = true;
	else
		mIsFocused = false;
}

bool TextBox::is_focused(void) const
{
	return mIsFocused;
}

std::string TextBox::get_text(void) const
{
	return mEnteredText;
}

void TextBox::draw(sf::RenderWindow *window) const
{
	window->draw(mDrawnText);
}