#pragma once

#include "ResourceIdentifiers.h"
#include "StateIdentifiers.h"

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>

namespace sf
{
	class RenderWindow;
}

namespace States
{
	class StateManager;

	class State
	{
	public:
		typedef std::unique_ptr<State> statePointer;

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
		StateManager *mStateManager;

	protected:
		inline Context get_context(void) const 
		{ 
			return mContext;
		}

		void add_state(ID stateID);
		void delete_state(void);

	public:
		State(StateManager &stateManager, Context context);
		virtual ~State(void);

		virtual void render(void) = 0;
		virtual bool update(sf::Time elapsedTime) = 0;
		virtual bool handle_event(const sf::Event &event) = 0;
	};
}