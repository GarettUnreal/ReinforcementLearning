#pragma once

#include "Policy.h"
#include "Action.h"
#include "State.h"
#include "SarsaValueFunction.h"
#include "EligibilityTraceUpdater.h"

class Sarsa
{
public:

	Sarsa(
		std::shared_ptr<SarsaValueFunction> valueFunction,
		std::shared_ptr<ModelParameters> eligibilityTraces,
		std::shared_ptr<ModelParameters> modelParameters,
		std::shared_ptr<EligibilityTraceUpdater> eligibilityTraceUpdater
	);

	virtual ~Sarsa();

	void setInitialStateAction(
		const State& state,
		const Action& action
	);

	void stepUpdate(
		const double lambda,
		const double gamma,
		const double alpha,
		const double reward,
		const State& state,
		const Action& action
	);

	void terminalUpdate(
		const double lambda,
		const double gamma,
		const double alpha,
		const double reward
	);

private:

	std::shared_ptr<SarsaValueFunction> _valueFunction;
	std::shared_ptr<EligibilityTraceUpdater> _eligibilityTraceUpdater;

	State _prevState;
	Action _prevAction;
	double _prevValuePred;
	std::shared_ptr<ModelParameters> _modelParameters;
	std::shared_ptr<ModelParameters> _eligibilityTraces;

};

