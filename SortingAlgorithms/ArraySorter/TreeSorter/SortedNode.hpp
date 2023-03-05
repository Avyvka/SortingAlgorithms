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

        // ����� ������ ���������� �������
        // 
        // ������� ������:
        //      4
        //     / \
        //    2   5
        //   / \
        //  1   3
        // 
        // 1. ���� ����� ������� �������� ���� ����, ������� ������� ���� 
        // � ������������ ��� ������ ������� � �������� �������� ����.
        // 
        // 2. ���� ����� �������� ������� �������� ���� �� ����,
        // ����� �������������� ���� �������� ���� � ����� ��������� �������� ����.
        // 
        //   �) ���� ������ �������� ���� ��������������� ���� ����,
        //      ������� ��� ������ �������� ���� ������� �����
        //      ������� ���� ����������� �� ������ ������� �������� ����.
        // 
        //   �) ���� ������ �������� ���� ��������������� ���� �������� ������� �����, 
        //      �������� ��� ������ �������� ���� �� NULL.
        //      ������� ������� ����.
        //      ������� ���� ����������� �� ������� ������� �������� ����.
        // 
        // 3. ��������� 1 � 2, ���� ������� ���� �� ������ ������.

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