#pragma once

#include "Widget.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include <string>

namespace GUI
{
	class InputBox : public Widget
	{
	private:
		sf::Text mDrawnText;

	private:
		std::string mEnteredText;
		uint8_t mMaxSymbols;
		bool mIsFocused;

	public:
		InputBox(void);
		InputBox(sf::Vector2f position, sf::Vector2i size, const sf::Font & font, uint8_t fontSize, uint8_t maxSymbols);
		virtual ~InputBox(void);

		inline bool is_mouse_over(sf::Vector2i mousePosition) const
		{
			return Widget::is_mouse_over(mousePosition);
		}

		void set_entered_text(std::string text);
		void enter_symbol(char symbol);
		void delete_symbol(void);
		bool is_focused(void) const;
		std::string get_text(void) const;

		virtual void draw(sf::RenderWindow *window) const override;
		virtual void update(sf::Vector2i mousePosition) override;
		virtual void on_click(bool clickedOn) override;
	};
}