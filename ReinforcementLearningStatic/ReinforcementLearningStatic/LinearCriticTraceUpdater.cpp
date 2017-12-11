#include "stdafx.h"
#include "LinearCriticTraceUpdater.h"
#include "LinearStateValueFunction.h"
#include "LinearStateFeatureCalculator.h"
#include "LinearParameters.h"

LinearCriticTraceUpdater::LinearCriticTraceUpdater()
{
}


LinearCriticTraceUpdater::~LinearCriticTraceUpdater()
{
}

void LinearCriticTraceUpdater::visitCritic(
	const std::shared_ptr<ValueFunction>& valueFunction,
	const State & state, const double lambda, const double gamma,
	std::shared_ptr<ModelParameters> criticTraces)
{
	const LinearStateValueFunction* linearValuFn = dynamic_cast<const LinearStateValueFunction*>(valueFunction.get());
	const LinearStateFeatureCalculator* featureCalculator = dynamic_cast<const LinearStateFeatureCalculator*>(
		linearValuFn->getFeatureCalculator().get());
	std::vector<unsigned int> requiredIndicies;
	StateCircumstance circumstance;
	circumstance.state = state;
	featureCalculator->calculateFeatures(circumstance, &requiredIndicies);
	LinearParameters* criticLinearTraces = dynamic_cast<LinearParameters*>(criticTraces.get());

	*criticLinearTraces *= gamma * lambda;

	unsigned int requiredIndex = 0;
	double traceValue = 0.0;
	for (unsigned int index = 0; index < requiredIndicies.size(); ++index)
	{
		requiredIndex = requiredIndicies.at(index);
		traceValue = criticLinearTraces->getAt(requiredIndex);

		criticLinearTraces->set(requiredIndex, traceValue + 1.0);
	}
}
