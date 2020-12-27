#pragma once
#include "Machines.h"
template <typename D, typename T>
class RingDHT {

private:
    T noOfmachines;
    T identifierSpace;
    Machines<D, T> machines;

public:
    /*
        Default Constructors && Parameterized Constructor.
    */
    RingDHT()
    {
        identifierSpace = 0;
        noOfmachines = 0;
        machines.setidentifierSpace(0);
    }
    RingDHT(T space, T no_machines) 
    {
        identifierSpace = space;
        noOfmachines = no_machines;
        machines.setidentifierSpace(identifierSpace);
    }

    Machines<D,T> getMachines()
    {
        return machines;
    }
    /*
        This function takes a key, a variable of long long passed by reference and 
        it returns a finalized hashed key by multiplying 37 repeatedily while adding the 
        ascii of every character in that passed key. 
        37 is a very mysteric prime number that makes this hash function unique to give
        as much as unique hashed key always. The variable that has been passed by reference
        is set before taking mod; which will help us to stop collisions.
    */
    T HashFunction(D key, unsigned long long* befHash)
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
        return hashedValue % (T)pow(2, identifierSpace);
    }
    /*
        This function takes a key, value pair and a starting machineID number and
        then inserts the data on the specific machine (hashed value of the key).
    */
    void insertData(D key, D value, T machineID)
    {
        unsigned long long int beforeHashVal = 0;
        T hash = HashFunction(key, &beforeHashVal);

        Machine_Node<D,T>* curr = machines.searchResponsibleMachine(hash, machineID);
        curr->file.increaseFileLineNumber(1);
        /*
        * This check deals with the case when line number 
        * exceeds from 100 in a specific file.
        */
        if (curr->file.getFileLineNumber() > 100)
        {
            curr->file.makeNewFile(machineID);
        }
        curr->file.insert(value);
        curr->tree.setRoot(curr->tree.insert(curr->tree.getRoot(), hash, beforeHashVal, curr->file.getFileLineNumber()));
    }

    /*
       This function auto assigns the machine IDs by;
       - Accessing the Nodal address from memory and storing it in a string.
       - Hashing those memory addresses and assiging machine IDs on that base.
    */
    void autoAssigning()
    {
        for (int i = 0; i < noOfmachines; i++) {
            machines.insertMachine(-1);
        }
        Machine_Node<D,T>* searchPtr = machines.getFirstMachine();
        do {
            unsigned long long int befHash = 0;
            T value = -1;

            D addressInString = to_string((long)searchPtr);
            value = HashFunction(addressInString,&befHash);
            while (machines.machineExists(value) == true)
            {
                value++;
                value = value % (T)pow(2, identifierSpace);
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

    /*
        This function takes machine IDs from user and then assign them.
    */
    void manualAssigning()
    {
        cout << "Enter values for machines respectively: \n";
        T value = -1;
        for (int i = 0; i < noOfmachines; i++)
        {
            cout << "Value # " << (i + 1) << " : " << endl;
            cin >> value;
            while (value < 0 || value >= pow(2, identifierSpace) || (i > 0 && machines.machineExists(value) == true)) // check for unique number and for number between identifier space
            {
                cout << "Error!\nPlease input a value;\n1) Less than total number of machines!\n2) Greater than zero\n3) Unique\nYour Input: ";
                cin >> value;
            }
            machines.insertMachine(value);
        }
        machines.sortMachines();
        machines.configureRoutingTable();
        Machine_Node<D,T>* searchPtr = machines.getFirstMachine();
        do {
            searchPtr->file.setFileName(searchPtr->data);
            searchPtr = searchPtr->next;
        } while (searchPtr != machines.getFirstMachine());
    }

    /*
        This function shows the menu at run time when user wants to add a new 
        machine. At the end, it calls another function which adjusts that
        machine ID and it's neighbouring AVL tree.
    */
    void insertionOfNewMachine()
    {
        T value = -1;
        char choice;
        cout << "\n-------------------------- Add a new machine --------------------------\n";
        cout << "|";
        cout << "\n|    Do you want to add the new machine manually or automatically?\n";
        cout << "|  Press A------------> Automatic Assigning.\n";
        cout << "|  Press M------------> Manual Assigning.\n\n";
        cout << "|\n";
        cout << "|> Your Choice: "; 
        cin >> choice;
        while (1)
        {
            if (choice != 'A' && choice != 'a' && choice != 'm' && choice != 'M')
            {
                cout << "|> Wrong input. Enter again please: ";
                cin >> choice;
            }
            else
                break;
        }
        switch (choice)
        {
            case 'A':
            case 'a':
            {
                machines.insertMachine(-1);
                Machine_Node<D, T>* searchPtr = machines.getFirstMachine();
                do {
                    if (searchPtr->data == -1)
                    {
                        unsigned long long int befHash = 0;
                        D addressInString = to_string((long)searchPtr);
                        value = HashFunction(addressInString, &befHash);
                        while (machines.machineExists(value) == true)
                        {
                            value++;
                            value = value % (T)pow(2, identifierSpace);
                        }
                        searchPtr->data = value;
                        break;
                    }
                    searchPtr = searchPtr->next;
                } while (searchPtr != machines.getFirstMachine());
                machines.sortMachines(); 
                do {
                    if (searchPtr->data == value)
                    {
                        searchPtr->file.setFileName(value);
                        break;
                    }
                    searchPtr = searchPtr->next;
                } while (searchPtr != machines.getFirstMachine());
                
                break;
            }
            case 'M':
            case 'm':
            {
                cout << "|> Enter the value for new machine: ";
                cin >> value;

                while (value < 0 || value >= pow(2, identifierSpace) || (machines.machineExists(value) == true)) // check for unique number and for number between identifier space
                {
                    cout << "Error!\nPlease input a value;\n1) Less than total number of machines!\n2) Greater than zero\n3) Unique\nYour Input: ";
                    cin >> value;
                }
                machines.insertMachine(value);
                machines.sortMachines();
                Machine_Node<D, T>* searchPtr = machines.getFirstMachine();
                do {
                    if (searchPtr->data == value)
                        searchPtr->file.setFileName(value);
                    searchPtr = searchPtr->next;
                } while (searchPtr != machines.getFirstMachine());
                break;
            }
        }
        if (value != -1)
        {
            noOfmachines++;
            cout << "\n\n*** ------- Inserting Machine " << value << " In Identifier Space ------- ***" << endl;
            insertMachineOnRuntime(value);
        }
    }
    /*
        This function inserts the data into newly added machine by removing
        data from successor machine. It also adjusts each AVL side by side.
    */
    void insertMachineOnRuntime(T value)
    {
        Machine_Node<D, T>* successorMachine = machines.getSuccessorMachine(value);
        cout << "\n\n> ------ Adjusting Routing Tables Of Machines ------ <" << endl << endl;
        machines.configureRoutingTable();
        cout << "\n> --- Fetching & Removing Data From Successor Machine --- <" << endl << endl;
        AVL<T>* retrievedAVL = new AVL<T>;
        AVL_Node<T>* successorRoot = machines.getMachineAVL(successorMachine->data);
        retrievedAVL->adjustMachineData(successorRoot, successorRoot, retrievedAVL, value, machines);
        machines.setMachineAVLRoot(retrievedAVL->getRoot(), value); // Set The AVL of New Machine
        cout << "\n> --- Machine " << value << " Got Inserted Successfully --- <" << endl;
        cout << "\n\n--- In Order of Machine " << value << " AVL Tree ---" << endl;
        cout << "|" << endl;
        retrievedAVL->inOrder(retrievedAVL->getRoot());
        cout << "|" << endl;
        cout << "----------- In order Ended -----------" << endl;
        cout << "\n\n--- In Order of Machine " << successorMachine->data << " AVL Tree ---" << endl;
        cout << "|" << endl;
        machines.getMachineAVLTree(successorMachine->data).inOrder(machines.getMachineAVL(successorMachine->data));
        cout << "|" << endl;
        cout << "----------- In order Ended -----------" << endl << endl;
        cout << "\n*** ------- End Of Machine " << value << " Insertion ------- ***" << endl << endl;
    }

    /*
        This function prompts the user to enter the machine to be deleted
        on run-time and then retrieve and inserts the data of the machine 
        to be deleted (if it exists) into next responsible machine and also
        adjusts the AVL of the responsible machine.
    */
    void deleteMachineOnRuntime()
    {
        T value = -1;
        cout << "\n-------------------------- Delete a new machine --------------------------\n";
        cout << "|";
        cout << "\n|    Enter the machine you want to delete: ";
        cin >> value;
        cout << "|\n";
        cout << "\n\n*** ------- Deleting Machine " << value << " From Identifier Space ------- ***" << endl;
        if (machines.machineExists(value))
        {
            Machine_Node<D, T>* successorMachine = machines.getSuccessorMachine(value); 
            cout << "\n\n> --- Removing Machine & Transfering Data To Successor Machine --- <" << endl << endl;
            machines.removeMachine(value);
            cout << "\n\n> ------ Adjusting Routing Tables Of Machines ------ <" << endl << endl;
            machines.configureRoutingTable();
            cout << "\n> --- Machine " << value << " Was Removed Successfully --- <" << endl;
            cout << "\n\n--- In Order of Machine " << successorMachine->data << " AVL Tree ---" << endl;
            cout << "|" << endl;
            machines.getMachineAVLTree(successorMachine->data).inOrder(successorMachine->tree.getRoot());
            cout << "|" << endl;
            cout << "----------- In order Ended -----------" << endl << endl;
            noOfmachines--;
        }
        else
        {
            cout << "\n\n----- Error! No Machine Found With ID " << value << " -----" << endl;
            cout << "\n\n--- Following Machines are Currently Active ---" << endl << endl;
            machines.display();
        }
        cout << "\n*** ---------- End Of Machine " << value << " Deletion ---------- ***" << endl << endl;
        
    }
    /*
        This function prompts the user to enter the key and a starting machine
        to delete the data if that 
    */
    D removeData(D key, T machineID)
    {
        unsigned long long int beforeHashVal = 0;
        T hash = HashFunction(key, &beforeHashVal);
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
                tempPtr = machines.getMachineAVLTree(curr->data).remove(curr->tree.getRoot(), hash, beforeHashVal);
                machines.setMachineAVLRoot(tempPtr, curr->data);
                cout << "\n\n--- In Order of Machine " << curr->data << " AVL Tree ---" << endl;
                cout << "|" << endl;
                machines.getMachineAVLTree(curr->data).inOrder(machines.getMachineAVL(curr->data));
                cout << "|" << endl;
                cout << "----------- In order Ended -----------" << endl << endl;
                return removedData;
            }
        }
        return removedData;   
    }
    /*
        This function prompts the user to enter the key and a starting machine
        to fetch the data and show to user (if that data exists).
    */
    D searchData(D key, T machineID)
    {
        unsigned long long int beforeHashVal = 0;
        T hash = HashFunction(key, &beforeHashVal);

        D finalOutput = "";

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
        cout << "\nData not found!";
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

    /*
        This function prints the routing table of the machine whose ID is
        passed as argument
    */
    void printSpecificRoutingTable(T machineID)
    {
        machines.printMachineRoutingTable(machineID);
    }

    /*
        This function shows the menu to the user 
    */
    void Menu()
    {
        cout << "\t\t\t\t\t--------------------------------------\n";
        cout << "\t\t\t\t\tData Storage over Distributed Networks\n";
        cout << "\t\t\t\t\t--------------------------------------\n";
        
        cout << "|\n";
        cout << "|  1. Insert data in (key,value) pair.\n";
        cout << "|  2. Remove data by specifying key from a starting machine.\n";
        cout << "|  3. Print routing table of a specific machine.\n";
        cout << "|  4. Print AVL tree of a machine with location of files & line numbers.\n";
        cout << "|  5. Add a new machine in Ring DHT.\n";
        cout << "|  6. Remove a machine from Ring DHT.\n";
        cout << "|  0. Exit.\n";
        cout << "|\n\n\n";

        cout << "|  Your choice: ";

    }
    ~RingDHT()
    {
    }
};