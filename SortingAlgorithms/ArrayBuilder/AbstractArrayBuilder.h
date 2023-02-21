#pragma once
#include "../Array/Array.hpp"

template <class T>
class AbstractArrayBuilder
{
public:
	virtual Array<T> create(std::size_t size) = 0;
	virtual Array<T> reverse(std::size_t size) = 0;
};

