#include "InputBox.h"
#include "Utility.h"

GUI::InputBox::InputBox(void) :
	mDrawnText(),
	mEnteredText(),
	mMaxSymbols(0),
	mIsFocused(false)
{

}

GUI::InputBox::InputBox(sf::Vector2f position, sf::Vector2i size, const sf::Font &font, uint8_t fontSize, uint8_t maxSymbols) :
	Widget(Utility::to_vector2i(position), size),
	mDrawnText(std::string(), font, fontSize),
	mEnteredText(),
	mMaxSymbols(maxSymbols),
	mIsFocused(false)
{
	mDrawnText.setPosition(position.x + 5.0f, position.y + 9.0f);
	mDrawnText.setFillColor(sf::Color::Black);
}

GUI::InputBox::~InputBox(void)
{

}

void GUI::InputBox::set_entered_text(std::string text)
{
	mEnteredText = text;
	mDrawnText.setString(mEnteredText);
}

void GUI::InputBox::enter_symbol(char symbol)
{
	if (mEnteredText.length() < mMaxSymbols)
	{
		mEnteredText += symbol;
		mDrawnText.setString(mEnteredText);
	}
}

void GUI::InputBox::delete_symbol(void)
{
	if (mEnteredText.length() > 0)
	{
		mEnteredText.erase(mEnteredText.length() - 1, 1);
		mDrawnText.setString(mEnteredText);
	}
}

bool GUI::InputBox::is_focused(void) const
{
	return mIsFocused;
}

std::string GUI::InputBox::get_text(void) const
{
	return mEnteredText;
}

void GUI::InputBox::draw(sf::RenderWindow *window) const
{
	window->draw(mDrawnText);
}

void GUI::InputBox::update(sf::Vector2i mousePosition)
{
	return;
}

void GUI::InputBox::on_click(bool clickedOn)
{
	if (clickedOn)
		mIsFocused = true;
	else
		mIsFocused = false;
}