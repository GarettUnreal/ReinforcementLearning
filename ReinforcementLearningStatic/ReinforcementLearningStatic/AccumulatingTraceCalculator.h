#pragma once

#include "NextTraceCalculator.h"

class AccumulatingTraceCalculator : public NextTraceCalculator
{
public:

	virtual double getNextTraceValue(double currentTraceValue);
};

