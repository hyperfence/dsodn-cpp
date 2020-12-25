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

    void insertAt(T n, int index)
    {
        AVL_List_Node<T>* temp = new AVL_List_Node<T>;
        temp->data = n;
        AVL_List_Node<T>* pre = new AVL_List_Node<T>;
        AVL_List_Node<T>* curr = head;
        for (int i = 0; i < index; i++) {
            pre = curr;
            curr = curr->next;
        }
        pre->next = temp;
        temp->next = curr;
    }

    void RemoveByValue(unsigned long long int n) {
        if (head->beforeHash == n) {
            head = NULL;
            delete head;
            return;
        }
        AVL_List_Node<T>* pre = new AVL_List_Node<T>;
        AVL_List_Node<T>* curr = head;
        while (curr->beforeHash != n) {
            pre = curr;
            curr = curr->next;
        }
        pre->next = curr->next;
        curr->next = NULL;
        cout << "Deleted File: " << curr->data << endl;
        delete curr;
    }

    void Remove() {
        AVL_List_Node<T>* curr = head;
        AVL_List_Node<T>* pre = new AVL_List_Node<T>;
        while (curr->next != NULL) {
            pre = curr;
            curr = curr->next;
        }
        pre->next = NULL;
        curr->next = NULL;
        delete curr;
    }

    void RemoveAt(int index) {
        AVL_List_Node<T>* pre = new AVL_List_Node<T>;
        AVL_List_Node<T>* curr = head;
        for (int i = 0; i < index; i++) {
            pre = curr;
            curr = curr->next;
        }
        pre->next = curr->next;
        curr->next = NULL;
        delete curr;
    }

    void replaceAt(T n, int index) {
        AVL_List_Node<T>* curr = head;
        for (int i = 0; i < index; i++) {
            curr = curr->next;
        }
        curr->data = n;
    }

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

    void insertAtMiddle(T n) {
        int len = 0;
        AVL_List_Node<T>* curr = head;
        while (curr->next != NULL) 
        {
            len++;
            curr = curr->next;
        }
        insertAt(n, len / 2 + 1);
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