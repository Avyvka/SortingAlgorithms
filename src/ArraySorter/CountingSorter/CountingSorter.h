#pragma once
#include <utility>
#include "../AbstractArraySorter.h"

template <class T>
class CountingSorter : public AbstractArraySorter<T>
{
private:
	std::pair<T, T> minmax(Array<T>& array);

public:
	std::string name() override;
	void sort(Array<T>& array) override;
};

template class CountingSorter<int>;
template class CountingSorter<long>;
template class CountingSorter<long long>;