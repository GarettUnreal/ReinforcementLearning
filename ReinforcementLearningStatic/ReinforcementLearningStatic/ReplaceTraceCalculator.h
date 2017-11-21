#pragma once

#include "NextTraceCalculator.h"

class ReplaceTraceCalculator : public NextTraceCalculator
{
public:

	virtual double getNextTraceValue(double currentTraceValue);
};

