#pragma once

#include "Machines.h"
#include <sstream>

template <typename D, typename T>
class RingDHT {
private:
    int noOfmachines;
    int identifierSpace;
    Machines<D, T> machines;

public:

    RingDHT(int space, int no_machines) 
    {
        identifierSpace = space;
        noOfmachines = no_machines;
        machines.setidentifierSpace(identifierSpace);
    }

    Machines<D,T> getMachines()
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

        Machine_Node<D,T>* curr = machines.searchResponsibleMachine(hash, machineID);
        curr->file.insert(value);
        curr->file.increaseFileLineNumber(1);
        curr->tree.setRoot(curr->tree.insert(curr->tree.getRoot(), hash, beforeHashVal, curr->file.getFileLineNumber()));

    }

    void autoAssigning()
    {
        for (int i = 0; i < noOfmachines; i++) {
            machines.insertMachine(-1);
        }
        Machine_Node<D,T>* searchPtr = machines.getFirstMachine();
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
            // function adjusts machine data .... paramater 
        }
        machines.sortMachines();
        machines.configureRoutingTable();
        Machine_Node<D,T>* searchPtr = machines.getFirstMachine();
        do {

            searchPtr->file.setFileName(searchPtr->data);
            searchPtr = searchPtr->next;
        } while (searchPtr != machines.getFirstMachine());
    }

    void insertMachineOnRuntime(int value)
    {
        Machine_Node<D, T>* successorMachine = machines.getSuccessorMachine(0);
        machines.insertMachine(value);
        machines.sortMachines();
        machines.configureRoutingTable();
        AVL<T>* retrievedAVL = new AVL<T>;
        AVL_Node<T>* successorRoot = machines.getMachineAVL(successorMachine->data);
        retrievedAVL->getMachineData(successorRoot, successorRoot, retrievedAVL, value);
        cout << "\n\nIn order of the AVL: " << endl;
        retrievedAVL->inOrder(retrievedAVL->getRoot());
        cout << "\n\nIn order ended" << endl;
        cout << "\n\n--- In order of Machine " << 2<< " AVL Tree ---" << endl;
        machines.getMachineAVLTree(2).inOrder(machines.getMachineAVL(2));
        cout << "\n--------- In order Ended ---------" << endl;
    }

    D removeData(D key, T machineID)
    {
        unsigned long long int beforeHashVal = 0;
        int hash = HashFunction(key, &beforeHashVal);
        D removedData = "";

        Machine_Node<D,T>* curr = machines.searchResponsibleMachine(hash, machineID);
        if (curr == NULL)
        {
            cout << "\n --- No Responsible Machine Found For Key: "<< key <<" ---" << endl;
            return "";
        }
        AVL_Node<T>* tempPtr = curr->tree.search(curr->tree.getRoot(), hash);

        if (tempPtr != NULL && (tempPtr->chainingList.searchBefHash(beforeHashVal) == true))
        {
            AVL_List_Node<T>* listNode = tempPtr->chainingList.searchNode(beforeHashVal);
            if (listNode != NULL) {
                int lineNumber = listNode->valLineNumber;
                removedData = curr->file.remove(lineNumber);
                //tempPtr->chainingList.RemoveByValue(beforeHashVal);
                tempPtr = machines.getMachineAVLTree(curr->data).remove(tempPtr, hash, beforeHashVal);
                //machines.setMachineAVLRoot(tempPtr);
                cout << "\n\n--- In order of Machine " << curr->data << " AVL Tree ---" << endl;
                machines.getMachineAVLTree(curr->data).inOrder(machines.getMachineAVL(curr->data));
                cout << "\n--------- In order Ended ---------" << endl;
                cout << "\nData succesfully removed!\n";
                return removedData;
            }
        }
        cout << "\nData not found!\n";
        return removedData;   
    }

    D searchData(D key, T machineID)
    {
        unsigned long long int beforeHashVal = 0;
        int hash = HashFunction(key, &beforeHashVal);

        string finalOutput = "";

        Machine_Node<D, T>* curr = machines.searchResponsibleMachine(hash, machineID);
        AVL_Node<T>* tempPtr = curr->tree.search(curr->tree.getRoot(), hash);
        if (tempPtr != NULL && (tempPtr->chainingList.searchBefHash(beforeHashVal) == true))
        {
            AVL_List_Node<T>* listNode = tempPtr->chainingList.searchNode(beforeHashVal);
            if (listNode != NULL) {
                int lineNumber = listNode->valLineNumber;
                finalOutput += "\n---------- Searching Data From Machine "+to_string(machineID);
                finalOutput += " ----------\n";
                finalOutput += "|\n";
                finalOutput += "| File Name:   "+ curr->file.getFileName()+"\n";
                finalOutput += "| Line Number: "+ to_string(lineNumber) + "\n";
                finalOutput += "| Found Data:  "+ curr->file.search(lineNumber);
                finalOutput += "\n|";
                finalOutput += "\n----------------------------------------------------\n\n";
                return finalOutput;
            }
        }
        return finalOutput;
    }

    /*
        This function frees all memory used by the List in nodes of AVL trees
    */
    void clearAVLTreeListMemory()
    {
        Machine_Node<D, T>* curr = machines.getHead();
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
        Machine_Node<D,T>* curr = machines.getHead();
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