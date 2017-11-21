#include "stdafx.h"
#include "LinearParameters.h"
#include <memory>

LinearParameters::LinearParameters( unsigned int size ) :
	_weights(size)
{
	for (unsigned int index = 0; index < size; ++index)
	{
		_weights.set(index, 0.0);
	}
}


LinearParameters::~LinearParameters()
{
}

void LinearParameters::update(double alpha, double delta, std::shared_ptr<ModelParameters> eligibilityTraces)
{
	const LinearParameters* traces = dynamic_cast<const LinearParameters*>(eligibilityTraces.get());
	_weights.addMult(traces->_weights, alpha * delta);
}

unsigned int LinearParameters::size() const
{
	return _weights.size();
}

void LinearParameters::operator*=(double factor)
{
	_weights *= factor;
}

double LinearParameters::getAt(unsigned int index) const
{
	return _weights.getAt(index);
}
