#pragma once

#include "ValueFunction.h"

#include "Policy.h"

class DiscreteGreedyPolicy : public Policy
{
public:
	DiscreteGreedyPolicy();
	~DiscreteGreedyPolicy();

	inline void setValueFunction(std::shared_ptr<ValueFunction> valueFunction)
	{
		_valueFunction = valueFunction;
	}

	inline void setActions(const std::vector< std::shared_ptr<Action> >& actions)
	{
		_actions = actions;
	}

	/*!
	 * Set the epsilon greedy value. The value must be between 0 and 1 inclusive.
	 * @param[in] epsilon The epsilon greedy value. This value determines the probability
	 * that you choose a random action. Set this to 0 to always be greedy.
	 * Set this value to 1 to always be random.
	 */
	inline void setEpsilonGreedy(double epsilon)
	{
		_epsilon = epsilon;
	}

	/*!
	* Chooese an action using a value function and a specified state.
	* This function should not be invoked unless the 'setValueFunction' has beend
	* invoked with a valid value function.
	* @param[in] state The state to evaluate which action to take.
	* @return An action to take based on the state. NULL is returned if
	* there are no actions to choose from.
	*/
	virtual std::shared_ptr<Action> chooseAction(const State& state);

	/*!
	 * Randomly choose an action from the set of available actions.
	 * @return A randomly chosen action. NULL is returned if there are
	 * no actions to choose from.
	 */
	virtual std::shared_ptr<Action> chooseRandomAction();

protected:

	bool testEpsilonGreedy();

	std::vector< std::shared_ptr<Action> > _actions;
	std::shared_ptr<ValueFunction> _valueFunction;
	double _epsilon;
};

