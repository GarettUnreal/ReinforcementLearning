#pragma once

#include <memory>
#include "ValueFunction.h"
#include "ModelParameters.h"
#include "PolicyProbabilityFunction.h"

class ActorEligibilityTraceUpdater
{
public:
	ActorEligibilityTraceUpdater();
	virtual ~ActorEligibilityTraceUpdater();

	virtual void visitActor(
		const std::shared_ptr<PolicyProbabilityFunction>& valueFunction,
		const State& state,
		const Action& action,
		const double lambda,
		const double gamma,
		std::shared_ptr<ModelParameters> actorTraces
	) = 0;
};

