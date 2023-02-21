#include "HashSorter.h"
#include <iostream>

template <class T>
std::pair<T, T> HashSorter<T>::minmax(Array<T>& array)
{
    T min = array.first();
    T max = array.first();

    for (std::size_t index = 0; index < array.size(); index++)
    {
        if (array[index] < min) {
            min = array[index];
        }

        if (array[index] > max) {
            max = array[index];
        }
    }

    return { min, max };
}

template <class T>
void HashSorter<T>::sort(Array<T>& array)
{
    const std::pair<T, T> pair = minmax(array);
    const T min = pair.first;
    const T max = pair.second;

    if (min == max) return;

    T* hashPos = new T[max + 1]{ 0 };
    T* hashNeg = new T[min + 1]{ 0 };

    std::cout << min << ", " << max << std::endl << std::endl;

    for (std::size_t index = 0; index < array.size(); index++)
    {
        if (array[index] >= 0)
        {
            hashPos[array[index]] += 1;
        }
        else
        {
            hashNeg[std::abs(array[index])] += 1;
        }
    }

    T resultIndex = 0;

    for (T index = min; index > 0; index--)
    {
        if (hashNeg[index])
        {
            for (T j = 0; j < hashNeg[index]; j++)
            {
                array[resultIndex++] = (-1) * index;
            }
        }
    }

    for (T index = 0; index <= max; index++)
    {   
        if (hashPos[index])
        {
            for (std::size_t j = 0; j < hashPos[index]; j++)
            {
                array[resultIndex++] = index;
            }
        }
    }

    delete[] hashPos;
    delete[] hashNeg;
}