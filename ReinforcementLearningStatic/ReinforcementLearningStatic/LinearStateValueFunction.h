#pragma once

#include "ValueFunction.h"

class LinearStateValueFunction : public ValueFunction
{
public:
	LinearStateValueFunction();
	virtual ~LinearStateValueFunction();

	virtual double value(const Circumstance& circumstance);
	virtual std::shared_ptr< ModelParameters > gradient(const Circumstance& circumstance);
};

