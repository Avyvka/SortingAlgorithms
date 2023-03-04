#pragma once

template <class T>
class Node
{
public:
    const T value;

    Node* left = NULL;
    Node* right = NULL;

    Node(T _value) : value(_value) {};

    void insert(Node<T>* node)
    {
        Node<T>* current = this;
        Node<T>* prevent = NULL;

        while (current != NULL)
        {
            prevent = current;

            if (current->value > node->value)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }

        if (prevent->value > node->value)
        {
            prevent->left = node;
        }
        else
        {
            prevent->right = node;
        }
    }
};