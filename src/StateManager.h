#ifndef STATE_MANAGER_H_
#define STATE_MANAGER_H_

#pragma once
#include <vector>

#include "State.h"
#include "ofxKinectUsers.h"


namespace Jungle
{
	enum StateOP
	{
		SOP_PUSH,
		SOP_POP,
	};

	class StateManager
	{
	public:
		StateManager(void);
		~StateManager(void);

		void Update();
		void ChangeState(State* game_state, StateOP op);
		State* CurrentState();

	private:
		std::vector<State*> states_;
		State* current_state_;

	};

}
#endif
