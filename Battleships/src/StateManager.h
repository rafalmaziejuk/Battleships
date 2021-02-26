#pragma once

#include <iostream>

#include <SFML/System/NonCopyable.hpp>

#include "State.h"

namespace States
{
	class StateManager : private sf::NonCopyable
	{
	private:
		State *mCurrentState;

	private:
		StateManager(void) : mCurrentState(nullptr) {  }
		~StateManager(void) { delete mCurrentState; }

	public:
		static StateManager & get_instance(void)
		{
			static StateManager stateManager;
			return stateManager;
		}

		inline bool is_empty(void) const
		{
			return (mCurrentState == nullptr) ? true : false;
		}

		inline void delete_state(void)
		{
			delete mCurrentState;
			mCurrentState = nullptr;
		}

		template <typename T>
		inline void change_state(State::Context &context)
		{
			if (!is_empty())
				delete mCurrentState;

			mCurrentState = new T(context);
		}

		inline State * get_state(void) const
		{
			return mCurrentState;
		}
	};
}