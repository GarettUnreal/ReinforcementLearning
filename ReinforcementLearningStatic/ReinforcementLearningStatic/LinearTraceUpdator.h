#pragma once

#include "EligibilityTraceUpdater.h"
#include "StateActionCircumstance.h"

class LinearTraceUpdator : public EligibilityTraceUpdater
{
public:
	LinearTraceUpdator();
	virtual ~LinearTraceUpdator();

	virtual void stateActionVisitUpdate(std::shared_ptr<ValueFunction> valueFunction,
		const Circumstance& circumstance, std::shared_ptr<ModelParameters> eligibilityTraces);

	virtual void stateDecayUpdate(double gamma, double lambda, std::shared_ptr<ModelParameters> eligibilityTraces);
};

