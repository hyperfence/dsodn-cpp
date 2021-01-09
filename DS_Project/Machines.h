#pragma once
#include <iomanip>
#include "AVL_Tree.h"
#include "RoutingTable.h"
#include "MachineFile.h"
#include "math.h"

using namespace std;

template <typename D, typename N>
struct Machine_Node
{
	N data;
	Machine_Node<D,N>* next;
	RoutingTable* routingTable;
	AVL<N> tree;
    MachineFile<D> file;
};

template <class D, class T>
class Machines {
private:
    int routingTableSize;
	Machine_Node<D,T>* head;

public:
    Machines()
    {
        this->head = NULL;
    }

    Machines(int space)
    {
        this->routingTableSize = space;
    }

    Machine_Node<D,int>* getHead()
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
        Machine_Node<D, T>* temp = new Machine_Node<D, T>;
        temp->data = value;
        temp->next = NULL;
        temp->routingTable = NULL;
        Machine_Node<D, T>* curr = head;
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
        This function sets the avl tree data member of the specified machine
    */
    void setMachineAVL(AVL<T>* avl)
    {
        head->tree = avl;
    }

    /*
        This function sets the root of avl tree of the specified machine
    */
    void setMachineAVLRoot(AVL_Node<T>* root, T machineID)
    {
        Machine_Node<D, T>* curr = head;
        while (curr->data != machineID) {
            curr = curr->next;
        }
        curr->tree.setRoot(root);
    }

    /*
        This function returns the root of avl tree of the specified machine
    */
    AVL_Node<T>* getMachineAVL(T machineID)
    {
        Machine_Node<D, T>* curr = head;
        while (curr->data != machineID) {
            curr = curr->next;
        }
        return curr->tree.getRoot();
    }

    /*
        This function returns the avl tree object of the specified machine
    */
    AVL<T> getMachineAVLTree(T machineID)
    {
        Machine_Node<D, T>* curr = head;
        while (curr->data != machineID) {
            curr = curr->next;
        }
        return curr->tree;
    }

    /*
        This function deletes the specified machine
    */
    Machine_Node<D,T>* removeMachine(T value) {
        Machine_Node<D, T>* pre = new Machine_Node<D, T>;
        pre = head;
        Machine_Node<D, T>* curr = head;
        while (curr->data != value) {
            pre = curr;
            curr = curr->next;
        }
        
        Machine_Node<D, T>* successorMachine = this->getSuccessorMachine(value);
        Machine_Node<D, T>* predecessorMachine = this->getPredecessorMachine(value);


        Machines <D, T> newObject;
        newObject.head = this->head;

        successorMachine->tree.setRoot(NULL);

        head->tree.adjustMachineDataOnRemove(curr->tree.getRoot(), successorMachine->tree, value, newObject);
        string fname = curr->file.getFilePath() + curr->file.getFileName();
        remove(fname.c_str());
        if (pre == head)
        {
            pre = curr->next;
            predecessorMachine->next = pre;
            head = pre;
        }
        else
        {
            pre->next = curr->next;
        }
        curr->next = NULL;
        curr->routingTable->clearRoutingTable();
        delete curr->routingTable;
        delete curr;
        return pre;
    }

