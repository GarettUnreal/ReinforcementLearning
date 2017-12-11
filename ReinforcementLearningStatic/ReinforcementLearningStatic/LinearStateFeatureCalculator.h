#pragma once

#include "StateCircumstance.h"
#include "Tiling.h"
#include <memory>
#include <vector>

class LinearStateFeatureCalculator
{
public:
	LinearStateFeatureCalculator(std::vector< std::shared_ptr<Tiling> > tilings);
	virtual ~LinearStateFeatureCalculator();

	virtual void calculateFeatures(
		const StateCircumstance& stateAction,
		std::vector< unsigned int >* requiredIndicies
	) const;

	unsigned int getNumFeatures() const;

private:

	std::vector< std::shared_ptr<Tiling> > _tilings;
};

