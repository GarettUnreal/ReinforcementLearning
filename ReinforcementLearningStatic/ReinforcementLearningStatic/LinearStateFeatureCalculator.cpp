#include "stdafx.h"
#include "LinearStateFeatureCalculator.h"


LinearStateFeatureCalculator::LinearStateFeatureCalculator(std::vector< std::shared_ptr<Tiling> > tilings) :
	_tilings(tilings)
{
}


LinearStateFeatureCalculator::~LinearStateFeatureCalculator()
{
}

void LinearStateFeatureCalculator::calculateFeatures(const StateCircumstance& state, std::vector<unsigned int>* requiredIndicies) const
{
	const Vector<double>& stateValues = state.state.getValue();

	unsigned int indexOffset = 0;
	for (unsigned int index = 0; index < _tilings.size(); ++index)
	{
		if (index >= 1)
		{
			indexOffset += _tilings.at(index - 1)->getNumIndices();
		}
		requiredIndicies->push_back(_tilings.at(index)->getIndex(stateValues) + indexOffset);
	}
}

unsigned int LinearStateFeatureCalculator::getNumFeatures() const
{
	int features = 0;
	for (unsigned int index = 0; index < _tilings.size(); ++index)
	{
		features += _tilings.at(index)->getNumIndices();
	}
	return features;
}
