#include "stdafx.h"
#include "LinearStateActionFeatureCalculator.h"


LinearStateActionFeatureCalculator::LinearStateActionFeatureCalculator(std::vector< std::shared_ptr<Tiling> > tilings) :
	_tilings(tilings)
{
}


LinearStateActionFeatureCalculator::~LinearStateActionFeatureCalculator()
{
	
}

void LinearStateActionFeatureCalculator::calculateFeatures(const StateActionCircumstance& stateAction, std::vector<unsigned int>* requiredIndicies) const
{
	const Vector<double>& stateValues = stateAction.state.getValue();
	const Vector<double>& actionValues = stateAction.action.getValue();

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

unsigned int LinearStateActionFeatureCalculator::getNumFeatures() const
{
	int features = 0;
	for (unsigned int index = 0; index < _tilings.size(); ++index)
	{
		features += _tilings.at(index)->getNumIndices();
	}
	return features;
}
