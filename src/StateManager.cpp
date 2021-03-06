#include "StateManager.h"

namespace Jungle
{
	StateManager::StateManager(void)
		:current_state_(NULL)
	{
	}


	StateManager::~StateManager(void)
	{
	}

	

	void StateManager::Update()
	{
		if(current_state_ != NULL)
			current_state_->Update();
	}

	void StateManager::ChangeState( State* game_state, StateOP op )
	{
		if(op == SOP_PUSH)
		{
			if(current_state_ == game_state) return;
			game_state->SetParent(current_state_);
			current_state_ = game_state;
		}
		else if (op == SOP_POP && current_state_ == game_state)
		{
			assert(current_state_ == game_state);
			//TODO: memory leak
			current_state_ = current_state_->GetParent();
		}
	}
	State* StateManager::CurrentState()
	{
		return current_state_;
	}

}
