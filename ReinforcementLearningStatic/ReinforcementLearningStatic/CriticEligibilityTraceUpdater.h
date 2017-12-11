#pragma once

#include <memory>
#include "ValueFunction.h"
#include "ModelParameters.h"
#include "State.h"

class CriticEligibilityTraceUpdater
{
public:
	CriticEligibilityTraceUpdater();
	virtual ~CriticEligibilityTraceUpdater();

	virtual void visitCritic(
		const std::shared_ptr<ValueFunction>& valueFunction,
		const State& state,
		const double lambda,
		const double gamma,
		std::shared_ptr<ModelParameters> criticTraces
	) = 0;
};

