#include "Button.h"
#include "Utility.h"

namespace GUI
{


	Button::Button(void) :
		Widget(),
		mSprite(),
		mDrawnText(),
		mCallback(),
		mDefaultFontSize(0),
		mIsTextDisabled(false)
	{

	}

	Button::Button(sf::Vector2f position,
						const sf::Texture &texture,
						const std::string &text,
						uint8_t fontSize,
						const sf::Font &font,
						sf::Color color) :
						Widget(Utility::to_vector2i(position), Utility::to_vector2i(texture.getSize())),
						mSprite(texture),
						mDrawnText(text, font, fontSize),
						mCallback(),
						mDefaultFontSize(fontSize),
						mIsTextDisabled(text.empty())
	{
		mSprite.setPosition(position);

		sf::FloatRect bounds = mSprite.getLocalBounds();
		mDrawnText.setPosition(position.x + bounds.width / 2.0f, position.y + bounds.height / 2.0f);
		Utility::align_text_center(mDrawnText);
		mDrawnText.setFillColor(color);
	}

	Button::~Button()
	{
	
	}

	void Button::draw(sf::RenderWindow *window) const
	{
		window->draw(mSprite);

		if (!mIsTextDisabled)
			window->draw(mDrawnText);
	}

	void Button::update(sf::Vector2i mousePosition)
	{
		if (mIsTextDisabled)
		{
			if (is_mouse_over(mousePosition) == true)
				mSprite.setScale(1.05f, 1.05f);
			else
				mSprite.setScale(1.00f, 1.00f);
		}
		else
		{
			if (is_mouse_over(mousePosition) == true)
				mDrawnText.setCharacterSize(mDefaultFontSize + 2);
			else
				mDrawnText.setCharacterSize(mDefaultFontSize);

			Utility::align_text_center(mDrawnText);
		}
	}

	void Button::on_click(bool clickedOn)
	{
		mCallback();
	}

}
