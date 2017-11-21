#pragma once

#include <vector>
#include <memory>
#include "ModelParameters.h"
#include "Vector.h"

class LinearParameters : public ModelParameters 
{
public:
	LinearParameters( unsigned int size);

	virtual ~LinearParameters();

	virtual void update(double alpha, double delta, std::shared_ptr<ModelParameters> eligibilityTraces);

	double getAt(unsigned int index) const;

	inline void set(unsigned int index, double value)
	{
		_weights.set(index, value);
	}

	unsigned int size() const;

	void operator*=(double factor);

private:

	Vector< double > _weights;
};

