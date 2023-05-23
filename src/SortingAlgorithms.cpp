#include <map>
#include <chrono>
#include <memory>
#include <iostream>
#include <functional>

#include "Array/Array.hpp"
#include "ArrayBuilder/NumberArrayBuilder.hpp"
#include "ArraySorter/QuickSorter.hpp"
#include "ArraySorter/BubbleSorter.hpp"
#include "ArraySorter/LidovskyHashSorter.hpp"
#include "ArraySorter/TreeSorter/TreeSorter.hpp"
#include "ArraySorter/CountingSorter/CountingSorter.h"

long long executeTime(std::function<void()> callback)
{   
    using std::chrono::microseconds;
    using std::chrono::high_resolution_clock;
    using std::chrono::steady_clock;

    steady_clock::time_point begin = high_resolution_clock::now();

    callback();

    steady_clock::time_point end = high_resolution_clock::now();

    return duration_cast<microseconds>(end - begin).count();
}

template<typename T>
long long timeOfSort(Array<T> array, AbstractArraySorter<T>& sorter)
{
    long long time = executeTime([&array, &sorter]() -> void { return sorter.sort(array); });

    if (array.isSorted())
    {
        return time;
    }
    else
    {
        return -1;
    }
}

std::string pad(std::string const& str, std::size_t size)
{
    if (str.size() < size)
    {
        return str + std::string(size - str.size(), ' ');
    }
    else
    {
        return str;
    }
}

template<typename Key, typename Value>
using SortedHashMap = std::map<Key, Value>;

template <class T>
void test()
{
    std::vector<std::size_t> sizes = { 1000, 2000, 4000, 8000, 16000, 32000, 64000 };

    std::vector<std::shared_ptr<AbstractArraySorter<T>>> sorters{
        std::make_shared<BubbleSorter<T>>(),
        std::make_shared<TreeSorter<T>>(),
        std::make_shared<CountingSorter<T>>(),
        std::make_shared<QuickSorter<T>>(),
        std::make_shared<LidovskyHashSorter<T>>()
    };

    NumberArrayBuilder<T> builder;
    SortedHashMap<std::string, std::function<Array<T>(std::size_t)>> types = {
        {"Ordered", [&builder](std::size_t size) -> Array<T> { return builder.create(size); }},
        {"Reverse", [&builder](std::size_t size) -> Array<T> { return builder.reverse(size); }},
        {"Random(1-12)", [&builder](std::size_t size) -> Array<T> { return builder.random(size, 1, 12); }},
        {"Random(1-7000)", [&builder](std::size_t size) -> Array<T> { return builder.random(size, 1, 70000); }}
    };

    for (std::pair<std::string, std::function<Array<T>(std::size_t)>> type : types)
    {   
        std::function<Array<T>(std::size_t)> createArray = type.second;

        std::cout << type.first << " ---------------------------------------------------- ";
        std::cout << std::endl << pad("", 10);

        for (std::shared_ptr<AbstractArraySorter<T>> sorter : sorters)
        {
            std::cout << pad(sorter->name(), sorter->name().length() + 6);
        }

        for (std::size_t size : sizes)
        {
            Array<T> array = createArray(size);

            std::cout << std::endl << pad("[" + std::to_string(size) + "]", 10);

            for (std::shared_ptr<AbstractArraySorter<T>> sorter : sorters)
            {
                std::cout << pad(std::to_string(timeOfSort(array.clone(), *sorter.get())), sorter->name().length() + 6);
            }
        }

        std::cout << std::endl << std::endl;
    }
}

int main()
{
    std::srand((unsigned)time(NULL));

    test<int>();
}
