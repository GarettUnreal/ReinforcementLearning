#include "stdafx.h"
#include "Tiles.h"


Tiles::Tiles()
{
}


Tiles::~Tiles()
{
}

void Tiles::initialize(const TilesConfig& config, double normalizedRandom )
{
	_min = config.min;
	_max = config.max;
	_numTiles = config.numTiles;

	if (_numTiles <= 1 || _min > _max)
	{
		throw BadArgumentException();
	}

	_tileSize = (_max - _min) / static_cast<double>(_numTiles - 1);
	_offset = normalizedRandom * _tileSize;
}

unsigned int Tiles::getTileIndex(double value) const
{
	return static_cast<unsigned int>(((value - (_min - _offset)) / _tileSize));
}
