#pragma once

#include <vector>
#include <memory>
#include "ActorEligibilityTraceUpdater.h"
#include "LinearParameters.h"

class LinearActorTraceUpdater : public ActorEligibilityTraceUpdater
{
public:
	LinearActorTraceUpdater();
	virtual ~LinearActorTraceUpdater();

	inline void setPossibleActions(const std::vector<std::shared_ptr<Action>>& possibleActions)
	{
		_possibleActions = possibleActions;
	}

	std::vector<std::shared_ptr<Action>> getPossibleActions() const
	{
		return _possibleActions;
	}

	virtual void visitActor(
		const std::shared_ptr<PolicyProbabilityFunction>& valueFunction,
		const State& state,
		const Action& action,
		const double lambda,
		const double gamma,
		std::shared_ptr<ModelParameters> actorTraces
	);

protected:

	std::shared_ptr<LinearParameters> sumGradientActions(
		const State& state,
		const std::vector<std::shared_ptr<Action>>& possibleActions,
		const std::shared_ptr<PolicyProbabilityFunction>& valueFunction
	);

	std::vector<std::shared_ptr<Action>> _possibleActions;
};

