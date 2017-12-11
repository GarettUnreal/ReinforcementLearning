#pragma once

#include "State.h"
#include "Action.h"
#include "Vector.h"
#include <vector>
#include "Tiling.h"
#include <memory>
#include "FeatureCalculator.h"
#include "StateActionCircumstance.h"

class LinearStateActionFeatureCalculator : public FeatureCalculator
{
public:
	LinearStateActionFeatureCalculator( std::vector< std::shared_ptr<Tiling> > tilings );
	virtual ~LinearStateActionFeatureCalculator();

	virtual void calculateFeatures(
		const StateActionCircumstance& stateAction,
		std::vector< unsigned int >* requiredIndicies
	) const;

	unsigned int getNumFeatures() const;

private:

	std::vector< std::shared_ptr<Tiling> > _tilings;
};

