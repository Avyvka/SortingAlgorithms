#include "CountingSorter.h"
#include <iostream>

template <class T>
std::pair<T, T> CountingSorter<T>::minmax(Array<T>& array)
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
void CountingSorter<T>::sort(Array<T>& array)
{
    const std::pair<T, T> pair = minmax(array);
    const T min = std::abs(pair.first);
    const T max = std::abs(pair.second);

    Array<T> hashNeg = Array<T>(min + 1);
    hashNeg.fill(NULL);

    Array<T> hashPos = Array<T>(max + 1);
    hashPos.fill(NULL);

    for (T index = 0; index < array.size(); index++)
    {
        if (array[index] < 0)
        {
            hashNeg[std::abs(array[index])] += 1;
        }
        else
        {
            hashPos[array[index]] += 1;
        }
    }

    T resultIndex = 0;

    for (T negIndex = min; negIndex > 0; negIndex--)
    {
        if (hashNeg[negIndex] != NULL)
        {
            for (T index = 0; index < hashNeg[negIndex]; index++)
            {
                array[resultIndex++] = (-1) * negIndex;
            }
        }
    }

    for (T posIndex = 0; posIndex <= max; posIndex++)
    {   
        if (hashPos[posIndex] != NULL)
        {
            for (T index = 0; index < hashPos[posIndex]; index++)
            {
                array[resultIndex++] = posIndex;
            }
        }
    }
}