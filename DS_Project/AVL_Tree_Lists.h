#pragma once

#include <iostream>

using namespace std;

template <class U>
struct AVL_List_Node
{
    U data;
    AVL_List_Node<U>* next;
    unsigned long long int beforeHash;
    int valLineNumber = 0;

};

template <class T>
class AVL_Tree_List
{
private:
    AVL_List_Node<T>* head;

public:

    AVL_Tree_List()
    {
        head = NULL;
    }

    AVL_List_Node<T>* getHead()
    {
        return head;
    }

    /*
        This function simply inserts the lineNumber and Hash in the singly LinkedList
    */
    void insert(T n, unsigned long long int befHash, int lineNumber)
    {
        AVL_List_Node<T>* temp = new AVL_List_Node<T>;
        temp->data = n;
        temp->beforeHash = befHash;
        temp->valLineNumber = lineNumber;
        temp->next = NULL;
        AVL_List_Node<T>* curr = head;

        if (head == NULL)
        {
            head = temp;
        }
        else
        {
            while (curr->next != NULL)
                curr = curr->next;
            curr->next = temp;
        }
    }

    void setAVLTreeList(AVL_List_Node<T>* list)
    {
        head = list;
    }

    /*
        This function removes the node by taking value
    */
    AVL_List_Node<T>* RemoveByValue(unsigned long long int n) {
        if (head->beforeHash == n && head->next == NULL) {
            head = NULL;
            delete head;
            return NULL;
        }
        AVL_List_Node<T>* mainList = head;
        AVL_List_Node<T>* traverseList = head;
        while (traverseList != NULL) {
            if (traverseList->beforeHash == n)
            {
                if (traverseList == mainList)
                {
                    head = traverseList->next;
                    cout << "\n------- Chaining List Data Removed -------" << endl;
                    cout << "|" << endl;
                    cout << "| Deleted Data Key:  " << traverseList->data << endl;
                    cout << "| Deleted Data Hash: " << traverseList->beforeHash << endl;
                    cout << "|" << endl;
                    cout << "------------------------------------------" << endl << endl;
                    AVL_List_Node<T>* delNode = new AVL_List_Node<T>();
                    delNode = traverseList;
                    delNode->next == NULL;
                    delete delNode;
                    break;
                }
                mainList->next = traverseList->next;
                cout << "\n------- Chaining List Data Removed -------" << endl;
                cout << "|" << endl;
                cout << "| Deleted Data Key:  " << traverseList->data << endl;
                cout << "| Deleted Data Hash: " << traverseList->beforeHash << endl;
                cout << "|" << endl;
                cout << "------------------------------------------" << endl << endl;
                AVL_List_Node<T>* delNode = new AVL_List_Node<T>();
                delNode = traverseList;
                delNode->next == NULL;
                delete delNode;
                break;
            }
            mainList = traverseList;
            traverseList = traverseList->next;
        }
        return head;
    }

    /*
        This function clears/delete the singly chaining List
    */
    void clear() {
        AVL_List_Node<T>* curr = head;
        AVL_List_Node<T>* next;
        while (curr != NULL)
        {
            next = curr->next;
            delete curr;
            curr = next;
        }
        head = NULL;
    }

    /*
        This function displays the singly chaining List
    */
    void display() {
        AVL_List_Node<T>* temp = head;
        if (head == NULL)
        {
            cout << "Empty AVL_Tree_List";
        }
        while (temp != NULL)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
    }

    /*
        This function sorts the singly chaining List
    */
    void sort() {
        AVL_List_Node<T>* temp1 = head;
        AVL_List_Node<T>* temp2;
        while (temp1->next != NULL) 
        {
            temp2 = temp1->next;
            while (temp2 != NULL) 
            {
                if (temp1->data > temp2->data) 
                {
                    T temp = temp1->data;
                    temp1->data = temp2->data;
                    temp2->data = temp;
                }
                temp2 = temp2->next;
            }
            temp1 = temp1->next;
        }
    }

    /*
        This function search for the value of beforeHash
        on each node of singly linked list.
    */
    bool searchBefHash(unsigned long long int befHash)
    {
        AVL_List_Node<T>* searchPtr = head;
        while (searchPtr != NULL)
        {
            if (searchPtr->beforeHash == befHash)
                return true;
            searchPtr = searchPtr->next;
        }
        return false;
    }

    /*
        This function seacrhes the node in singly LinkedList based on value and returns it
    */
    AVL_List_Node<T>* searchNode(unsigned long long int befHash)
    {
        AVL_List_Node<T>* searchPtr = head;
        while (searchPtr != NULL)
        {
            if (searchPtr->beforeHash == befHash)
                return searchPtr;
            searchPtr = searchPtr->next;
        }
        return NULL;
    }

    ~AVL_Tree_List() 
    {
        
    }
};