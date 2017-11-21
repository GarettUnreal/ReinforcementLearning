#include "stdafx.h"
#include "Sarsa.h"


Sarsa::Sarsa(
	std::shared_ptr<SarsaValueFunction> valueFunction,
	std::shared_ptr<ModelParameters> eligibilityTraces,
	std::shared_ptr<ModelParameters> modelParameters,
	std::shared_ptr<EligibilityTraceUpdater> eligibilityTraceUpdater
) :
	_valueFunction(valueFunction),
	_eligibilityTraces(eligibilityTraces),
	_modelParameters(modelParameters),
	_eligibilityTraceUpdater(eligibilityTraceUpdater),
	_prevState(0),
	_prevAction(0),
	_prevValuePred(0)
{
}


Sarsa::~Sarsa()
{
}

void Sarsa::setInitialStateAction(
	const State& state,
	const Action& action
)
{
	_prevState = state;
	_prevAction = action;
	_prevValuePred = _valueFunction->value(_prevState, _prevAction);
}

void
Sarsa::stepUpdate(
	const double lambda,
	const double gamma,
	const double alpha,
	const double reward,
	const State& state,
	const Action& action
)
{
	_eligibilityTraceUpdater->stateVisitUpdate(_valueFunction, _prevState, _prevAction, _eligibilityTraces );

	double currValuePred = _valueFunction->value(state, action);

	double delta = reward + gamma * currValuePred - _prevValuePred;

	_modelParameters->update(alpha, delta, _eligibilityTraces);

	_eligibilityTraceUpdater->stateDecayUpdate(gamma, lambda, _eligibilityTraces);

	_prevState = state;
	_prevAction = action;
	_prevValuePred = currValuePred;
}

void Sarsa::terminalUpdate(const double lambda, const double gamma, const double alpha, const double reward)
{
	_eligibilityTraceUpdater->stateVisitUpdate(_valueFunction, _prevState, _prevAction, _eligibilityTraces);
	double delta = reward - _prevValuePred;

	_modelParameters->update(alpha, delta, _eligibilityTraces);
}
