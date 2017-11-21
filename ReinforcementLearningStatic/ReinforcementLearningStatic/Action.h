#pragma once

#include "Vector.h"

class Action
{
public:
	Action(unsigned int dimensions);
	~Action();

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

