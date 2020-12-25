#pragma once

#include <iostream>
#include "AVL_Tree_Lists.h"

template <class U>
struct AVL_Node {
    AVL_Tree_List<U> chainingList;
    AVL_Node<U>* Left;
    AVL_Node<U>* Right;
    int height;
};

template <class T>
class AVL {
private:
    AVL_Node<T>* Root;

public:

    AVL()
    {
        Root = NULL;
    }

    AVL_Node<T>* getRoot()const
    {
        return Root;
    }

    void setRoot(AVL_Node<T>* root)
    {
        this->Root = root;
    }

    int getHeight(AVL_Node<T>* n)
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

    AVL_Node<T>* rotateRight(AVL_Node<T>* n) {
        AVL_Node<T>* temp1 = n->Left;
        AVL_Node<T>* T2 = temp1->Right;

        temp1->Right = n;
        n->Left = T2;

        n->height = max(getHeight(n->Left), getHeight(n->Right)) + 1;
        temp1->height = max(getHeight(temp1->Left), getHeight(temp1->Right)) + 1;

        return temp1;
    }

    AVL_Node<T>* rotateLeft(AVL_Node<T>* n)
    {
        AVL_Node<T>* temp1 = n->Right;
        AVL_Node<T>* temp2 = temp1->Left;

        temp1->Left = n;
        n->Right = temp2;

        n->height = max(getHeight(n->Left), getHeight(n->Right)) + 1;
        temp1->height = max(getHeight(temp1->Left), getHeight(temp1->Right)) + 1;

        return temp1;
    }

    int Balance(AVL_Node<T>* n)
    {
        if (n == NULL)
            return 0;
        return getHeight(n->Left) - getHeight(n->Right);
    }

    AVL_Node<T>* insert(AVL_Node<T>* n, T value, unsigned long long int befHash, int lineNumber) 
    {
        if (n == NULL) 
        {
            n = new AVL_Node<T>;
            n->chainingList.insert(value, befHash, lineNumber);
            n->Left = NULL;
            n->Right = NULL;
            n->height = 1;
            Root = n;
            return n;
        }
        else if (value < n->chainingList.getHead()->data)
        {
            n->Left = insert(n->Left, value, befHash, lineNumber);
        }
        else if (value > n->chainingList.getHead()->data)
        {
            n->Right = insert(n->Right, value, befHash, lineNumber);
        }
        else if (value == n->chainingList.getHead()->data)
        {
            n->chainingList.insert(value, befHash, lineNumber);
        }
        else
        {
            return n;
        }
        n->height = 1 + max(getHeight(n->Left), getHeight(n->Right));
        int balance = Balance(n);
        if (balance > 1 && value < n->Left->chainingList.getHead()->data)
        {
            return rotateRight(n);
        }
        if (balance < -1 && value > n->Right->chainingList.getHead()->data)
        {
            return rotateLeft(n);
        }
        if (balance > 1 && value > n->Left->chainingList.getHead()->data)
        {
            n->Left = rotateLeft(n->Left);
            return rotateRight(n);
        }
        if (balance < -1 && value < n->Right->chainingList.getHead()->data)
        {
            n->Right = rotateRight(n->Right);
            return rotateLeft(n);
        }
        return n;
    }

    AVL_Node<T>* leftMostNode(AVL_Node<T>* n)
    {
        AVL_Node<T>* current = n;
        while (current->Left != NULL)
        {
            current = current->Left;
        }
        return current;
    }

