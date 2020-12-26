#pragma once

#include <iostream>
#include "Machines.h"
#include "AVL_Tree_Lists.h"
#include <string>

// forward declaration..
template <typename D, typename N>
struct Machine_Node;

template <class D, class T>
class Machines;

//////////////////////////
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

        AVL_Node<T>* searchNode = search(n,value);
       
        if(searchNode->chainingList.getHead()->next != NULL)
        {
            searchNode->chainingList.setAVLTreeList(searchNode->chainingList.RemoveByValue(befHash));
            return n;
        }

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

    void adjustMachineData(AVL_Node<T>* successorTree, AVL_Node<T>* successorRoot, AVL<T>* retrievedAVL, T machineID, T predecessorID, Machine_Node <string,T>* newMachine)
    {
        if (successorTree != NULL)
        {
            adjustMachineData(successorTree->Left, successorRoot, retrievedAVL, machineID, predecessorID,newMachine);
            if (successorTree->chainingList.getHead() != NULL)
            {
                if (successorTree->chainingList.getHead()->data <= machineID)
                {
                    AVL_List_Node<T>* succTreeChainingList = successorTree->chainingList.getHead();
                    while (succTreeChainingList != NULL)
                    {
                        AVL_Node<T>* root = retrievedAVL->getRoot();
                        // Create The File of this Machine
                        // Then Insert the Data by calling succtreeChainingList->data
                        // Then insert the line number in the below function
                        //Machines <string, T> tempObject;
                        //Machine_Node <string, T>* predecessorMachine = tempObject.getPredecessorMachine(newMachine->data);


                      //  string valueInserted = succTreeChainingList->valLineNumber
                        
                        newMachine->file.increaseFileLineNumber(1);
                        newMachine->file.insert(to_string(succTreeChainingList->data));
                        retrievedAVL->setRoot(retrievedAVL->insert(root, succTreeChainingList->data, succTreeChainingList->beforeHash, newMachine->file.getFileLineNumber()));
                        successorRoot = this->remove(successorRoot, succTreeChainingList->data, succTreeChainingList->beforeHash);
                        succTreeChainingList = successorTree->chainingList.getHead();
                    }
                }
                else if (successorTree->chainingList.getHead() != NULL && successorTree->chainingList.getHead()->data > machineID && predecessorID > machineID)
                {
                    AVL_List_Node<T>* succTreeChainingList = successorTree->chainingList.getHead();
                    while (succTreeChainingList != NULL)
                    {
                        AVL_Node<T>* root = retrievedAVL->getRoot();
                        newMachine->file.increaseFileLineNumber(1);
                        newMachine->file.insert(to_string(succTreeChainingList->data));
                        // Create The File of this Machine
                        // Then Insert the Data by calling succtreeChainingList->data
                        // Then insert the line number in the below function
                        retrievedAVL->setRoot(retrievedAVL->insert(root, succTreeChainingList->data, succTreeChainingList->beforeHash, newMachine->file.getFileLineNumber()));
                        successorRoot = this->remove(successorRoot, succTreeChainingList->data, succTreeChainingList->beforeHash);
                        succTreeChainingList = successorTree->chainingList.getHead();
                    }
                }      
            }
            adjustMachineData(successorTree->Right, successorRoot, retrievedAVL, machineID, predecessorID, newMachine);
        }
    }
    
    void adjustMachineDataOnRemove(AVL_Node<T>* currentTree, AVL<T>* successorTree, T machineID, T predecessorID)
    {
        if (successorTree != NULL)
        {
            adjustMachineDataOnRemove(currentTree->Left, successorTree, machineID, predecessorID);
            if (currentTree->chainingList.getHead() != NULL)
            {
                if (currentTree->chainingList.getHead()->data <= machineID)
                {
                    AVL_List_Node<T>* currTreeChainingList = currentTree->chainingList.getHead();
                    while (currTreeChainingList != NULL)
                    {
                        AVL_Node<T>* root = successorTree->getRoot();
                        successorTree->setRoot(successorTree->insert(root, currTreeChainingList->data, currTreeChainingList->beforeHash, 0));
                        currTreeChainingList = currTreeChainingList->next;
                    }
                }
                else if (currentTree->chainingList.getHead() != NULL && currentTree->chainingList.getHead()->data > machineID && predecessorID > machineID)
                {
                    AVL_List_Node<T>* currTreeChainingList = currentTree->chainingList.getHead();
                    while (currTreeChainingList != NULL)
                    {
                        AVL_Node<T>* root = successorTree->getRoot();
                        successorTree->setRoot(successorTree->insert(root, currTreeChainingList->data, currTreeChainingList->beforeHash, 0));
                        currTreeChainingList = currTreeChainingList->next;
                    }
                }
            }
            adjustMachineDataOnRemove(currentTree->Right, successorTree, machineID, predecessorID);
        }
    }

    void inOrder(AVL_Node<T>* n) 
    {
        if (n != NULL) 
        {
            inOrder(n->Left);
            // We can add a loop here till the end of singly list to display content of that list
            if (n->chainingList.getHead() == NULL)
            {
                return;
            }
            AVL_List_Node<T>* treeChainingList = n->chainingList.getHead();
            cout << "| -> ";
            while (treeChainingList != NULL)
            {
                cout << treeChainingList->data << " >> ";
                treeChainingList = treeChainingList->next;
            }
            cout << "NULL" << endl;
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