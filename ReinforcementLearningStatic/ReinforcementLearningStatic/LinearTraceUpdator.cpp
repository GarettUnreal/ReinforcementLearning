#include "stdafx.h"
#include "LinearTraceUpdator.h"
#include "LinearStateActionValueFunction.h"
#include "LinearParameters.h"
#include "LinearStateActionFeatureCalculator.h"

LinearTraceUpdator::LinearTraceUpdator()
{
}


LinearTraceUpdator::~LinearTraceUpdator()
{
}

void LinearTraceUpdator::stateActionVisitUpdate(std::shared_ptr<ValueFunction> valueFunction,
	const Circumstance& circumstance, std::shared_ptr<ModelParameters> eligibilityTraces)
{
	const StateActionCircumstance& stateActionCircumstance = dynamic_cast<const StateActionCircumstance&>(circumstance);
	const LinearStateActionValueFunction* linearValuFn = static_cast<const LinearStateActionValueFunction*>(valueFunction.get());
	LinearStateActionFeatureCalculator* calculator = dynamic_cast<LinearStateActionFeatureCalculator*>(linearValuFn->getFeatureCalculator().get() );
	std::vector<unsigned int> requiredIndicies;
	calculator->calculateFeatures(stateActionCircumstance, &requiredIndicies);
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
