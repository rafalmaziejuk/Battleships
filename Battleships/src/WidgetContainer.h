#pragma once

#include "Widget.h"

#include <map>
#include <functional>

namespace GUI
{
	template <typename T>
	class WidgetContainer
	{
	private:
		std::map<T, Widget *> mContainer;

	public:
		WidgetContainer(void) : mContainer() {  }

		template <typename WidgetType>
		void insert_widget(T name, WidgetType *widget)
		{
			mContainer.insert(std::pair<T, WidgetType *>(name, widget));
		}

		template <typename WidgetType>
		WidgetType * get_widget(T index)
		{
			return static_cast<WidgetType *>(mContainer[index]);
		}

		uint8_t get_size(void) const
		{
			return mContainer.size();
		}

		void draw(sf::RenderWindow *window) const
		{
			for (auto &[name, widget] : mContainer)
				widget->draw(window);
		}

		void update(sf::Vector2i mousePosition)
		{
			for (auto &[name, widget] : mContainer)
				widget->update(mousePosition);
		}

		void handle_event(const sf::Event &event)
		{
			for (auto &[name, widget] : mContainer)
				widget->handle_event(event);
		}

		void clear_widgets(void)
		{
			for (auto &[name, widget] : mContainer)
				delete widget;
		}
	};
}