#include "StateManager.h"

#include <cassert>

namespace States
{
	StateManager::StateManager(State::Context context) :
		mStates(),
		mStateConstructors(),
		mPendingActions(),
		mContext(context)
	{

	}

	State::statePointer StateManager::create_state(ID stateID)
	{
		auto stateConstructor = mStateConstructors.find(stateID);
		assert(stateConstructor != mStateConstructors.end());

		return stateConstructor->second();
	}

	void StateManager::do_pending_actions(void)
	{
		for (auto &pendingAction : mPendingActions)
		{
			switch (pendingAction.mAction)
			{
				case Action::ADD:
					mStates.push_back(create_state(pendingAction.mStateID));
					break;

				case Action::DELETE:
					mStates.pop_back();
					break;
			}
		}

		mPendingActions.clear();
	}

	void StateManager::render(void)
	{
		for (auto &state : mStates)
			state->render();
	}

	void StateManager::update(sf::Time elapsedTime)
	{
		for (auto &state : mStates)
		{
			if (!state->update(elapsedTime))
				break;
		}

		do_pending_actions();
	}

	void StateManager::handle_event(const sf::Event &event)
	{
		for (auto &state : mStates)
		{
			if (!state->handle_event(event))
				break;
		}

		do_pending_actions();
	}

	void StateManager::add_state(ID stateID)
	{
		mPendingActions.push_back(PendingAction(Action::ADD, stateID));
	}

	void StateManager::delete_state(void)
	{
		mPendingActions.push_back(PendingAction(Action::DELETE));
	}

	bool StateManager::is_empty(void) const
	{
		return mStates.empty();
	}

	StateManager::PendingAction::PendingAction(Action action, ID stateID) :
		mAction(action),
		mStateID(stateID)
	{

	}
}
