#include "InputBox.h"
#include "Utility.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

namespace GUI
{
	InputBox::InputBox(void) :
		Widget(),
		mEnteredText(),
		mMaxSymbols(0),
		mIsTextSet(false)
	{

	}

	InputBox::InputBox(	sf::Vector2f position,
						sf::Vector2i size,
						const sf::Font &font,
						uint8_t fontSize,
						uint8_t maxSymbols) :
		Widget(Utility::to_vector2i(position), size, std::string(), font, fontSize),
		mEnteredText(),
		mMaxSymbols(maxSymbols),
		mIsTextSet(false)
	{
		
	}

	InputBox::~InputBox(void)
	{

	}

	void InputBox::enter_symbol(char symbol)
	{
		if (mEnteredText.length() < mMaxSymbols)
		{
			mEnteredText += symbol;
			set_text(mEnteredText);
		}

		if (!mIsTextSet)
		{
			set_text_position();
			mIsTextSet = true;
		}
	}

	void InputBox::delete_symbol(void)
	{
		if (mEnteredText.length() > 0)
		{
			mEnteredText.erase(mEnteredText.length() - 1, 1);
			set_text(mEnteredText);
		}
	}

	void InputBox::draw(sf::RenderWindow *window) const
	{
		Widget::draw(window);
	}

	void InputBox::update(sf::Vector2i mousePosition)
	{
		return;
	}

	void InputBox::handle_event(const sf::Event &event)
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
							select();
						else
							deselect();
					}

					break;
				}

				case sf::Event::TextEntered:
				{
					if (event.text.unicode < 128 && is_selected())
					{
						switch (event.text.unicode)
						{
							case 8:
								delete_symbol();
								break;

							default:
							{
								if ((event.text.unicode >= '0' && event.text.unicode <= '9') || event.text.unicode == '.')
									enter_symbol(static_cast<char>(event.text.unicode));

								break;
							}	
						}
					}
				}
			}
		}
	}
}