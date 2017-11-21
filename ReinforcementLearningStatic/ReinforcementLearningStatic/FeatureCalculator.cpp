#include "stdafx.h"
#include "FeatureCalculator.h"


FeatureCalculator::FeatureCalculator(std::vector< std::shared_ptr<Tiling> > tilings) :
	_tilings(tilings)
{
}


FeatureCalculator::~FeatureCalculator()
{
	
}

void FeatureCalculator::calculateFeatures(const State & state, const Action & action, std::vector<unsigned int>* requiredIndicies)
{
	const Vector<double>& stateValues = state.getValue();
	const Vector<double>& actionValues = action.getValue();

	Vector<double> stateActionValues(stateValues.size() + actionValues.size() );
	for (unsigned int index = 0; index < stateValues.size(); ++index)
	{
		stateActionValues.set(index, stateValues.getAt(index));
	}
	
	for (unsigned int index = stateValues.size(); index < stateActionValues.size(); ++index)
	{
		stateActionValues.set(index, actionValues.getAt(index - stateValues.size()));
	}

	unsigned int indexOffset = 0;
	for (unsigned int index = 0; index < _tilings.size(); ++index)
	{
		if (index >= 1)
		{
			indexOffset += _tilings.at(index - 1)->getNumIndices();
		}
		requiredIndicies->push_back(_tilings.at(index)->getIndex(stateActionValues) + indexOffset);
	}
}

unsigned int FeatureCalculator::getNumFeatures() const
{
	int features = 0;
	for (unsigned int index = 0; index < _tilings.size(); ++index)
	{
		features += _tilings.at(index)->getNumIndices();
	}
	return features;
}
