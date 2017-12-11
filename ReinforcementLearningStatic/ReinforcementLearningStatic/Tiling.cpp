#include "stdafx.h"
#include "Tiling.h"


Tiling::Tiling() :
	_numIndices(0)
{
}


Tiling::~Tiling()
{
}

void Tiling::initialize(const std::vector<TilesConfig>& dimensionConfigs)
{
	_numIndices = 0;
	double normalizedRandom = rand() / static_cast<double>(RAND_MAX);
	for (unsigned int index = 0; index < dimensionConfigs.size(); ++index)
	{
		TilesConfig tileConfig = dimensionConfigs.at(index);
		Tiles tiles;
		tiles.initialize(tileConfig,normalizedRandom);
		_tileDimensions.push_back(tiles);

		if (index >= 1)
		{
			_numIndices *= tiles.getNumTiles();
		}
		else
		{
			_numIndices = tiles.getNumTiles();
		}
	}
}

unsigned int Tiling::getIndex(const Vector<double>& value) const
{
	unsigned int index = -1;
	double dimensionValue = 0.0;
	unsigned int dimensionIndex = 0;
	unsigned int dimensionOffset = 0;

	if (_tileDimensions.size() > 1)
	{
		index = 0;
		dimensionOffset = 1;
		for (unsigned int dimension = 0; dimension < _tileDimensions.size(); ++dimension)
		{
			if (dimension > 0)
			{
				dimensionOffset *= _tileDimensions.at(dimension - 1).getNumTiles();
			}

			dimensionValue = value.getAt(dimension);
			dimensionIndex = _tileDimensions.at(dimension).getTileIndex(dimensionValue);
			index += dimensionIndex * dimensionOffset;
		}
	}

	return index;
}
