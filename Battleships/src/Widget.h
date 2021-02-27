#pragma once

#include "Utility.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Text.hpp>

#include <string>

namespace sf
{
	class RenderWindow;
	class Event;
}

namespace GUI
{
	class Widget
	{
	public:
		enum class AlignOptions : uint8_t
		{
			LEFT,
			CENTER
		};

	private:
		sf::IntRect mTriggerArea;
		sf::Text mText;

	private:
		bool mIsTextVisible;
		bool mIsSelected;
		bool mIsActive;
		uint8_t mDefaultFontSize;
		AlignOptions mAlignMode;

	public:
		inline bool is_mouse_over(sf::Vector2i mousePosition) const
		{
			return mTriggerArea.contains(mousePosition);
		}

		inline void select(void)
		{
			mIsSelected = true;
		}

		inline void deselect(void)
		{
			mIsSelected = false;
		}

		inline void activate(void)
		{
			mIsActive = true;
		}

		inline void deactivate(void)
		{
			mIsActive = false;
		}

		inline bool is_text_visible(void) const
		{
			return mIsTextVisible;
		}

		inline bool is_selected(void) const
		{
			return mIsSelected;
		}

		inline bool is_active(void) const
		{
			return mIsActive;
		}

		inline void set_text(const std::string &text)
		{
			mText.setString(text);
		}

		inline std::string get_text(void)
		{
			return mText.getString();
		}

		inline void change_text_visibility(bool isTextVisible)
		{
			mIsTextVisible = isTextVisible;
		}

		inline void set_text_color(sf::Color color)
		{
			mText.setFillColor(color);
		}

		/*
			Alter text size by passed value.
		*/
		inline void change_text_size(int8_t value)
		{
			mText.setCharacterSize(mDefaultFontSize + value);
			set_text_position();
		}

		void set_text_position(void)
		{
			sf::FloatRect textBounds = mText.getLocalBounds();
			Utility::set_origin_to_center(mText);

			switch (mAlignMode)
			{
				case AlignOptions::LEFT:
					mText.setPosition(mTriggerArea.left + textBounds.width / 2.0f + 5.0f, mTriggerArea.top + mTriggerArea.height / 2.0f);
					break;

				case AlignOptions::CENTER:
					mText.setPosition(mTriggerArea.left + mTriggerArea.width / 2.0f, mTriggerArea.top + mTriggerArea.height / 2.0f);
					break;
			}
		}

		inline void set_align_mode(AlignOptions mode)
		{
			mAlignMode = mode;
		}

	public:
		Widget(void);
		Widget(	sf::Vector2i position, 
				sf::Vector2i size, 
				const std::string &text = std::string(), 
				const sf::Font &font = sf::Font(), 
				uint8_t fontSize = 0);
		virtual ~Widget(void);

		virtual void draw(sf::RenderWindow *window) const;
		virtual void update(sf::Vector2i mousePosition) = 0;
		virtual void handle_event(const sf::Event &event) = 0;
	};
}