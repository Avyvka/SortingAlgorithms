#pragma once
#include "AbstractArraySorter.h"
#include "../Array/Array.hpp"

template <class T>
class BubbleSorter : public AbstractArraySorter<T>
{
private:
    void swap(T& arg0, T& arg1)
    {
        T temp = arg0;
        arg0 = arg1;
        arg1 = temp;
    }

public:
	void sort(Array<T>& array) override
	{
        for (T step = 0; step < array.size() - 1; ++step)
        {
            for (T index = 0; index < array.size() - step - 1; ++index)
            {
                if (array[index] > array[index + 1])
                {
                    swap(array[index], array[index + 1]);
                }
            }
        }
	}
};