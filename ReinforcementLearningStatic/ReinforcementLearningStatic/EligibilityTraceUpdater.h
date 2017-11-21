#pragma once

#include "NextTraceCalculator.h"
#include "SarsaValueFunction.h"

class EligibilityTraceUpdater
{
public:
	EligibilityTraceUpdater();
	virtual ~EligibilityTraceUpdater();

	virtual void stateVisitUpdate(std::shared_ptr<SarsaValueFunction> valueFunction,
		const State& state, const Action& action, std::shared_ptr<ModelParameters> eligibilityTraces ) = 0;

	virtual void stateDecayUpdate(double gamma, double lambda, std::shared_ptr<ModelParameters> eligibilityTraces) = 0;

	inline void setNextTraceCalculator(std::shared_ptr<NextTraceCalculator> nextTraceCalculator)
	{
		_nextTraceCalculator = nextTraceCalculator;
	}

	std::shared_ptr<NextTraceCalculator> getNextTraceCalculator() const
	{
		return _nextTraceCalculator;
	}

protected:

	/*!
	 * Allows for a particular type of trace update.
	 * For example, replace traces or accumulating traces.
	 */
	std::shared_ptr<NextTraceCalculator> _nextTraceCalculator;
};

