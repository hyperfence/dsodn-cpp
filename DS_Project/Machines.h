#pragma once
#include "AVL_Tree.h"
#include "RoutingTable.h"
#include "MachineFile.h"

using namespace std;

template <typename N>
struct Machine_Node
{
	N data;
	Machine_Node<N>* next;
	RoutingTable* routingTable;
	AVL<N> tree;
    MachineFile file;
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

    Machines(int space)
    {
        this->routingTableSize = space;
    }

    Machine_Node<int>* getHead()
    {
        return head;
    }

    /*
        This function sets the identifier space of the DHT
    */
    void setidentifierSpace(int space) 
    {
        this->routingTableSize = space;
    }

    /*
        This function inserts a machine and performs insertion sort at the same time
    */
    void insertMachine(T value)
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

    /*
        This function deletes the specified machine
    */
    void removeMachine(T value) {
        Machine_Node<T>* pre = new Machine_Node<T>;
        Machine_Node<T>* curr = head;
        while (curr->data != value) {
            pre = curr;
            curr = curr->next;
        }
        pre->next = curr->next;
        curr->next = NULL;
        curr->routingTable->clearRoutingTable();
        delete curr->routingTable;
        delete curr;
    }

    /*
        This function sorts all the machines in ascending order based on their ID
    */
    void sortMachines() {
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

    /*
        This function returns the total number of active machines in the DHT
    */
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

    /*
        This function takes the key of the machine and returns that specific machine if
        found else this function will return NULL if machine not found.
    */
    Machine_Node<T>* getMachine(T value)
    {
        Machine_Node<T>* successor = NULL;
        Machine_Node<T>* ptr = head;
        do
        {
            if (ptr->data == value)
            {
                successor = ptr;
                break;
            }
            ptr = ptr->next;
        } while (ptr != head);
        return successor;
    }

    /*
        This function takes the key of the machine and finds the immediate active routing successor
        and then return that machine else this function will return NULL if machine not found.
    */
    Machine_Node<T>* getSuccessorRoutingMachine(T value)
    {
        Machine_Node<T>* successor = NULL;
        Machine_Node<T>* ptr = head;
        while (1) // Infinite Loop Until Successor is found
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

    /*
        This function takes the key of the machine and finds the immediate active successor
        and then return that machine else this function will return NULL if machine not found.
    */
    Machine_Node<T>* getSuccessorMachine(T value)
    {
        Machine_Node<T>* successor = NULL;
        Machine_Node<T>* ptr = head;
        while (1) // Infinite Loop Until Successor is found
        {
            if (ptr->data > value)
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

    /*
        This function displays the ring DHT of active machines in a linear manner
    */
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

    /*
        This function returns the address of last machine in the ring DHT
    */
    Machine_Node<T>* getLastMachine()
    {
        Machine_Node<T>* curr = head;
        if (head == NULL)
        {
            return NULL;
        }
        do
        {
            curr = curr->next;
        } while (curr->next != head);
        return curr;
    }

    /*
        This function returns the address of first machine in the ring DHT
    */
    Machine_Node<T>* getFirstMachine()
    {
        Machine_Node<T>* curr = head;
        if (head == NULL)
        {
            return NULL;
        }
        return curr;
    }

    /*
        This function returns true if the machine exists in the DHT
    */
    bool machineExists(T value)
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
        This function returns true if the machine is in last place of the DHT Ring
    */
    bool isLastMachine(T value)
    {
        Machine_Node<T>* ptr = getMachine(value);
        if (ptr->next == this->head)
        {
            return true;
        }
        return false;
    }

    /*
        This function returns true if the machine is in first place of the DHT Ring
    */
    bool isFirstMachine(T value)
    {
        if (this->head->data == value)
        {
            return true;
        }
        return false;
    }

    /*
        This function takes hashed key of data and machine from the Ring_DHT class and then
        performs the search according to the given keys
    */
    Machine_Node<T>* searchResponsibleMachine(T dataKey, T machineKey)
    {
        cout << "\n...... Searching From Machine " << machineKey << " ......" << endl << endl;
        Machine_Node<T>* startingMachine = getMachine(machineKey);
        for (int i = 0; i < routingTableSize; i++)
        {
            //Machine_Node<T>* temp = new Machine_Node<T>();
            //Machine_Node<T>* temp2 = new Machine_Node<T>();
            Machine_Node<T>* temp = static_cast<Machine_Node<T>*>(startingMachine->routingTable->getElement(i));
            Machine_Node<T>* temp2 = static_cast<Machine_Node<T>*>(startingMachine->routingTable->getElement(i + 1));
            if (dataKey > getLastMachine()->data)
            {
                cout << "  Reached Machine : " << startingMachine->data << " -> " << getFirstMachine()->data << endl;
                startingMachine = getFirstMachine();
                cout << "\n......      Search Ended      ......" << endl << endl;
                return startingMachine;
            }
            else if (dataKey < getFirstMachine()->data)
            {
                cout << "  Reached Machine : " << startingMachine->data << " -> " << getFirstMachine()->data << endl;
                startingMachine = getFirstMachine();
                cout << "\n......      Search Ended      ......" << endl << endl;
                return startingMachine;
            }
            else if (isLastMachine(startingMachine->data) == true && dataKey >= startingMachine->data)
            {
                cout << "  Reached Machine: " << startingMachine->data << " -> " << getFirstMachine()->data << endl;
                startingMachine = getFirstMachine();
                cout << "\n......      Search Ended      ......" << endl << endl;
                return startingMachine;
            }
            else if (dataKey == startingMachine->data)
            {
                cout << "  Reached Machine: " << startingMachine->data << endl;
                cout << "\n......      Search Ended      ......" << endl << endl;
                return startingMachine;
            }
            else if (temp->data == dataKey)
            {
                cout << "  Reached Machine: " << startingMachine->data << " -> " << temp->data << endl;
                startingMachine = temp;
                cout << "\n......      Search Ended      ......" << endl << endl;
                return startingMachine;
            }
            else if (dataKey > startingMachine->data && temp->data >= dataKey)
            {
                cout << "  Reached Machine: " << startingMachine->data << " -> " << temp->data << endl;
                startingMachine = temp;
                cout << "\n......      Search Ended      ......" << endl << endl;
                return startingMachine;
            }
            else if (dataKey > temp->data && temp2 != NULL && dataKey < temp2->data)
            {
                cout << "  Reached Machine: " << startingMachine->data << " -> " << temp->data << endl;
                startingMachine = temp;
                i = -1;
            }
            else if (dataKey > temp->data && temp2 == NULL)
            {
                cout << "  Reached Machine: " << startingMachine->data << " -> " << temp->data << endl;
                startingMachine = temp;
                i = -1;
            }
        }
        cout << "\n......      Search Ended      ......" << endl << endl;
        return NULL;
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
            int identifierSpace = pow(2, this->routingTableSize);
            cout << "Machine " << temp->data << ": ";
            T* routingTable = new T[this->routingTableSize];
            for (int i = 0; i < routingTableSize; i++)
            {
                routingTable[i] = temp->data + pow(2, i);
                if (routingTable[i] > identifierSpace - 1)
                {
                    routingTable[i] = routingTable[i] - identifierSpace;
                }
            }
            for (int i = 0; i < routingTableSize; i++)
            {
                Machine_Node<T>* nearestActive = this->getSuccessorRoutingMachine(routingTable[i]);
                if (temp->routingTable == NULL) //The routing table is empty
                {
                    temp->routingTable = new RoutingTable();
                    // Typecast the Machine_Node pointer to void pointer to store it in routing_tables linked list
                    temp->routingTable->insert(static_cast<void*>(nearestActive));
                }
                else // The routing table is not empty. So lets assign the machine to its end
                {
                    // Typecast the Machine_Node pointer to void pointer to store it in routing_tables linked list
                    temp->routingTable->insert(static_cast<void*>(nearestActive));
                }
            }
            // Display the values of routing tables
            for (int i = 0; i < routingTableSize; i++)
            {
                // Now typecast the void pointer back to Machine_Node pointer to access the data
                Machine_Node<T>* temp2 = static_cast<Machine_Node<T>*>(temp->routingTable->getElement(i));
                cout << " " << temp2->data;
            }
            temp = temp->next;
            cout << endl;
            delete[] routingTable;
        } while (temp != head);
    }

    /*
        This function clears up the memory allocated for the active machines 
    */
    void clear() 
    {
        Machine_Node<T>* curr = head;
        Machine_Node<T>* temp;
        do
        {
            temp = curr;
            curr = curr->next;
            temp->routingTable->clearRoutingTable(); // This will clear the memory allocated for routing tables
            delete temp->routingTable;
            delete temp;
        } while (curr != head);
        head = NULL;
    }
};