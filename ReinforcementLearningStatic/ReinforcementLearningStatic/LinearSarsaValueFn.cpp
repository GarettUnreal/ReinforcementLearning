#include "stdafx.h"

#include "Vector.h"
#include "LinearSarsaValueFn.h"
#include "LinearParameters.h"


LinearSarsaValueFn::LinearSarsaValueFn(FeatureCalculator* featureCalculator) :
	_featureCalculator(featureCalculator)
{
}


LinearSarsaValueFn::~LinearSarsaValueFn()
{
	delete _featureCalculator;
}

double LinearSarsaValueFn::value(const State & state, const Action & action )
{
	const LinearParameters* linearParameters = dynamic_cast<const LinearParameters*>(_modelParameters.get());

	std::vector<unsigned int> requiredIndicies;
	_featureCalculator->calculateFeatures(state, action, &requiredIndicies);

	double result = 0.0;
	unsigned int requiredIndex = 0;
	for (unsigned int index = 0; index < requiredIndicies.size(); ++index)
	{
		requiredIndex = requiredIndicies.at(index);
		result += linearParameters->getAt(requiredIndex);
	}

	return result;
}

std::shared_ptr< ModelParameters > LinearSarsaValueFn::gradient(const State & state, const Action & action)
{
	std::vector<unsigned int> requiredIndicies;
	_featureCalculator->calculateFeatures(state, action, &requiredIndicies);
	const LinearParameters* linearParameters = dynamic_cast<const LinearParameters*>(_modelParameters.get());

	unsigned int numFeatures = _featureCalculator->getNumFeatures();
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