    /*
        This function sorts all the machines in ascending order based on their ID
    */
    void sortMachines() {
        Machine_Node<D,T>* temp1 = head;
        Machine_Node<D,T>* temp2;
        do {
            temp2 = temp1->next;
            while (temp2 != head) {
                if (temp1->data > temp2->data) {
                    int temp = temp1->data;
                    temp1->data = temp2->data;
                    temp2->data = temp;

                    RoutingTable* temproutingTable = temp1->routingTable;
                    temp1->routingTable = temp2->routingTable;
                    temp2->routingTable = temproutingTable;

                    AVL<T> temptree = temp1->tree;
                    temp1->tree = temp2->tree;
                    temp2->tree = temptree;

                    MachineFile<D> tempfile = temp1->file;
                    temp1->file = temp2->file;
                    temp2->file = tempfile;

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
        Machine_Node<D,T>* temp = head;
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
    Machine_Node<D,T>* getMachine(T value)
    {
        Machine_Node<D, T>* machine = NULL;
        Machine_Node<D, T>* ptr = head;
        do
        {
            if (ptr->data == value)
            {
                machine = ptr;
                break;
            }
            ptr = ptr->next;
        } while (ptr != head);
        return machine;
    }

    /*
        This function takes the key of the machine and finds the immediate active routing successor
        and then return that machine else this function will return NULL if machine not found.
    */
    Machine_Node<D,T>* getSuccessorRoutingMachine(T value)
    {
        Machine_Node<D, T>* successor = NULL;
        Machine_Node<D, T>* ptr = head;
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
    Machine_Node<D,T>* getSuccessorMachine(T value)
    {
        Machine_Node<D,T>* successor = NULL;
        Machine_Node<D,T>* ptr = head;
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
        This function takes the key of the machine and finds the immediate active predecessor
        and then return that machine else this function will return NULL if machine not found.
    */
    Machine_Node<D, T>* getPredecessorMachine(T value)
    {
        Machine_Node<D, T>* predecessor = NULL;
        Machine_Node<D, T>* ptr = head;
        while (1) // Infinite Loop Until Successor is found
        {
            if (ptr == NULL)
            {
                break;
            }
            if (ptr->next->data == value)
            {
                predecessor = ptr;
                break;
            }
            ptr = ptr->next;
        }
        return predecessor;
    }

    /*
        This function displays the ring DHT of active machines in a linear manner
    */
    void display() {
        Machine_Node<D,T>* curr = head;
        if (head == NULL)
        {
            cout << "\n No Machines Found" << endl;
            return;
        }
        cout << "\n----------  Machines List  ----------" << endl;
        cout << "|" << endl;
        cout << "|  ";
        do
        {
            cout << curr->data << " -> ";
            curr = curr->next;
        } while (curr != head);
        cout << "--- <- " << head->data << endl;
        cout << "|" << endl;
        cout << "-------------------------------------" << endl << endl;
    }

    /*
        This function returns the address of last machine in the ring DHT
    */
    Machine_Node<D,T>* getLastMachine()
    {
        Machine_Node<D,T>* curr = head;
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
    Machine_Node<D,T>* getFirstMachine()
    {
        Machine_Node<D,T>* curr = head;
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
        Machine_Node<D,T>* ptr = head;
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
        Machine_Node<D, T>* ptr = getMachine(value);
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
    Machine_Node<D,T>* searchResponsibleMachine(T dataKey, T machineKey)
    {
        cout << "\n\n------ Routing Starting From Machine " << setfill('0') << setw(3) << machineKey << " ------" << endl;
        cout << "|" << endl;
        Machine_Node<D,T>* startingMachine = getMachine(machineKey);
        for (int i = 0; i < routingTableSize; i++)
        {
            Machine_Node<D,T>* temp = static_cast<Machine_Node<D,T>*>(startingMachine->routingTable->getElement(i));
            Machine_Node<D,T>* temp2 = static_cast<Machine_Node<D,T>*>(startingMachine->routingTable->getElement(i + 1));
            if (dataKey > getLastMachine()->data)
            {
                cout << "|  Routing From Machine : " << setfill('0') << setw(3) << startingMachine->data << " -> " << setfill('0') << setw(3) << getFirstMachine()->data << endl;
                startingMachine = getFirstMachine();
                cout << "|" << endl;
                cout << "-----------------------------------------------" << endl << endl;
                return startingMachine;
            }
            else if (dataKey < getFirstMachine()->data)
            {
                cout << "|  Routing From Machine : " << setfill('0') << setw(3) << startingMachine->data << " -> " << setfill('0') << setw(3) << getFirstMachine()->data << endl;
                startingMachine = getFirstMachine();
                cout << "|" << endl;
                cout << "-----------------------------------------------" << endl << endl;
                return startingMachine;
            }
            else if (isLastMachine(startingMachine->data) == true && dataKey >= startingMachine->data)
            {
                cout << "|  Routing From Machine: " << setfill('0') << setw(3) << startingMachine->data << " -> " << setfill('0') << setw(3) << getFirstMachine()->data << endl;
                startingMachine = getFirstMachine();
                cout << "|" << endl;
                cout << "-----------------------------------------------" << endl << endl;
                return startingMachine;
            }
            else if (dataKey == startingMachine->data)
            {
                cout << "|  Routing From Machine: " << setfill('0') << setw(3) << startingMachine->data << endl;
                cout << "|" << endl;
                cout << "-----------------------------------------------" << endl << endl;
                return startingMachine;
            }
            else if (temp->data == dataKey)
            {
                cout << "|  Routing From Machine: " << setfill('0') << setw(3) << startingMachine->data << " -> " << setfill('0') << setw(3) << temp->data << endl;
                startingMachine = temp;
                cout << "|" << endl;
                cout << "-----------------------------------------------" << endl << endl;
                return startingMachine;
            }
            else if (dataKey > startingMachine->data && temp->data >= dataKey)
            {
                cout << "|  Routing From Machine: " << setfill('0') << setw(3) << startingMachine->data << " -> " << setfill('0') << setw(3) << temp->data << endl;
                startingMachine = temp;
                cout << "|" << endl;
                cout << "-----------------------------------------------" << endl << endl;
                return startingMachine;
            }
            else if (dataKey > temp->data && temp2 != NULL && dataKey < temp2->data)
            {
                cout << "|  Routing From Machine: " << setfill('0') << setw(3) << startingMachine->data << " -> " << setfill('0') << setw(3) << temp->data << endl;
                startingMachine = temp;
                i = -1;
            }
            else if (dataKey > temp->data && temp2 == NULL)
            {
                cout << "|  Routing From Machine: " << setfill('0') << setw(3) << startingMachine->data << " -> " << setfill('0') << setw(3) << temp->data << endl;
                startingMachine = temp;
                i = -1;
            }
        }
        cout << "|       -NULL-" << endl;
        cout << "-----------------------------------------------" << endl << endl;
        return NULL;
    }


    /*
        This function adjusts routing tables for every machine
    */
    void configureRoutingTable()
    {
        int numOfMachines = this->getTotalSize();
        Machine_Node<D,T>* temp = head;
        cout << "\n-------- Routing Tables of Machines --------" << endl;
        cout << "|" << endl;
        do
        {
            int identifierSpace = pow(2, this->routingTableSize);
            cout << "| -> Machine " << setfill('0') << setw(3) << temp->data << ": ";
            T* routingTable = new T[this->routingTableSize];
            for (int i = 0; i < routingTableSize; i++)
            {
                routingTable[i] = temp->data + pow(2, i);
                if (routingTable[i] > identifierSpace - 1)
                {
                    routingTable[i] = routingTable[i] - identifierSpace;
                }
            }
            if (temp->routingTable != NULL)
            {
                temp->routingTable->clearRoutingTable();
            }
            temp->routingTable = new RoutingTable();
            for (int i = 0; i < routingTableSize; i++)
            {
                Machine_Node<D,T>* nearestActive = this->getSuccessorRoutingMachine(routingTable[i]);
                temp->routingTable->insert(static_cast<void*>(nearestActive));
            }
            // Display the values of routing tables
            for (int i = 0; i < routingTableSize; i++)
            {
                // Now typecast the void pointer back to Machine_Node pointer to access the data
                Machine_Node<D,T>* temp2 = static_cast<Machine_Node<D,T>*>(temp->routingTable->getElement(i));
                cout<< setfill(' ') << setw(3) << temp2->data << "  ";
            }
            temp = temp->next;
            cout << endl;
            delete[] routingTable;
        } while (temp != head);
        cout << "|" << endl;
        cout << "--------------------------------------------" << endl << endl << endl << endl;
    }

    /*
        This function prints the routing table of the machine whose ID is
        passed as argument
    */
    void printMachineRoutingTable(T machineID)
    {
        Machine_Node<D, T>* machine = NULL;
        Machine_Node<D, T>* ptr = head;
        do
        {
            if (ptr->data == machineID)
            {
                machine = ptr;
                break;
            }
            ptr = ptr->next;
        } while (ptr != head);
        if (machine == NULL)
        {
            cout << "\n-------- Routing Table of Machine " << machineID << " --------" << endl;
            cout << "|" << endl;
            cout << "| No Machine Found! " << endl;
            cout << "|" << endl;
            cout << "--------------------------------------------" << endl << endl;
            return;
        }
        cout << "\n-------- Routing Table of Machine " << machineID <<" --------" << endl;
        cout << "|" << endl;
        cout << "| -> Machine " << setfill('0') << setw(3) << machineID << ": ";
        for (int i = 0; i < this->routingTableSize; i++)
        {
            // Typecast the void pointer back to Machine_Node pointer to access the data
            Machine_Node<D, T>* temp = static_cast<Machine_Node<D, T>*>(machine->routingTable->getElement(i));
            cout << setfill(' ') << setw(3) << temp->data << "  ";
        }
        cout << "\n|" << endl;
        cout << "--------------------------------------------" << endl << endl;
    }

    /*
        This functions takes machine ID as an input and display it's 
        AVL tree and file line numbers.
    */
    void displayAVLOfMachine(T MachineID) {
        Machine_Node<D, T>* Machine = getMachine(MachineID);
        cout << "|  >. File Path: " << Machine->file.getFilePath() + Machine->file.getFileName() << endl;
        Machine->tree.displayLineNumber(Machine->tree.getRoot());
    }

    /*
        This function clears up the memory allocated for the active machines 
    */
    void clear() 
    {
        Machine_Node<D,T>* curr = head;
        Machine_Node<D,T>* temp;
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