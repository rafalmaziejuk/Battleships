#include "State.h"
#include "StateManager.h"

namespace States
{
	State::State(StateManager &stateManager, Context context) :
		mStateManager(&stateManager),
		mContext(context)
	{

	}

    State::~State(void)
    {

    }

	void State::add_state(ID stateID)
	{
		mStateManager->add_state(stateID);
	}

	void State::delete_state(void)
	{
		mStateManager->delete_state();
	}
    
}