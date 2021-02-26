#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include "ResourceIdentifiers.h"

namespace States
{
	class State
	{
	public:
		struct Context
		{
			sf::RenderWindow *mWindow;
			TextureManager *mTextures;
			FontManager *mFonts;

			Context(sf::RenderWindow &window, TextureManager &textures, FontManager &fonts) :
				mWindow(&window),
				mTextures(&textures),
				mFonts(&fonts)
			{

			}
		};

	private:
		Context mContext;

	protected:
		Context get_context(void) const { return mContext; }

	public:
		State(Context context) : mContext(context) { }

		virtual ~State(void) { };

		virtual void render(void) = 0;
		virtual void update(sf::Time elapsedTime) = 0;
		virtual void handle_event(const sf::Event &event) = 0;
	};
}