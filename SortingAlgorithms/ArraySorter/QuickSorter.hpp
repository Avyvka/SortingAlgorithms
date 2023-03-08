#pragma once
#include "AbstractArraySorter.h"
#include "../Array/Array.hpp"
#include <stack>

template <class T>
class QuickSorter : public AbstractArraySorter<T>
{
private:
    std::size_t partition(Array<T>& array, std::size_t low, std::size_t high, T pivot)
    {
        std::size_t pIndex = low;

        // Переупорядочивание массива таким образом,
        // чтобы все элементы со значениями меньше опорного
        // располагались перед опорным, а элементы 
        // со значениями больше опорного располагались после него.

        for (std::size_t index = low; index <= high; index++)
        {
            if (array[index] <= pivot)
            {
                array.swap(pIndex++, index);
            }
        }

        return pIndex - 1;
    }

    void sort(Array<T>& array, std::size_t low, std::size_t high)
    {
        std::stack<std::size_t> stack;

        stack.push(low);
        stack.push(high);

        while (!stack.empty())
        {

            high = stack.top();
            stack.pop();

            low = stack.top();
            stack.pop();

            std::size_t pivotIndex = partition(array, low, high, array[high]);

            if (pivotIndex > low + 1)
            {
                stack.push(low);
                stack.push(pivotIndex - 1);
            }

            if (pivotIndex + 1 < high)
            {
                stack.push(pivotIndex + 1);
                stack.push(high);
            }
        }
    }

public:
    std::string name()
    {
        return "Quick";
    }

    void sort(Array<T>& array) override
    {
        sort(array, 0, array.size() - 1);
    }
};