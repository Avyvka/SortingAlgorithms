#pragma once
#include "../Array/Array.hpp"

template <class T>
class AbstractArraySorter
{
public:
	virtual void sort(Array<T>& array) = 0;
};