#include "Widget.h"

#include <SFML/Graphics/RenderWindow.hpp>

namespace GUI
{
	Widget::Widget(void) :
		mTriggerArea(),
		mText(),
		mIsTextVisible(true),
		mIsSelected(false),
		mIsActive(true),
		mDefaultFontSize(0),
		mAlignMode(AlignOptions::CENTER)
	{
		mText.setFillColor(sf::Color::Black);
	}

	Widget::Widget(sf::Vector2i position, sf::Vector2i size, const std::string &text, const sf::Font &font, uint8_t fontSize) :
		mTriggerArea(position, size),
		mText(text, font, fontSize),
		mIsTextVisible(true),
		mIsSelected(false),
		mIsActive(true),
		mDefaultFontSize(fontSize),
		mAlignMode(AlignOptions::CENTER)
	{
		mText.setFillColor(sf::Color::Black);
	}

	Widget::~Widget(void)
	{

	}

	void Widget::draw(sf::RenderWindow *window) const
	{
		if (mIsTextVisible)
			window->draw(mText);
	}
}