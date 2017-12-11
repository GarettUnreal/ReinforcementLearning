#pragma once

#include "Vector.h"

class State
{
public:
	State(unsigned int dimensions);
	~State();

	inline const Vector<double>& getValue() const
	{
		return _values;
	}

	inline void set(unsigned int index, double value)
	{
		_values.set(index, value);
	}

private:

	Vector<double> _values;
};

