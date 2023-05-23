#pragma once
#include <memory>
#include <string>
#include <iostream>

template <class T>
class Array
{
private:
	std::unique_ptr<T[]> _pointer;
	std::size_t _size;

	std::string pad(std::string const& str, size_t s)
	{
		if (str.size() < s)
			return std::string(s - str.size(), ' ') + str;
		else
			return str;
	}

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

	bool isSorted()
	{
		for (std::size_t index = 0; index < _size - 1; index++)
		{
			if (_pointer[index] > _pointer[index + 1])
			{
				return false;
			}
		}

		return true;
	}

	void swap(T& arg0, T& arg1)
	{
		T temp = arg0;
		arg0 = arg1;
		arg1 = temp;
	}

	void swap(std::size_t arg0, std::size_t arg1)
	{
		swap(_pointer[arg0], _pointer[arg1]);
	}

	void print()
	{
		const std::size_t length = std::to_string(_size - 1).length();

		for (std::size_t index = 0; index < _size; index++)
		{
			std::cout << "[" << pad(std::to_string(index), length) << "] = " << _pointer[index] << std::endl;
		}

		std::cout << std::endl;
	}

	void fill(T value)
	{
		for (std::size_t index = 0; index < _size; index++)
		{
			_pointer[index] = value;
		}
	}

	Array<T> clone()
	{
		Array<T> clone = Array<T>(_size);

		for (std::size_t index = 0; index < _size; index++)
		{
			clone[index] = _pointer[index];
		}

		return clone;
	}
};