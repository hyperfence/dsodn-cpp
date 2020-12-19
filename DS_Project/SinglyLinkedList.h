#pragma once
#include <iostream>
#include "MachineFile.h"
using namespace std;

template <class U>
struct node
{
    U data;
    node<U>* next;
    unsigned long long int beforeHash;
    MachineFile file;
};
template <class T>
class AVL_Tree_List
{

public:
    node<T>* head;
    AVL_Tree_List()
    {
        head = NULL;
    }

    void insert(T n)
    {
        node<T>* temp = new node<T>;
        temp->data = n;
        temp->next = NULL;
        node<T>* curr = head;

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
        node<T>* temp = new node<T>;
        temp->data = n;
        node<T>* pre = new node<T>;
        node<T>* curr = head;
        for (int i = 0; i < index; i++) {
            pre = curr;
            curr = curr->next;
        }
        pre->next = temp;
        temp->next = curr;
    }

    void RemoveByValue(T n) {
        node<T>* pre = new node<T>;
        node<T>* curr = head;
        while (curr->data != n) {
            pre = curr;
            curr = curr->next;
        }
        pre->next = curr->next;
        curr->next = NULL;
        delete curr;
    }

    void Remove() {
        node<T>* curr = head;
        node<T>* pre = new node<T>;
        while (curr->next != NULL) {
            pre = curr;
            curr = curr->next;
        }
        pre->next = NULL;
        curr->next = NULL;
        delete curr;
    }

    void RemoveAt(int index) {
        node<T>* pre = new node<T>;
        node<T>* curr = head;
        for (int i = 0; i < index; i++) {
            pre = curr;
            curr = curr->next;
        }
        pre->next = curr->next;
        curr->next = NULL;
        delete curr;
    }

    void replaceAt(T n, int index) {
        node<T>* curr = head;
        for (int i = 0; i < index; i++) {
            curr = curr->next;
        }
        curr->data = n;
    }

    void clear() {
        node<T>* curr;
        while (head != NULL)
        {
            curr = head;
            delete curr;
            head = head->next;
        }
    }

    void display() {
        node<T>* temp = head;
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
        node<T>* temp1 = head;
        node<T>* temp2;
        while (temp1->next != NULL) {
            temp2 = temp1->next;
            while (temp2 != NULL) {
                if (temp1->data > temp2->data) {
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
        node<T>* curr = head;
        while (curr->next != NULL) {
            len++;
            curr = curr->next;
        }
        insertAt(n, len / 2 + 1);
    }

    ~AVL_Tree_List() {
        //clear();
        delete head;
    }
};