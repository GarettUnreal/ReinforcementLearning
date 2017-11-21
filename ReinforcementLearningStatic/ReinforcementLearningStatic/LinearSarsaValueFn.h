#pragma once

#include "SarsaValueFunction.h"
#include "FeatureCalculator.h"

class LinearSarsaValueFn : public SarsaValueFunction
{
public:
	LinearSarsaValueFn(FeatureCalculator* featureCalculator);
	virtual ~LinearSarsaValueFn();

	virtual double value(
		const State& state,
		const Action& action
	);

	virtual std::shared_ptr< ModelParameters > gradient(
		const State& state,
		const Action& action
	);

	inline FeatureCalculator* getFeatureCalculator() const
	{
		return _featureCalculator;
	}

private:

	FeatureCalculator* _featureCalculator;
};

