#pragma once

#include "Action.h"
#include "State.h"
#include "ModelParameters.h"
#include "PolicyProbabilityFunction.h"
#include "CriticEligibilityTraceUpdater.h"
#include "ActorEligibilityTraceUpdater.h"
#include "ValueFunction.h"

#include <memory>

struct StepParameters {
	double criticLambda;
	double actorLambda;
	double gamma;
	double criticAlpha;
	double actorAlpha;
	double reward;
};

class PolicyGradient
{
public:
	PolicyGradient(
		std::shared_ptr<ValueFunction> criticFunction,
		std::shared_ptr<PolicyProbabilityFunction> actorFunction,
		std::shared_ptr<ModelParameters> criticParameters,
		std::shared_ptr<ModelParameters> actorParameters
	);

	virtual ~PolicyGradient();

	void setInitialState(const State& state);

	void stepUpdate(const StepParameters& stepParameters, const State & nextState,
		const Action & previousAction);

private:

	std::shared_ptr<ValueFunction> _criticFunction;
	std::shared_ptr<PolicyProbabilityFunction> _actorFunction;
	double _prevValuePred;
	State _prevState;

	std::shared_ptr<ModelParameters> _criticTraces;
	std::shared_ptr<ModelParameters> _actorTraces;
	std::shared_ptr<ModelParameters> _criticParameters;
	std::shared_ptr<ModelParameters> _actorParameters;

	std::shared_ptr<CriticEligibilityTraceUpdater> _criticEligibilityUpdater;
	std::shared_ptr<ActorEligibilityTraceUpdater> _actorEligibilityUpdater;
};

