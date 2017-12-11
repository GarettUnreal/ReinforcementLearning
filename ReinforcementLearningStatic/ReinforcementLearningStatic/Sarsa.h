#pragma once

#include "Policy.h"
#include "Action.h"
#include "State.h"
#include "ValueFunction.h"
#include "EligibilityTraceUpdater.h"
#include "StateActionCircumstance.h"

class Sarsa
{
public:

	Sarsa(
		std::shared_ptr<ValueFunction> valueFunction,
		std::shared_ptr<ModelParameters> eligibilityTraces,
		std::shared_ptr<ModelParameters> modelParameters,
		std::shared_ptr<EligibilityTraceUpdater> eligibilityTraceUpdater
	);

	virtual ~Sarsa();

	void setInitialStateAction( const StateActionCircumstance& stateAction );

	void stepUpdate(
		const double lambda,
		const double gamma,
		const double alpha,
		const double reward,
		const StateActionCircumstance& stateAction
	);

	void terminalUpdate(
		const double lambda,
		const double gamma,
		const double alpha,
		const double reward
	);

private:

	std::shared_ptr<ValueFunction> _valueFunction;
	std::shared_ptr<EligibilityTraceUpdater> _eligibilityTraceUpdater;

	StateActionCircumstance _prevCircumstance;
	double _prevValuePred;
	std::shared_ptr<ModelParameters> _modelParameters;
	std::shared_ptr<ModelParameters> _eligibilityTraces;

};

