#pragma once
#include "Node.hpp"
#include "../AbstractArraySorter.h"

template <class T>
class TreeSorter : public AbstractArraySorter<T>
{
private:
    void inorder(Node<T>* root, Array<T>& array)
    {
        if (root == NULL)
        {
            return;
        }

        Node<T> *current = root;
        Node<T> *prevent;
        std::size_t index = 0;

        while (current != NULL)
        {
            if (current->left == NULL)
            {
                array[index++] = current->value;
                current = current->right;
            }
            else
            {
                prevent = current->left;

                while (prevent->right != NULL && prevent->right != current)
                {
                    prevent = prevent->right;
                }

                if (prevent->right == NULL)
                {
                    prevent->right = current;
                    current = current->left;
                }
                else
                {
                    prevent->right = NULL;
                    array[index++] = current->value;
                    current = current->right;
                }
            }
        }
    }

public:
    void sort(Array<T>& array) override
    {
        Node<T>* root = new Node<T>(array.first());

        for (int index = 1; index < array.size(); index++)
        {
            root->insert(new Node<T>(array[index]));
        }

        inorder(root, array);
    }
};

