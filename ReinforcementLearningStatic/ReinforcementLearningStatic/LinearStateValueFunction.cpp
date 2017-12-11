#include "stdafx.h"
#include "LinearStateValueFunction.h"
#include "State.h"

LinearStateValueFunction::LinearStateValueFunction()
{
}


LinearStateValueFunction::~LinearStateValueFunction()
{
}

double LinearStateValueFunction::value(const Circumstance& circumstance)
{
	return 0.0;
}

std::shared_ptr<ModelParameters> LinearStateValueFunction::gradient(const Circumstance& circumstance)
{
	return std::shared_ptr<ModelParameters>();
}
