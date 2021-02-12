/*
    Data Storage over Distributed Networks - C++

    Version: 1.0.0

    A Project By:
        Hammad Ahmed @hammadahmedpk
        Hunaid Sohail @hunaid2000
        Malik Talha @malik727
*/

#include "Ring_DHT.h"
#include <string>


/*
    The main program starts here
*/
int main()
{
    /*
        These three lines deletes all the .txt files stored in Machine_Files 
        directory before starting the Ring DHT's execution.
    */
    string command = "del /Q ";
    string path = "Machine_Files\\*.txt";
    system(command.append(path).c_str());

    /*
        Execution of Ring DHT starts from here..
    */

    int numberOfMachines, identifierSpace;
    char choice = '\0';

    cout << "|  >. Specify the number of machines: ";
    cin >> numberOfMachines;
    while (cin.fail())
    {
        cout << "|  >. Specify the number of machines: ";
        cin.clear();
        std::cin.ignore(256, '\n');
        cin >> numberOfMachines;
    }

    cout << "|  >. Specify the size of identifier space in bits: ";
    cin >> identifierSpace;
    while (cin.fail())
    {
        cout << "|  >. Specify the size of identifier space in bits: ";
        cin.clear();
        std::cin.ignore(256, '\n');
        cin >> identifierSpace;
    }

    RingDHT <string, int> dht(identifierSpace, numberOfMachines);

    cout << "\n\n|  >. Assign unique machines IDS to machines: ";
    cout << "\n|";
    cout << "\n|  Do you want to add the new machine manually or automatically?\n";
    cout << "|  Press A------------> Automatic Assigning.\n";
    cout << "|  Press M------------> Manual Assigning.\n\n";
    cout << "|\n";
    cout << "|  >. Your Choice: ";
    cin >> choice;

    while (1)
    {
        if (choice != 'A' && choice != 'a' && choice != 'm' && choice != 'M')
        {
            cout << "|  >. Wrong input. Enter again please: ";
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
            dht.autoAssigning();
            break;
        }

        case 'M':
        case 'm':
        {   
            dht.manualAssigning();
            break;
        }
    }

    choice = '\0';
    
    while (choice != '0')
    {
        dht.Menu();
        cin >> choice;
        cin.ignore(100, '\n');
        switch (choice)
        {
            case '1':
            {
                string key, value;
                int machineID;

                cout << "\n\n|  >. Enter key: ";
                getline(cin, key);

                cout << "|  >. Enter value: ";
                getline(cin, value);

                cout << "|  >. Enter starting machine ID: ";
                cin >> machineID;

                while (machineID < 0 || machineID >= pow(2, identifierSpace) || (dht.getMachines().machineExists(machineID) == false)) // check for unique number and for number between identifier space
                {
                    cout << "\n\n|  >. Error!\n|  >. Please input a value;\n|  >. 1) Less than total number of machines!\n|  >. 2) Greater than zero\n|  >. 3) An active machine.\n|  >. Your Input: ";
                    cin >> machineID;
                }

                dht.insertData(key, value, machineID);
                break;
            }
            
            case '2':
            {
                string key, value;
                string removedData = "";
                int machineID;

                cout << "\n\n|  >. Enter key: ";
                getline(cin, key);

                cout << "|  >. Enter starting machine ID: ";
                cin >> machineID;

                while (machineID < 0 || machineID >= pow(2, identifierSpace) || (dht.getMachines().machineExists(machineID) == false)) // check for unique number and for number between identifier space
                {
                    cout << "\n\n|  >. Error!\n|  >. Please input a value;\n|  >. 1) Less than total number of machines!\n|  >. 2) Greater than zero\n|  >. 3) An active machine.\n|  >. Your Input: ";
                    cin >> machineID;
                }

                removedData = dht.removeData(key, machineID);

                if (removedData != "")
                {
                    cout << "|  >. Data removed sucessfully!\n";
                    cout << "|  >. Removed data is:\t" << removedData << endl;
                }
                else
                    cout << "|  >. Data NOT found!\n";

                break;
            }

            case '3':
            {
                int machineID;

                cout << "|  >. Enter starting machine ID: ";
                cin >> machineID;

                while (machineID < 0 || machineID >= pow(2, identifierSpace) || (dht.getMachines().machineExists(machineID) == false)) // check for unique number and for number between identifier space
                {
                    cout << "\n\n|  >. Error!\n|  >. Please input a value;\n|  >. 1) Less than total number of machines!\n|  >. 2) Greater than zero\n|  >. 3) An active machine.\n|  >. Your Input: ";
                    cin >> machineID;
                }

                dht.printSpecificRoutingTable(machineID);

                break;
            }

            case '4':
            {
                int machineID;

                cout << "|  >. Enter starting machine ID: ";
                cin >> machineID;

                while (machineID < 0 || machineID >= pow(2, identifierSpace) || (dht.getMachines().machineExists(machineID) == false)) // check for unique number and for number between identifier space
                {
                    cout << "\n\n|  >. Error!\n|  >. Please input a value;\n|  >. 1) Less than total number of machines!\n|  >. 2) Greater than zero\n|  >. 3) An active machine.\n|  >. Your Input: ";
                    cin >> machineID;
                }

                dht.displayMachineAVL(machineID);
                break;
            }

            case '5':
            {
                dht.getMachines().display();
                dht.insertionOfNewMachine();
                break;
            }

            case '6':
            {
                dht.getMachines().display();
                dht.deleteMachineOnRuntime();
                break;
            }

            case '0':
            {
                choice = '0';
                break;
            }
        }
    }

    dht.clearAVLTreeListMemory();   // Release all unwanted memory from the AVL Lists
    dht.clearAVLTreeMemory();   // Release all unwanted memory from AVL trees
    dht.clearAllMachineMemory(); // Release all unwanted memory from the machines

}