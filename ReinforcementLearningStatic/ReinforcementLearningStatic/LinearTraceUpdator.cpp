#include "stdafx.h"
#include "LinearTraceUpdator.h"
#include "LinearSarsaValueFn.h"
#include "LinearParameters.h"

LinearTraceUpdator::LinearTraceUpdator()
{
}


LinearTraceUpdator::~LinearTraceUpdator()
{
}

void LinearTraceUpdator::stateVisitUpdate(std::shared_ptr<SarsaValueFunction> valueFunction, const State & state,
	const Action & action, std::shared_ptr<ModelParameters> eligibilityTraces)
{
	const LinearSarsaValueFn* linearValuFn = static_cast<const LinearSarsaValueFn*>(valueFunction.get());
	FeatureCalculator* calculator = linearValuFn->getFeatureCalculator();
	std::vector<unsigned int> requiredIndicies;
	calculator->calculateFeatures(state, action, &requiredIndicies);
	LinearParameters* linearParameters = dynamic_cast<LinearParameters*>(eligibilityTraces.get());

	unsigned int requiredIndex = 0;
	double traceValue = 0.0;
	for (unsigned int index = 0; index < requiredIndicies.size(); ++index)
	{
		requiredIndex = requiredIndicies.at(index);
		traceValue = linearParameters->getAt(requiredIndex);

		linearParameters->set(requiredIndex, _nextTraceCalculator->getNextTraceValue( traceValue ) );
	}
}

void LinearTraceUpdator::stateDecayUpdate(double gamma, double lambda, std::shared_ptr<ModelParameters> eligibilityTraces)
{
	LinearParameters* linearParameters = dynamic_cast<LinearParameters*>(eligibilityTraces.get());
	
	(*linearParameters) *= gamma * lambda;
}
