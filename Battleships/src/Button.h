#pragma once

#include "Widget.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include <functional>

namespace GUI
{
	class Button : public Widget
	{
	private:
		sf::Sprite mSprite;
		sf::Text mDrawnText;

	private:
		std::function<void(void)> mCallback;
		uint8_t mDefaultFontSize;
		bool mIsTextDisabled;

	public:
		Button(void);
		Button(	sf::Vector2f position,
				const sf::Texture &texture = sf::Texture(),
				const std::string &text = std::string(),
				uint8_t fontSize = 0,
				const sf::Font &font = sf::Font(),
				sf::Color color = sf::Color::White);
		
		virtual ~Button();

		inline void set_callback(std::function<void(void)> callback)
		{
			mCallback = std::move(callback);
		}

		virtual void draw(sf::RenderWindow *window) const override;
		virtual void update(sf::Vector2i mousePosition) override;
		virtual void on_click(bool clickedOn) override;
	};
}