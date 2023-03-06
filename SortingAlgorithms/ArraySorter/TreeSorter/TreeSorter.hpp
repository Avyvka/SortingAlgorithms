#pragma once
#include "SortedNode.hpp"
#include "../AbstractArraySorter.h"

template <class T>
class TreeSorter : public AbstractArraySorter<T>
{
public:
    std::string name()
    {
        return "Tree";
    }

    void sort(Array<T>& array) override
    {
        SortedNode<T>* root = new SortedNode<T>(array.first());

        for (int index = 1; index < array.size(); index++)
        {
            root->insert(new SortedNode<T>(array[index]));
        }

        root->inorder(array);
    }
};

