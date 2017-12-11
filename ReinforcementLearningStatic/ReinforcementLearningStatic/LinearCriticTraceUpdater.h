#pragma once

#include "CriticEligibilityTraceUpdater.h"

class LinearCriticTraceUpdater : public CriticEligibilityTraceUpdater
{
public:
	LinearCriticTraceUpdater();
	virtual ~LinearCriticTraceUpdater();

	virtual void visitCritic(
		const std::shared_ptr<ValueFunction>& valueFunction,
		const State& state,
		const double lambda,
		const double gamma,
		std::shared_ptr<ModelParameters> criticTraces
	);
};

