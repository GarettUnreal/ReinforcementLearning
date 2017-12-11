#pragma once

#include <cmath>
#include <exception>

class ElementSizeMismatchException : public std::exception
{
	virtual const char* what() const throw()
	{
		return "Vector element size mismatch";
	}
};

template <class T>
class Vector
{
public:
	Vector(unsigned int numElements);

	Vector(const Vector& other);
	~Vector();

	inline unsigned int size() const
	{
		return _numElements;
	}

	inline T getAt(unsigned int index) const
	{
		return _elements[index];
	}

	inline void set(unsigned int index, T value)
	{
		_elements[index] = value;
	}

	inline void addMult(const Vector& other, double multFactor);

	Vector operator+(const Vector& other) const;
	Vector operator*(T factor) const;
	Vector& operator=(const Vector& other);
	Vector& operator*=(T factor);
	Vector& operator+=(T factor);


private:

	inline void alloc(int size)
	{
		_numElements = size;
		_elements = new T[_numElements];
	}

	inline void dealloc()
	{
		_numElements = 0;
		delete _elements;
		_elements = NULL;
	}

	T* _elements;
	unsigned int _numElements;
};

template <class T>
Vector<T>::Vector(unsigned int size) :
	_elements( NULL )
{
	alloc(size);
}

template<class T>
inline Vector<T>::Vector(const Vector & other) :
	_elements( NULL )
{
	*this = other;
}

template <class T>
Vector<T>::~Vector()
{
	dealloc();
}

template <class T>
void Vector<T>::addMult(const Vector& other, double multFactor)
{
	if (_numElements != other._numElements)
	{
		throw ElementSizeMismatchException();
	}

	for (unsigned int index = 0; index < _numElements; ++index)
	{
		_elements[index] += other._elements[index] * multFactor;
	}
}

template <class T>
Vector<T> Vector<T>::operator+(const Vector<T>& other) const
{
	if (_numElements != other._numElements)
	{
		throw ElementSizeMismatchException();
	}

	Vector result(_numElements);

	for (unsigned int index = 0; index < _numElements; ++index)
	{
		result._elements[index] = _elements[index] + other._elements[index];
	}

	return result;
}

template <class T>
Vector<T> Vector<T>::operator*(T factor) const
{
	Vector result(_numElements);

	for (unsigned int index = 0; index < _numElements; ++index)
	{
		result._elements[index] = _elements[index] * factor;
	}

	return result;
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
	if (this != &other)
	{
		if (_numElements != other._numElements)
		{
			dealloc();
			alloc(other._numElements);
		}

		for (unsigned int index = 0; index < _numElements; ++index)
		{
			_elements[index] = other._elements[index];
		}
	}

	return *this;
}

template <class T>
Vector<T>& Vector<T>::operator*=(T factor)
{
	for (unsigned int index = 0; index < _numElements; ++index)
	{
		_elements[index] = factor * _elements[index];
	}

	return *this;
}

template <class T>
Vector<T>& Vector<T>::operator+=(T factor)
{
	if (_numElements != other._numElements)
	{
		throw ElementSizeMismatchException();
	}

	for (unsigned int index = 0; index < _numElements; ++index)
	{
		_elements[index] = _elements[index] + other._numElements[index];
	}

	return *this;
}

