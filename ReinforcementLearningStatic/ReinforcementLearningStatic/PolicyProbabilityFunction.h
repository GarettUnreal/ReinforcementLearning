#pragma once

#include "Action.h"
#include "State.h"

class PolicyProbabilityFunction
{
public:
	PolicyProbabilityFunction();
	virtual ~PolicyProbabilityFunction();

	virtual double value(const Action& action, const State& state) = 0;

	virtual double gradient(const Action& action, const State& state) = 0;
};

