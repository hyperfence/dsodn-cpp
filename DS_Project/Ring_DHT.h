#pragma once

#include "Machines.h"
#include <sstream>

template <class T>
class RingDHT {
private:
    int noOfmachines;
    int identifierSpace;
    Machines<int> machines;

public:

    RingDHT(int space, int no_machines) 
    {
        identifierSpace = space;
        noOfmachines = no_machines;
        machines.setidentifierSpace(identifierSpace);
    }

    Machines<int> getMachines()
    {
        return machines;
    }

    int HashFunction(string key, unsigned long long* befHash)
    {
        unsigned long long int hashedValue = 0;
        int length = key.size();
        if (key.size() > 8)
        {
            length = 8;
        }
        for (int i = 0; i < length; i++)
        {
            hashedValue = 37 * hashedValue + key[i];
        }
        *befHash = hashedValue;
        return hashedValue % (int)pow(2, identifierSpace);
    }

    void insert(string key, string value, int machineID)
    {
        unsigned long long int beforeHashVal = 0;
        int hash = HashFunction(key, &beforeHashVal);

        Machine_Node<int>* curr = machines.searchResponsibleMachine(hash, machineID);
        curr->file.insert(value);
        curr->file.increaseFileLineNumber(1);
        curr->tree.setRoot(curr->tree.insert(curr->tree.getRoot(), hash, beforeHashVal, curr->file.getFileLineNumber()));

    }

    void autoAssigning()
    {
        for (int i = 0; i < noOfmachines; i++) {
            machines.insertMachine(-1);
        }
        Machine_Node<int>* searchPtr = machines.getFirstMachine();
        do {
            unsigned long long int befHash = 0;
            int value = -1;

            string addressInString = to_string((long)searchPtr);

            //ostringstream address;
            //address << searchPtr;
            //string addressInString = address.str();

            value = HashFunction(addressInString,&befHash);
            while (machines.machineExists(value) == true)
            {
                value++;
                value = value % (int)pow(2, identifierSpace);
            }
            searchPtr->data = value;
            searchPtr->file.setFileName(value);
            searchPtr = searchPtr->next;
        } while (searchPtr != machines.getFirstMachine());
        machines.sortMachines();
        machines.configureRoutingTable();
        searchPtr = machines.getFirstMachine();
        do {
            searchPtr->file.setFileName(searchPtr->data);
            searchPtr = searchPtr->next;
        } while (searchPtr != machines.getFirstMachine());
    }

    // getting values from user manually 
    void manualAssigning()
    {
        cout << "Enter values for machines respectively: \n";
        int value = -1;
        for (int i = 0; i < noOfmachines; i++)
        {
            cout << "Value # " << (i + 1) << " : " << endl;
            cin >> value;
            while (value < 0 || value > pow(2, identifierSpace) || (i > 0 && machines.machineExists(value) == true)) // check for unique number and for number between identifier space
            {
                cout << "Error!\nPlease input a value;\n1) Less than total number of machines!\n2) Greater than zero\n3) Unique\nYour Input: ";
                cin >> value;
            }
            machines.insertMachine(value);
        }
        machines.sortMachines();
        machines.configureRoutingTable();
        Machine_Node<int>* searchPtr = machines.getFirstMachine();
        do {

            searchPtr->file.setFileName(searchPtr->data);
            searchPtr = searchPtr->next;
        } while (searchPtr != machines.getFirstMachine());
    }

    void removeData(T key, int machineID)
    {
        unsigned long long int beforeHashVal = 0;
        int hash = HashFunction(key, &beforeHashVal);

        Machine_Node<int>* curr = machines.searchResponsibleMachine(hash, machineID);
        AVL_Node<int>* tempPtr = curr->tree.search(curr->tree.getRoot(), hash);
        if (tempPtr != NULL && (tempPtr->chainingList.searchBefHash(beforeHashVal) == true))
        {
            AVL_List_Node<int>* listNode = tempPtr->chainingList.searchNode(beforeHashVal);
            if (listNode != NULL) {
                int lineNumber = listNode->valLineNumber;
                curr->file.remove(lineNumber);
                cout << "\nData succesfully removed!\n";
                return;
            }
        }
        cout << "\n404 Error. Data not found!\n";
    }

    T searchData(T key, int machineID)
    {
        unsigned long long int beforeHashVal = 0;
        int hash = HashFunction(key, &beforeHashVal);

        Machine_Node<int>* curr = machines.searchResponsibleMachine(hash, machineID);
        AVL_Node<int>* tempPtr = curr->tree.search(curr->tree.getRoot(), hash);
        if (tempPtr != NULL && (tempPtr->chainingList.searchBefHash(beforeHashVal) == true))
        {
            AVL_List_Node<int>* listNode = tempPtr->chainingList.searchNode(beforeHashVal);
            if (listNode != NULL) {
                int lineNumber = listNode->valLineNumber;
                cout << "\n----------------------------------------------------\n";
                cout << "File Name : " << curr->file.getFileName() << endl;
                cout << "Line Number : " << lineNumber << endl;
                return "Data Value : " + curr->file.search(lineNumber);
                cout << "\n----------------------------------------------------\n";
            }
        }
    }

    /*
        This function frees all memory used by the List in nodes of AVL trees
    */
    void clearAVLTreeListMemory()
    {
        Machine_Node<int>* curr = machines.getHead();
        do
        {
            curr->tree.deleteTreeList(curr->tree.getRoot());
            curr = curr->next;
        } while (curr != machines.getHead());
    }

    /*
        This function frees all memory used by AVL trees itself
    */
    void clearAVLTreeMemory()
    {
        Machine_Node<int>* curr = machines.getHead();
        do
        {
            curr->tree.deleteTree(curr->tree.getRoot());
            curr = curr->next;
        } while (curr != machines.getHead());
    }

    /*
        This function frees all memory used by the machines
    */
    void clearAllMachineMemory()
    {
        machines.clear();
    }

    ~RingDHT()
    {
    }
};