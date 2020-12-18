#pragma once
#include <iostream>

using namespace std;

template <class T>
class singlyCircularList
{
    template <class U>
    struct node
    {
        U data;
        node* next;
    };
    node<T>* head;
public:
    singlyCircularList()
    {
        head = NULL;
    }

    void insert(T value)
    {
        node<T>* temp = new node<T>;
        temp->data = value;
        temp->next = NULL;
        node<T>* curr = head;

        if (head == NULL)
        {
            head = temp;
            temp->next = head;
        }
        else
        {
            do {
                curr = curr->next;
            } while (curr->next != head);

            curr->next = temp;
            temp->next = head;
        }
    }

    void Remove(T value) {
        node<T>* pre = new node<T>;
        node<T>* curr = head;
        while (curr->data != value) {
            pre = curr;
            curr = curr->next;
        }
        pre->next = curr->next;
        curr->next = NULL;
        delete curr;
    }

    void clear() {
        node<T>* curr = head;
        node<T>* temp;
        do
        {
            temp = curr;
            curr = curr->next;
            delete temp;
        } while (curr != head);
        head = NULL;
    }

    void display() {
        node<T>* curr = head;
        if (head == NULL)
        {
            cout << "Empty List" << endl;
            return;
        }
        do
        {
            cout << curr->data << " ";
            curr = curr->next;
        } while (curr != head);
    }

};