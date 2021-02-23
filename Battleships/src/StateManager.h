#pragma once

#include <iostream>
#include <SFML/System/NonCopyable.hpp>
#include "State.h"

class StateManager : private sf::NonCopyable
{
private:
	State *mCurrentState;

private:
	StateManager(void) : mCurrentState(nullptr) { }
	~StateManager(void) { delete mCurrentState; }

public:
	static StateManager & get_instance(void) 
	{ 
		static StateManager stateManager;
		return stateManager;
	}

	template <typename T>
	void change_state(State::Context &context)
	{
		if (mCurrentState != nullptr)
			delete mCurrentState;

		State *newState = new T(context);
		mCurrentState = newState;
	}
	
	State * get_state(void) { return mCurrentState; }
};