#include "stdafx.h"
#include "Sarsa.h"


Sarsa::Sarsa(
	std::shared_ptr<ValueFunction> valueFunction,
	std::shared_ptr<ModelParameters> eligibilityTraces,
	std::shared_ptr<ModelParameters> modelParameters,
	std::shared_ptr<EligibilityTraceUpdater> eligibilityTraceUpdater
) :
	_valueFunction(valueFunction),
	_eligibilityTraces(eligibilityTraces),
	_modelParameters(modelParameters),
	_eligibilityTraceUpdater(eligibilityTraceUpdater),
	_prevValuePred(0)
{}

Sarsa::~Sarsa()
{
}

void Sarsa::setInitialStateAction(const StateActionCircumstance& stateAction)
{
	_prevCircumstance.state = stateAction.state;
	_prevCircumstance.action = stateAction.action;
	_prevValuePred = _valueFunction->value(stateAction);
}

void
Sarsa::stepUpdate(
	const double lambda,
	const double gamma,
	const double alpha,
	const double reward,
	const StateActionCircumstance& stateAction
)
{
	_eligibilityTraceUpdater->stateActionVisitUpdate(_valueFunction, _prevCircumstance, _eligibilityTraces );

	double currValuePred = _valueFunction->value(stateAction);

	double delta = reward + gamma * currValuePred - _prevValuePred;

	_modelParameters->update(alpha, delta, _eligibilityTraces);

	_eligibilityTraceUpdater->stateDecayUpdate(gamma, lambda, _eligibilityTraces);

	_prevCircumstance.state = stateAction.state;
	_prevCircumstance.action = stateAction.action;
	_prevValuePred = currValuePred;
}

void Sarsa::terminalUpdate(const double lambda, const double gamma, const double alpha, const double reward)
{
	_eligibilityTraceUpdater->stateActionVisitUpdate(_valueFunction, _prevCircumstance, _eligibilityTraces);
	double delta = reward - _prevValuePred;

	_modelParameters->update(alpha, delta, _eligibilityTraces);
}
