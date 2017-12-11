#include "stdafx.h"
#include <set>
#include "LinearActorTraceUpdater.h"
#include "LinearStateActionFeatureCalculator.h"
#include "LinearStateActionValueFunction.h"
#include "StateCircumstance.h"

LinearActorTraceUpdater::LinearActorTraceUpdater()
{
}


LinearActorTraceUpdater::~LinearActorTraceUpdater()
{
}

void LinearActorTraceUpdater::visitActor(
	const std::shared_ptr<PolicyProbabilityFunction>& valueFunction,
	const State & state, const Action & action, const double lambda, const double gamma,
	std::shared_ptr<ModelParameters> actorTraces)
{
	const LinearStateActionValueFunction* linearValuFn = dynamic_cast<const LinearStateActionValueFunction*>(valueFunction.get());
	const LinearStateActionFeatureCalculator* featureCalculator = dynamic_cast<const LinearStateActionFeatureCalculator*>(
		linearValuFn->getFeatureCalculator().get());
	std::vector<unsigned int> requiredIndicies;
	StateActionCircumstance circumstance;
	circumstance.state = state;
	circumstance.action = action;
	featureCalculator->calculateFeatures(circumstance, &requiredIndicies);
	LinearParameters* criticLinearTraces = dynamic_cast<LinearParameters*>(actorTraces.get());

	*criticLinearTraces *= gamma * lambda;

	std::set<unsigned int> reqIndSet;
	for (unsigned int requiredIndex = 0; requiredIndex < requiredIndicies.size(); ++requiredIndex)
	{
		reqIndSet.insert(requiredIndicies.at(requiredIndex));
	}

	std::shared_ptr<LinearParameters> sumGrad = sumGradientActions(state, _possibleActions, valueFunction);

	unsigned int numFeatures = featureCalculator->getNumFeatures();
	double newValue = 0.0;
	for (unsigned int featureIndex = 0; featureIndex < numFeatures; ++featureIndex)
	{
		newValue = criticLinearTraces->getAt(featureIndex);
		if (reqIndSet.find(featureIndex) == reqIndSet.end())
		{
			newValue -= sumGrad->getAt(featureIndex);
		}
		else
		{
			newValue += 1.0 - sumGrad->getAt(featureIndex);
		}
		criticLinearTraces->set(featureIndex, newValue);
	}
}

std::shared_ptr<LinearParameters> LinearActorTraceUpdater::sumGradientActions(
	const State& state,
	const std::vector<std::shared_ptr<Action>>& possibleActions,
	const std::shared_ptr<PolicyProbabilityFunction>& valueFunction
)
{
	const LinearStateActionValueFunction* linearValuFn = dynamic_cast<const LinearStateActionValueFunction*>(valueFunction.get());
	const LinearStateActionFeatureCalculator* featureCalculator = dynamic_cast<const LinearStateActionFeatureCalculator*>(
		linearValuFn->getFeatureCalculator().get());
	std::shared_ptr<LinearParameters> result(new LinearParameters(featureCalculator->getNumFeatures()));

	StateActionCircumstance circumstance;
	circumstance.state = state;

	for (unsigned int actionIndex = 0; actionIndex < _possibleActions.size(); ++actionIndex)
	{
		circumstance.action = *(_possibleActions.at(actionIndex));

		double actionProbability = valueFunction->value(*(_possibleActions.at(actionIndex)), state);

		std::vector<unsigned int> requiredIndicies;
		featureCalculator->calculateFeatures(circumstance, &requiredIndicies);
		for (unsigned int requiredIndex = 0; requiredIndex < requiredIndicies.size(); ++requiredIndex)
		{
			result->set(requiredIndex, actionProbability + result->getAt(requiredIndex));
		}
	}

	return result;
}
