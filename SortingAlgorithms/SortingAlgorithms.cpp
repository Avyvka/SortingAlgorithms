#include <iostream>
#include <time.h> 
#include "ArrayBuilder/NumberArrayBuilder.hpp"
#include "ArraySorter/CountingSorter/CountingSorter.h"
#include "ArraySorter/BubbleSorter.hpp"
#include "ArraySorter/TreeSorter/TreeSorter.hpp"
#include "ArraySorter/LidovskyHashSorter.hpp"
#include "ArraySorter/QuickSorter.hpp"
#include "Array/Array.hpp"
#include <chrono>
#include <functional>
#include <memory>

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

template<typename Key, typename Value>
using HashMap = std::unordered_map<Key, Value>;

typedef HashMap<std::size_t, long long> SortingTime;

template<typename T>
using SorterStatistics = HashMap<std::shared_ptr<AbstractArraySorter<T>>, SortingTime>;

template<typename T>
using SortingStatistics = HashMap<std::string, SorterStatistics<T>>;

std::vector<std::size_t> sizes = { 1000, 2000, 4000, 8000, 16000, 32000, 64000 };

template <class T>
SortingStatistics<T> test()
{
    SortingStatistics<T> result;
    NumberArrayBuilder<T> builder;

    std::vector<std::shared_ptr<AbstractArraySorter<T>>> sorters{
        std::make_shared<BubbleSorter<T>>(),
        std::make_shared<TreeSorter<T>>(),
        std::make_shared<CountingSorter<T>>(),
        std::make_shared<QuickSorter<T>>(),
        std::make_shared<LidovskyHashSorter<T>>()
    };

    HashMap<std::string, std::function<Array<T>(std::size_t)>> types = {
        {"Ordered", [&builder](std::size_t size) -> Array<T> {return builder.create(size); }},
        {"Reverse", [&builder](std::size_t size) -> Array<T> {return builder.reverse(size); }},
        {"Random(1-12)", [&builder](std::size_t size) -> Array<T> { return builder.random(size, 1, 13); }},
        {"Random(1-7000)", [&builder](std::size_t size) -> Array<T> { return builder.random(size, 1, 70001); }}
    };

    for (std::pair<std::string, std::function<Array<T>(std::size_t)>> type : types)
    {   
        std::function<Array<T>(std::size_t)> createArray = type.second;
        
        if (!result.contains(type.first))
        {
            result.insert({ type.first, SorterStatistics<T>() });
        }
        SorterStatistics<T> &sorterStatistics = result.at(type.first);

        for (std::size_t size : sizes)
        {
            Array<T> array = createArray(size);

            for (std::shared_ptr<AbstractArraySorter<T>> sorter : sorters)
            {
                if (!sorterStatistics.contains( sorter ))
                {
                    sorterStatistics.insert({ sorter, SortingTime() });
                }
                SortingTime &sortingTime = sorterStatistics.at(sorter);

                sortingTime.insert({ size, timeOfSort(array.clone(), *sorter.get()) });
            }
        }
    }

    return result;
}

std::string pad(std::string const& str, size_t s)
{
    if (str.size() < s)
        return str + std::string(s - str.size(), ' ');
    else
        return str;
}

template <class T>
void print(SortingStatistics<T> statistics)
{
    for (std::pair<std::string, SorterStatistics<T>> type : statistics)
    {
        std::cout << pad(type.first, 18);

        for (std::size_t size : sizes)
        {
            std::cout << pad("[" + std::to_string(size) + "]", 10);
        }

        std::cout << std::endl;

        for (std::pair<std::shared_ptr<AbstractArraySorter<T>>, SortingTime> sorterStatistics : type.second)
        {
            std::shared_ptr<AbstractArraySorter<T>> sorter = sorterStatistics.first;
            SortingTime sortingTime = sorterStatistics.second;

            std::cout << pad("   " + sorter->name(), 18);

            for (std::size_t size : sizes)
            {
                std::cout << pad(std::to_string(sortingTime.at(size)), 10);
            }

            std::cout << std::endl;
        }

        std::cout << std::endl;
    }
}

int main()
{
    std::srand((unsigned)time(NULL));

    print(test<long>());
}
