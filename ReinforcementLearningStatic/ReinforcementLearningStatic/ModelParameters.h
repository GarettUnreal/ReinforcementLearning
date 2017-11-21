#pragma once

#include <memory>

class ModelParameters
{
public:
	ModelParameters();

	virtual ~ModelParameters();

	virtual void update(double alpha, double delta, std::shared_ptr<ModelParameters> eligibilityTraces) = 0;
};

