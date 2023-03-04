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
        Node<T> *prevent = NULL;
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

