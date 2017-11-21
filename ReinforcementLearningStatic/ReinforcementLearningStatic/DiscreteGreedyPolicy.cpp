#include "stdafx.h"
#include "DiscreteGreedyPolicy.h"


DiscreteGreedyPolicy::DiscreteGreedyPolicy()
{
}


DiscreteGreedyPolicy::~DiscreteGreedyPolicy()
{
}

std::shared_ptr<Action> DiscreteGreedyPolicy::chooseAction(const State& state)
{
	if (testEpsilonGreedy())
	{
		return chooseRandomAction();
	}

	unsigned int numActions = _actions.size();
	unsigned int actionIndex = numActions;
	double bestValue = DBL_MIN;
	double stateActionValue = 0.0;
	for (unsigned int index = 0; index < numActions; ++index)
	{
		stateActionValue = _valueFunction->value(state, *_actions.at(index));
		if (actionIndex == numActions || stateActionValue > bestValue)
		{
			bestValue = stateActionValue;
			actionIndex = index;
		}
	}

	if (actionIndex != numActions)
	{
		return _actions.at(actionIndex);
	}

	return std::shared_ptr<Action>();
}

std::shared_ptr<Action> DiscreteGreedyPolicy::chooseRandomAction()
{
	if (_actions.size() == 0)
	{
		return std::shared_ptr<Action>();
	}

	double normalizedRandom = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
	unsigned int randomIndex = static_cast<unsigned int>((_actions.size()) * normalizedRandom);
	if (randomIndex == _actions.size())
	{
		randomIndex = _actions.size() - 1;
	}

	return _actions.at(randomIndex);
}

bool DiscreteGreedyPolicy::testEpsilonGreedy()
{
	double normalizedRandom = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
	return normalizedRandom < _epsilon;
}

