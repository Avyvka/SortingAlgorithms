#pragma once
#include "AbstractArrayBuilder.h"

template <class T>
class NumberArrayBuilder : public AbstractArrayBuilder<T>
{
public:
	Array<T> create(std::size_t size) override
	{
		Array<T> result = Array<T>(size);

		for (std::size_t index = 0; index < size; index++) {
			result[index] = (T)index;
		}

		return result;
	}

	Array<T> reverse(std::size_t size) override
	{
		Array<T> result = Array<T>(size);

		for (std::size_t index = 0; index < size; index++) {
			result[index] = (T)size - index - 1;
		}

		return result;
	}

	Array<T> random(std::size_t size, T from, T to)
	{
		Array<T> result = Array<T>(size);

		for (std::size_t index = 0; index < size; index++) {
			result[index] = (T)from + (std::rand() % ((T)to - (T)from + 1));
		}

		return result;
	}
};

