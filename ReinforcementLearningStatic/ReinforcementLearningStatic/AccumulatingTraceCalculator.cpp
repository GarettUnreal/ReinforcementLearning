#include "stdafx.h"
#include "AccumulatingTraceCalculator.h"

double AccumulatingTraceCalculator::getNextTraceValue(double currentTraceValue)
{
	return currentTraceValue + 1.0;
}
