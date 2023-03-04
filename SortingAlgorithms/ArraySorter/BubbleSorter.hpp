#pragma once
#include "AbstractArraySorter.h"
#include "../Array/Array.hpp"

template <class T>
class BubbleSorter : public AbstractArraySorter<T>
{
public:
	void sort(Array<T>& array) override
	{
        for (std::size_t step = 0; step < array.size() - 1; step++)
        {
            for (std::size_t index = 0; index < array.size() - step - 1; index++)
            {
                if (array[index] > array[index + 1])
                {
                    array.swap(index, index + 1);
                }
            }
        }
	}
};