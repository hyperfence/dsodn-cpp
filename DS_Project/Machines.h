#pragma once
#include "AVL_Tree.h"
#include "RoutingTable.h"

using namespace std;

template <typename N>
struct Machine_Node
{
	N data;
	Machine_Node<N>* next;
	RoutingTable* routingTable;
	AVL<N> tree;
};

template <class T>
class Machines {
private:
    int routingTableSize;
	Machine_Node<T>* head;

public:
	Machines()
	{
        this->head = NULL;
	}

    Machines(int identifierSpace)
    {
        identifierSpace = log2(identifierSpace);
        this->routingTableSize = identifierSpace;
    }

    void insert(T value)
    {
        Machine_Node<T>* temp = new Machine_Node<T>;
        temp->data = value;
        temp->next = NULL;
        temp->routingTable = NULL;
        Machine_Node<T>* curr = head;
        if (this->head == NULL)
        {
            temp->next = temp;
            head = temp;
        }
        else if (curr->data >= temp->data)
        {
            while (curr->next != head)
            {
                curr = curr->next;
            }
            curr->next = temp;
            temp->next = head;
            head = temp;
        }
        else
        {
            while (curr->next != head && curr->next->data < temp->data)
                curr = curr->next;

            temp->next = curr->next;
            curr->next = temp;
        }
    }

    void remove(T value) {
        Machine_Node<T>* pre = new Machine_Node<T>;
        Machine_Node<T>* curr = head;
        while (curr->data != value) {
            pre = curr;
            curr = curr->next;
        }
        pre->next = curr->next;
        curr->next = NULL;
        delete curr;
    }

    void sort() {
        Machine_Node<T>* temp1 = head;
        Machine_Node<T>* temp2;
        do {
            temp2 = temp1->next;
            while (temp2 != head) {
                if (temp1->data > temp2->data) {
                    int temp = temp1->data;
                    temp1->data = temp2->data;
                    temp2->data = temp;
                }
                temp2 = temp2->next;
            }
            temp1 = temp1->next;
        } while (temp1->next != head);
    }

    void clear() {
        Machine_Node<T>* curr = head;
        Machine_Node<T>* temp;
        do
        {
            temp = curr;
            curr = curr->next;
            delete temp;
        } while (curr != head);
        head = NULL;
    }

    int getTotalSize()
    {
        int size = 0;
        Machine_Node<T>* temp = head;
        do
        {
            temp = temp->next;
            size++;
        } while (temp != head);
        return size;
    }

    Machine_Node<T>* getSuccessorMachine(T value)
    {
        Machine_Node<T>* successor = new Machine_Node<T>();
        successor = NULL;
        Machine_Node<T>* ptr = head;
        while(1) // Infinite Loop Until Successor is found
        {
            if (ptr->data >= value)
            {
                successor = ptr;
                break;
            }
            ptr = ptr->next;
            if (ptr == head)
            {
                successor = ptr;
                break;
            }
        }
        return successor;
    }

    void display() {
        Machine_Node<T>* curr = head;
        if (head == NULL)
        {
            cout << "Empty List" << endl;
            return;
        }
        do
        {
            cout << curr->data << " -> ";
            curr = curr->next;
        } while (curr != head);
        cout << "NULL" << endl;
    }
    bool search(T value)
    {
        bool flag = false;
        Machine_Node<T>* ptr = head;
        do {
            if (ptr->data == value)
            {
                flag = true;
            }     
            ptr = ptr->next;
        } while (ptr != head);
        return flag;
    }

    /*
        This function adjusts routing tables for every machine
    */
	void configureRoutingTable()
	{
        int numOfMachines = this->getTotalSize();
        Machine_Node<T>* temp = head;
        do
        {
            int identifierSpace = pow(2,this->routingTableSize);
            cout << "Machine " << temp->data << ": ";
            T* routingTable = new T[this->routingTableSize];
            for (int i=0; i<routingTableSize; i++)
            {
                routingTable[i] = temp->data + pow(2,i);
                if (routingTable[i] > identifierSpace-1)
                {
                    routingTable[i] = routingTable[i] - identifierSpace;
                }
            }
            for (int i = 0; i < routingTableSize; i++)
            {
                Machine_Node<T>* nearestActive = this->getSuccessorMachine(routingTable[i]);
                if (temp->routingTable == NULL) //The routing table is empty
                {
                    temp->routingTable = new RoutingTable();
                    temp->routingTable->insert(static_cast<void*>(nearestActive));                   
                }
                else // The routing table is not empty. So lets assign the machine to its end
                {
                    temp->routingTable->insert(static_cast<void*>(nearestActive));
                }
            }
            for (int i = 0; i < routingTableSize; i++)
            {
                Machine_Node<T>* temp2 = static_cast<Machine_Node<T>*>(temp->routingTable->getElement(i));
                cout << " " << temp2->data;
            }
            temp = temp->next;
            cout << endl;
        } while (temp != head);
        
	}
};