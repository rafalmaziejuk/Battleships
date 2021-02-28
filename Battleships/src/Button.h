#pragma once

#include "Widget.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <functional>

namespace GUI
{
	class Button : public Widget
	{
	private:
		sf::Sprite mSprite;

	private:
		std::function<void(void)> mCallback;

	public:
		Button(void);
		Button(	sf::Vector2f position,
				const sf::Texture &texture,
				const std::string &text = std::string(),
				const sf::Font &font = sf::Font(),
				uint8_t fontSize = 0);
		virtual ~Button();

		inline void set_callback(std::function<void(void)> callback)
		{
			mCallback = std::move(callback);
		}

		virtual void draw(sf::RenderWindow *window) const;
		virtual void update(sf::Vector2i mousePosition) override;
		virtual bool handle_event(const sf::Event &event) override;
	};
}