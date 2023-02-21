#include <iostream>
#include "ArrayBuilder/NumberArrayBuilder.hpp"
#include "ArraySorter/HashSorter/HashSorter.h"
#include "Array/Array.hpp"

int main()
{
    std::srand((unsigned)time(NULL));

    NumberArrayBuilder<int> builder;
    HashSorter<int> sorter;

    Array<int> array = builder.random(10, 1, 13);

    for (int index = 0; index < array.size(); index++)
    {
        std::cout << array[index] << std::endl;
    }

    std::cout << std::endl;

    sorter.sort(array);

    for (int index = 0; index < array.size(); index++)
    {
        std::cout << array[index] << std::endl;
    }
}
