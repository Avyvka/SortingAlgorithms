#pragma once
#include <utility>
#include "../AbstractArraySorter.h"

template <class T>
class HashSorter : public AbstractArraySorter<T>
{
private:
    std::pair<T, T> minmax(Array<T>& array);

public:
	void sort(Array<T>& array) override;
};

template class HashSorter<int>;
template class HashSorter<long>;