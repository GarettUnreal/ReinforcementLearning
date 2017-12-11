#pragma once

#include <exception>

class BadArgumentException : public std::exception
{
	const char* what() const
	{
		return "Bad Argument Exception";
	}
};

struct TilesConfig
{
	unsigned int numTiles;
	double max;
	double min;
};

class Tiles
{
public:
	Tiles();
	~Tiles();

	void initialize(const TilesConfig& config, double normalizedRandom);

	unsigned int getTileIndex(double value) const;

	inline unsigned int getNumTiles() const
	{
		return _numTiles;
	}

	inline double getOffset() const
	{
		return _offset;
	}

private:

	unsigned int _numTiles;
	double _offset;
	double _max;
	double _min;
	double _tileSize;
};

