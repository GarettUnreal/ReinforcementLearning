#pragma once

#include "ValueFunction.h"

class LinearStateActionValueFunction : public ValueFunction
{
public:
	LinearStateActionValueFunction();
	virtual ~LinearStateActionValueFunction();

	virtual double value(const Circumstance& circumstance);

	virtual std::shared_ptr< ModelParameters > gradient(const Circumstance& circumstance);
};

