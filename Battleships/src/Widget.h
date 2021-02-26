#pragma once

#include <string>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace GUI
{
	class Widget
	{
	private:
		sf::IntRect mTriggerArea;

	protected:
		inline bool is_mouse_over(sf::Vector2i mousePosition) const
		{
			return mTriggerArea.contains(mousePosition);
		}

		inline sf::IntRect get_trigger_area(void) const
		{
			return mTriggerArea;
		}

	public:
		Widget(void) :
			mTriggerArea()
		{

		}

		Widget(sf::Vector2i position, sf::Vector2i size) :
			mTriggerArea(position, size)
		{

		}
		
		virtual ~Widget(void) 
		{

		}

		virtual void draw(sf::RenderWindow *window) const = 0;
		virtual void update(sf::Vector2i mousePosition) = 0;
		virtual void on_click(bool clickedOn) = 0;
	};
}


