#pragma once

#include "Widget.h"
#include <SFML/Graphics/RectangleShape.hpp>

#include <string>

namespace GUI
{
	class InputBox : public Widget
	{
	private:
		std::string mEnteredText;
		uint8_t mMaxSymbols;
		bool mIsTextSet;

	private:
		void enter_symbol(char symbol);
		void delete_symbol(void);

	public:
		InputBox(void);
		InputBox(sf::Vector2f position, sf::Vector2i size, const sf::Font &font, uint8_t fontSize, uint8_t maxSymbols);
		virtual ~InputBox(void);

		virtual void draw(sf::RenderWindow *window) const;
		virtual void update(sf::Vector2i mousePosition) override;
		virtual void handle_event(const sf::Event &event) override;
	};
}