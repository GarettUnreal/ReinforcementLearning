#pragma once

#include <memory>
#include <vector>
#include "Action.h"
#include "State.h"

class Policy
{
public:
	Policy();

	virtual ~Policy();

	/*!
	 * Chooese an action using a value function and a specified state.
	 * This function should not be invoked unless the 'setValueFunction' has beend
	 * invoked with a valid value function.
	 * @param[in] state The state to evaluate which action to take.
	 * @return An action to take based on the state.
	 */
	virtual std::shared_ptr<Action> chooseAction( const State& state ) = 0;
	
};

