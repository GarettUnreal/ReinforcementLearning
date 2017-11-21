#pragma once

#include "EligibilityTraceUpdater.h"

class LinearTraceUpdator : public EligibilityTraceUpdater
{
public:
	LinearTraceUpdator();
	virtual ~LinearTraceUpdator();

	virtual void stateVisitUpdate(std::shared_ptr<SarsaValueFunction> valueFunction,
		const State& state, const Action& action, std::shared_ptr<ModelParameters> eligibilityTraces);

	virtual void stateDecayUpdate(double gamma, double lambda, std::shared_ptr<ModelParameters> eligibilityTraces);
};

