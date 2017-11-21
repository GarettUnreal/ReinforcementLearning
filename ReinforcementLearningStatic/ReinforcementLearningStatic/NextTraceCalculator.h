#pragma once

/*!
 * Calculates the next trace value given the current trace value.
 * Dervied classes must override the getNextTraceValue(...) function.
 */
class NextTraceCalculator
{
public:

	virtual double getNextTraceValue(double currentTraceValue) = 0;
};

