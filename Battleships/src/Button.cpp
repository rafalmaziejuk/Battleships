#include "Button.h"
#include "Utility.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

namespace GUI
{
	Button::Button(void) :
		Widget(),
		mSprite(),
		mCallback()
	{

	}

	Button::Button(	sf::Vector2f position, 
					const sf::Texture &texture, 
					const std::string &text, 
					const sf::Font &font,
					uint8_t fontSize) :
		Widget(Utility::to_vector2i(position), Utility::to_vector2i(texture.getSize()), text, font, fontSize),
		mSprite(texture),
		mCallback()
	{
		change_text_visibility(!text.empty());

		if (!is_text_visible())
		{
			Utility::set_origin_to_center(mSprite);

			sf::FloatRect spriteBounds = mSprite.getLocalBounds();
			sf::Vector2f spritePosition(position.x + spriteBounds.width / 2.0f, position.y + spriteBounds.height / 2.0f);
			mSprite.setPosition(spritePosition);
		}
		else
			mSprite.setPosition(position);
	}

	Button::~Button(void)
	{
		
	}

	void Button::draw(sf::RenderWindow *window) const
	{
		if (is_active())
		{
			window->draw(mSprite);
			Widget::draw(window);
		}
	}

	void Button::update(sf::Vector2i mousePosition)
	{
		if (is_active())
		{
			if (!is_text_visible())
			{
				if (is_mouse_over(mousePosition))
					mSprite.setScale(1.05f, 1.05f);
				else
					mSprite.setScale(1.00f, 1.00f);
			}
			else
			{
				if (is_mouse_over(mousePosition))
					change_text_size(2);
				else
					change_text_size(-2);
			}
		}
	}

	bool Button::handle_event(const sf::Event &event)
	{
		if (is_active())
		{
			switch (event.type)
			{
				case sf::Event::MouseButtonReleased:
				{
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						sf::Vector2i mousePosition(event.mouseButton.x, event.mouseButton.y);

						if (is_mouse_over(mousePosition))
						{
							mCallback();
							return true;
						}
					}

					break;
				}

				default: break;
			}
		}

		return false;
	}
}