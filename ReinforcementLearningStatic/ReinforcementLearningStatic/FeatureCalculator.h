#pragma once

#include "State.h"
#include "Action.h"
#include "Vector.h"
#include <vector>
#include "Tiling.h"
#include <memory>

class FeatureCalculator
{
public:
	FeatureCalculator( std::vector< std::shared_ptr<Tiling> > tilings );
	virtual ~FeatureCalculator();

	virtual void calculateFeatures(
		const State& state,
		const Action& action,
		std::vector< unsigned int >* requiredIndicies
	);

	unsigned int getNumFeatures() const;

private:

	std::vector< std::shared_ptr<Tiling> > _tilings;
};

