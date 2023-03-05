#pragma once

template <class T>
class Node
{
private:
    Node* _left = NULL;
    Node* _right = NULL;

protected:
    virtual void left(Node<T>* node) final
    {
        _left = node;
    }

    virtual void right(Node<T>* node) final
    {
        _right = node;
    }

    virtual void setLeft(Node<T>* root, Node<T>* node) final
    {
        root->left(node);
    }

    virtual void setRight(Node<T>* root, Node<T>* node) final
    {
        root->right(node);
    }

public:
    const T value;

    Node(T _value) : value(_value) {};

    virtual void insert(Node<T>* node) = 0;

    virtual Node* left() const final
    {
        return _left;
    }

    virtual Node* right() const final
    {
        return _right;
    }
};