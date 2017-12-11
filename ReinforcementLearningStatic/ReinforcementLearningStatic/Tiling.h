#pragma once

#include "Tiles.h"
#include <vector>
#include "Vector.h"

class Tiling
{
public:
	Tiling();
	~Tiling();

	void initialize(const std::vector<TilesConfig>& dimensionConfigs);

	unsigned int getIndex(const Vector<double>& value) const;

	unsigned int getNumIndices() const
	{
		return _numIndices;
	}

private:

	unsigned int _numIndices;
	
	std::vector<Tiles> _tileDimensions;
};

