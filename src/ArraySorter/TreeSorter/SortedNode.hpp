#pragma once
#include "Node.hpp"

template <class T>
class SortedNode : public Node<T>
{
private:
    using Node<T>::setLeft;
    using Node<T>::setRight;

public:
    using Node<T>::Node;

    void insert(Node<T>* node) override
    {
        Node<T>* current = this;
        Node<T>* prevent = NULL;

        while (current != NULL)
        {
            prevent = current;

            if (current->value > node->value)
            {
                current = current->left();
            }
            else
            {
                current = current->right();
            }
        }

        if (prevent->value > node->value)
        {
            setLeft(prevent, node);
        }
        else
        {
            setRight(prevent, node);
        }
    }

    void inorder(Array<T>& array)
    {
        Node<T>* current = this;
        Node<T>* prevent = NULL;
        std::size_t index = 0;

        // Обход дерева алгоритмом Морриса
        // 
        // Порядок обхода:
        //      4
        //     / \
        //    2   5
        //   / \
        //  1   3
        // 
        // 1. Если левый потомок текущего узла пуст, вывести текущий узел 
        // и использовать его правый потомок в качестве текущего узла.
        // 
        // 2. Если левый дочерний элемент текущего узла не пуст,
        // найти предшествующий узел текущего узла в левом поддереве текущего узла.
        // 
        //   а) Если правый дочерний узел предшествующего узла пуст,
        //      сделать его правый дочерний узел текущим узлом
        //      Текущий узел обновляется до левого потомка текущего узла.
        // 
        //   б) Если правый дочерний узел предшествующего узла является текущим узлом, 
        //      сбросить его правый дочерний узел на NULL.
        //      Вывести текущий узел.
        //      Текущий узел обновляется до правого потомка текущего узла.
        // 
        // 3. Повторить 1 и 2, пока текущий узел не станет пустым.

        while (current != NULL)
        {
            if (current->left() == NULL)
            {
                array[index++] = current->value;
                current = current->right();
            }
            else
            {
                prevent = current->left();

                while (prevent->right() != NULL && prevent->right() != current)
                {
                    prevent = prevent->right();
                }

                if (prevent->right() == NULL)
                {
                    setRight(prevent, current);
                    current = current->left();
                }
                else
                {
                    setRight(prevent, NULL);
                    array[index++] = current->value;
                    current = current->right();
                }
            }
        }
    }
};