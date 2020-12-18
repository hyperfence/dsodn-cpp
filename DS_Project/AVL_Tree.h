#pragma once
#include <iostream>

using namespace std;

template <class T>
struct AVL {
    template <class U>
    struct Node {
        U data;
        Node<U>* Left;
        Node<U>* Right;
        int height;
    };
    Node<T>* Root = NULL;

    int getHeight(Node<T>* n)
    {
        if (n != NULL)
            return n->height;
        else
            return 0;
    }

    int max(int val1, int val2)
    {
        if (val1 > val2)
            return val1;
        return val2;
    }

    Node<T>* rotateRight(Node<T>* n) {
        Node<T>* temp1 = n->Left;
        Node<T>* T2 = temp1->Right;

        temp1->Right = n;
        n->Left = T2;

        n->height = max(getHeight(n->Left), getHeight(n->Right)) + 1;
        temp1->height = max(getHeight(temp1->Left), getHeight(temp1->Right)) + 1;

        return temp1;
    }

    Node<T>* rotateLeft(Node<T>* n)
    {
        Node<T>* temp1 = n->Right;
        Node<T>* temp2 = temp1->Left;

        temp1->Left = n;
        n->Right = temp2;

        n->height = max(getHeight(n->Left), getHeight(n->Right)) + 1;
        temp1->height = max(getHeight(temp1->Left), getHeight(temp1->Right)) + 1;

        return temp1;
    }

    int Balance(Node<T>* n)
    {
        if (n == NULL)
            return 0;
        return getHeight(n->Left) - getHeight(n->Right);
    }

    Node<T>* insert(Node<T>* n, T value) {
        if (n == NULL) {
            n = new Node<T>;
            n->data = value;
            n->Left = NULL;
            n->Right = NULL;
            n->height = 1;
            return n;
        }
        else if (value < n->data) {
            n->Left = insert(n->Left, value);
        }
        else if (value > n->data) {
            n->Right = insert(n->Right, value);
        }
        else
            return n;

        n->height = 1 + max(getHeight(n->Left), getHeight(n->Right));
        int balance = Balance(n);

        if (balance > 1 && value < n->Left->data)
            return rotateRight(n);

        if (balance < -1 && value > n->Right->data)
            return rotateLeft(n);

        if (balance > 1 && value > n->Left->data)
        {
            n->Left = rotateLeft(n->Left);
            return rotateRight(n);
        }

        if (balance < -1 && value < n->Right->data)
        {
            n->Right = rotateRight(n->Right);
            return rotateLeft(n);
        }

        return n;
    }

    Node<T>* leftMostNode(Node<T>* n)
    {
        Node<T>* current = n;

        while (current->Left != NULL)
            current = current->Left;

        return current;
    }

    Node<T>* remove(Node<T>* n, int value)
    {
        if (n == NULL)
            return n;

        if (value < n->data)
            n->Left = remove(n->Left, value);

        else if (value > n->data)
            n->Right = remove(n->Right, value);

        else
        {
            if (n->Left == NULL) {
                Node<T>* temp = n->Right;
                delete n;
                return temp;
            }
            else if (n->Right == NULL) {
                Node<T>* temp = n->Left;
                delete n;
                return temp;
            }

            Node<T>* temp = n->Right;

            while (temp && temp->Left != NULL)
                temp = temp->Left;

            n->data = temp->data;
            n->Right = remove(n->Right, temp->data);
        }

        if (n == NULL)
            return n;

        n->height = 1 + max(getHeight(n->Left), getHeight(n->Right));
        int balance = Balance(n);

        if (balance > 1 && Balance(n->Left) >= 0)
            return rotateRight(n);

        if (balance > 1 && Balance(n->Left) < 0)
        {
            n->Left = rotateLeft(n->Left);
            return rotateRight(n);
        }

        if (balance < -1 && Balance(n->Right) <= 0)
            return rotateLeft(n);

        if (balance < -1 && Balance(n->Right) > 0)
        {
            n->Right = rotateRight(n->Right);
            return rotateLeft(n);
        }

        return n;
    }

    void inOrder(Node<T>* n) {
        if (n != NULL) {
            inOrder(n->Left);
            cout << n->data << " ";
            inOrder(n->Right);
        }
    }

};