    AVL_Node<T>* remove(AVL_Node<T>* n, T value, unsigned long long int befHash)
    {
        if (n == NULL)
        {
            return n;
        }

        if (value < n->chainingList.getHead()->data)
        {
            n->Left = remove(n->Left, value, befHash);
        }

        else if (value > n->chainingList.getHead()->data)
        {
            n->Right = remove(n->Right, value, befHash);
        }
        else
        {
            if (n->Left == NULL) 
            {
                AVL_Node<T>* temp = n->Right;
                //delete n;
                n->chainingList.RemoveByValue(befHash);
                return temp;
            }
            else if (n->Right == NULL) 
            {
                AVL_Node<T>* temp = n->Left;
                //delete n;
                n->chainingList.RemoveByValue(befHash);
                return temp;
            }
            AVL_Node<T>* temp = n->Right;
            while (temp && temp->Left != NULL)
            {
                temp = temp->Left;
            }
            n->chainingList.getHead()->data = temp->chainingList.getHead()->data;
            n->Right = remove(n->Right, temp->chainingList.getHead()->data, befHash);
        }
        if (n == NULL)
        {
            return n;
        }
        n->height = 1 + max(getHeight(n->Left), getHeight(n->Right));
        int balance = Balance(n);
        if (balance > 1 && Balance(n->Left) >= 0)
        {
            return rotateRight(n);
        }
        if (balance > 1 && Balance(n->Left) < 0)
        {
            n->Left = rotateLeft(n->Left);
            return rotateRight(n);
        }
        if (balance < -1 && Balance(n->Right) <= 0)
        {
            return rotateLeft(n);
        }
        if (balance < -1 && Balance(n->Right) > 0)
        {
            n->Right = rotateRight(n->Right);
            return rotateLeft(n);
        }
        return n;
    }

    int getMachineDataSize(AVL_Node<T>* n, int& size, T machineID)
    {
        if (n != NULL)
        {
            inOrder(n->Left, size, machineID);
            if (n->chainingList.getHead() != NULL)
            {
                if (n->chainingList.getHead()->data <= machineID)
                {
                    size++;
                }
            }
            inOrder(n->Right, size, machineID);
        }
    }

    void getMachineData(AVL_Node<T>* successorTree, AVL_Node<T>* successorRoot, AVL<T>* retrievedAVL, T machineID)
    {
        if (successorTree != NULL)
        {
            getMachineData(successorTree->Left, successorRoot, retrievedAVL, machineID);
            if (successorTree->chainingList.getHead() != NULL)
            {
                if (successorTree->chainingList.getHead()->data <= machineID)
                {
                    AVL_Node<T>* root = retrievedAVL->getRoot();
                    retrievedAVL->insert(root, successorTree->chainingList.getHead()->data, successorTree->chainingList.getHead()->beforeHash, 0);
                    this->remove(successorRoot, 2, successorTree->chainingList.getHead()->data);
                }
            }
            getMachineData(successorTree->Right, successorRoot, retrievedAVL, machineID);

        }
    }
    

    void inOrder(AVL_Node<T>* n) 
    {
        if (n != NULL) 
        {
            inOrder(n->Left);
            if (n->chainingList.getHead() != NULL)
                cout << n->chainingList.getHead()->data << ",";
            inOrder(n->Right);
        }
    }

    AVL_Node<T>* search(AVL_Node <T>* temp, int val)
    {
        if (temp == NULL)
        {
            return temp;
        }
        else if (temp->chainingList.getHead() == NULL)
        {
            cout << "\n--- The Chaining List Is Empty! ---" << endl;
            return NULL;
        }
        else if (val < temp->chainingList.getHead()->data)
        {
            temp->Left = search(temp->Left, val);
        }
        else if (val > temp->chainingList.getHead()->data)
        {
            temp->Right = search(temp->Right, val);
        }
        else if (val == temp->chainingList.getHead()->data)
        {
            return temp;
        }
    }

    // deleting the list of every node of tree
    void deleteTreeList(AVL_Node<T>* n)
    {
        if (n != NULL)
        {
            deleteTreeList(n->Left);
            n->chainingList.clear();
            deleteTreeList(n->Right);
        }
    }

    // deleting the tree itself
    void deleteTree(AVL_Node<T>* n) {
        if (n != NULL) {
            deleteTree(n->Left);
            deleteTree(n->Right);
            delete n;
        }
        n = NULL;
    }

};