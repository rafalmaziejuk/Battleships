#pragma once

#include "State.h"
#include "StateIdentifiers.h"

#include <SFML/System/NonCopyable.hpp>

#include <functional>
#include <utility>
#include <cstdint>
#include <vector>
#include <map>

namespace States
{
	class StateManager : private sf::NonCopyable
	{
	public:
		enum class Action : uint8_t
		{
			ADD,
			DELETE
		};

	private:
		State::statePointer create_state(ID stateID);
		void do_pending_actions(void);

	private:
		struct PendingAction
		{
			Action mAction;
			ID mStateID;
			
			explicit PendingAction(Action action, ID stateID = ID::NONE);
		};

	private:
		std::vector<State::statePointer> mStates;
		std::map<States::ID, std::function<State::statePointer()>> mStateConstructors;
		std::vector<PendingAction> mPendingActions;
		States::State::Context mContext;

	public:
		explicit StateManager(State::Context context);

		template <typename T>
		inline void register_state(ID stateID);
		
		template <typename T1, typename T2>
		inline void register_state(ID stateID, T2 t2);

		void render(void);
		void update(sf::Time elapsedTime);
		void handle_event(const sf::Event &event);

		void add_state(ID stateID);
		void delete_state(void);
		bool is_empty(void) const;
	};

	template<typename T>
	inline void StateManager::register_state(ID stateID)
	{
		mStateConstructors[stateID] = [this](void)
		{
			return State::statePointer(new T(*this, mContext));
		};
	}

	template<typename T1, typename T2>
	inline void StateManager::register_state(ID stateID, T2 t2)
	{
		mStateConstructors[stateID] = [this, t2](void)
		{
			return State::statePointer(new T1(*this, mContext, t2));
		};
	}
}