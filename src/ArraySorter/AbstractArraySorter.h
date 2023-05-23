#pragma once
#include <string>
#include "../Array/Array.hpp"

template <class T>
class AbstractArraySorter
{
public:
	virtual void sort(Array<T>& array) = 0;
	virtual std::string name() = 0;
};