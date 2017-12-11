#include "stdafx.h"

#include "Vector.h"
#include "LinearStateActionValueFunction.h"
#include "LinearParameters.h"
#include "LinearStateActionFeatureCalculator.h"

LinearStateActionValueFunction::LinearStateActionValueFunction()
{
}


LinearStateActionValueFunction::~LinearStateActionValueFunction()
{}

double LinearStateActionValueFunction::value(const Circumstance& circumstance)
{
	const StateActionCircumstance& stateAction = dynamic_cast<const StateActionCircumstance&>(circumstance);
	const LinearParameters* linearParameters = dynamic_cast<const LinearParameters*>(_modelParameters.get());

	std::vector<unsigned int> requiredIndicies;
	dynamic_cast<LinearStateActionFeatureCalculator*>(_featureCalculator.get() )->calculateFeatures(stateAction, &requiredIndicies);

	double result = 0.0;
	unsigned int requiredIndex = 0;
	for (unsigned int index = 0; index < requiredIndicies.size(); ++index)
	{
		requiredIndex = requiredIndicies.at(index);
		result += linearParameters->getAt(requiredIndex);
	}

	return result;
}

std::shared_ptr< ModelParameters > LinearStateActionValueFunction::gradient(const Circumstance& circumstance)
{
	const StateActionCircumstance& stateAction = dynamic_cast<const StateActionCircumstance&>(circumstance);
	std::vector<unsigned int> requiredIndicies;
	LinearStateActionFeatureCalculator* featureCalculator = dynamic_cast<LinearStateActionFeatureCalculator*>(_featureCalculator.get());

	featureCalculator->calculateFeatures(stateAction, &requiredIndicies);
	const LinearParameters* linearParameters = dynamic_cast<const LinearParameters*>(_modelParameters.get());

	unsigned int numFeatures = featureCalculator->getNumFeatures();
	LinearParameters* result = new LinearParameters(numFeatures);

	for (unsigned int index = 0; index < numFeatures; ++index)
	{
		result->set(index, 0.0);
	}

	for (unsigned int index = 0; index < requiredIndicies.size(); ++index)
	{
		result->set(requiredIndicies.at(index), 1.0);
	}

	return std::shared_ptr< ModelParameters >( result );
}
