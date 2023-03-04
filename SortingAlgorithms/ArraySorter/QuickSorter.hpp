#pragma once
#include "AbstractArraySorter.h"
#include "../Array/Array.hpp"

template <class T>
class QuickSorter : public AbstractArraySorter<T>
{
private:
    std::size_t partition(Array<T>& array, std::size_t low, std::size_t high, T pivot)
    {
        std::size_t pIndex = low;

        for (std::size_t index = low; index <= high; index++)
        {
            if (array[index] <= pivot) {
                array.swap(pIndex++, index);
            }
        }

        return pIndex - 1;
    }

    void sort(Array<T>& array, std::size_t low, std::size_t high)
    {   
        if (low < high + 1) 
        {
            std::size_t pivotIndex = partition(array, low, high, array[high]);

            sort(array, low, pivotIndex - 1);
            sort(array, pivotIndex + 1, high);
        }
    }

public:
    void sort(Array<T>& array) override
    {
        sort(array, 0, array.size() - 1);
    }
};