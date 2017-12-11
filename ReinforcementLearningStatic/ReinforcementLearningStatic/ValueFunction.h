#pragma once

#include "Circumstance.h"
#include "ModelParameters.h"
#include <memory>
#include "FeatureCalculator.h"

class ValueFunction
{
public:
	ValueFunction();

	virtual ~ValueFunction();

	inline std::shared_ptr<FeatureCalculator> getFeatureCalculator() const
	{
		return _featureCalculator;
	}

	inline std::shared_ptr<ModelParameters> getModelParameters() const
	{
		return _modelParameters;
	}

	inline void setFeatureCalculator(std::shared_ptr<FeatureCalculator> featureCalculator)
	{
		_featureCalculator = featureCalculator;
	}

	inline void setModelParameters(std::shared_ptr< ModelParameters > modelParameters)
	{
		_modelParameters = modelParameters;
	}

	virtual double value(const Circumstance& circumstance) = 0;

	virtual std::shared_ptr< ModelParameters > gradient(const Circumstance& circumstance) = 0;

protected:
	std::shared_ptr<FeatureCalculator> _featureCalculator;
	std::shared_ptr< ModelParameters > _modelParameters;
};

