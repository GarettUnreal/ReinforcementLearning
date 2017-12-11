#include "stdafx.h"
#include "PolicyGradient.h"
#include "StateCircumstance.h"

PolicyGradient::PolicyGradient(
	std::shared_ptr<ValueFunction> criticFunction,
	std::shared_ptr<PolicyProbabilityFunction> actorFunction,
	std::shared_ptr<ModelParameters> criticParameters,
	std::shared_ptr<ModelParameters> actorParameters
) :
	_criticFunction(criticFunction),
	_actorFunction(actorFunction),
	_criticParameters(criticParameters),
	_actorParameters(actorParameters),
	_prevValuePred(0),
	_prevState(0)
{
}


PolicyGradient::~PolicyGradient()
{
}

void PolicyGradient::setInitialState(const State& state)
{
	_prevState = state;
	StateCircumstance stateCircumstance;
	stateCircumstance.state = state;
	_prevValuePred = _criticFunction->value(stateCircumstance);
}

void PolicyGradient::stepUpdate(const StepParameters& stepParameters, const State & nextState,
	const Action & previousAction)
{

	StateCircumstance stateCircumstance;
	stateCircumstance.state = nextState;
	double currValuePred = _criticFunction->value(stateCircumstance);
	double delta = stepParameters.reward + stepParameters.gamma * currValuePred - _prevValuePred;

	_criticEligibilityUpdater->visitCritic( _criticFunction, nextState, stepParameters.gamma,
		stepParameters.criticLambda, _criticTraces);
	_actorEligibilityUpdater->visitActor( _actorFunction, nextState, previousAction, stepParameters.gamma,
		stepParameters.actorLambda, _actorTraces);

	_criticParameters->update(stepParameters.criticAlpha, delta, _criticTraces);
	_actorParameters->update(stepParameters.actorAlpha, delta, _actorTraces);

	_prevState = nextState;
}
