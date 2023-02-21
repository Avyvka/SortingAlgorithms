#pragma once
#include <memory>

template <class T>
class Array
{
private:
	std::unique_ptr<T[]> _pointer;
	std::size_t _size;

public:
	Array(std::size_t size)
	{
		_size = size;
		_pointer = std::unique_ptr<T[]>(new T[_size]);
	}

	std::size_t size()
	{
		return _size;
	}

	T& first()
	{
		return _pointer[0];
	}

	T& last()
	{
		return _pointer[_size - 1];
	}

	T& operator [] (std::size_t index)
	{
		return _pointer[index];
	}
};