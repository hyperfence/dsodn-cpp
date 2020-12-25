/*
    The lines below are required for debugging memeory leaks.
    These lines will be removed when all memory leaks are resolved.
*/
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif


/*
    The main program starts here
*/
#include "Ring_DHT.h"

using namespace std;

int main()
{
    RingDHT<string, int> dht(4, 5);
   // dht.autoAssigning();
    dht.manualAssigning();
    dht.getMachines().display();
    // dht.machines.display();

    //cout << endl;

    dht.insert("Talha", "1st", 12);
    dht.insert("Talha", "2nd", 2);
    dht.insert("Hunaid", "3rd", 5);
    dht.insert("Hassan Raza", "4th", 8);
    dht.insert("Hammad", "5th", 2);
    dht.insert("Akmal", "5th", 3);
    // dht.insert("Ahsan", "6th", 5);
    // dht.insert("Adam", "7th", 12);
    // dht.insert("Khan", "8th", 8);

    /*dht.removeData("Hunaid", 5);
    dht.removeData("Hassan Raza", 8);*/
    dht.removeData("Akmal", 3);

    cout << dht.searchData("Hunaid", 5);
    cout << dht.searchData("Talha", 8);
    cout << dht.searchData("Hassan Raza", 12);
    cout << "\n------------------------------------\n";
    //cout << "Removed data is: " << dht.removeData("Hunaid", 5);
    //cout << dht.searchData("Adam", 3);
    //cout << dht.searchData("Khan", 8);
    // cout << dht.searchData("Ahsan", 2);

    // dht.insert(5, "1st",12);
    // dht.insert(5, "2nd",2);
    // dht.insert(9,"3rd",5);
    // dht.insert(13,"4th",8);

    // Machine_Node<int>* searchPtr = dht.machines.head;
    // do {
    //     cout << searchPtr->data << " ";
    //     searchPtr->tree.inOrder(searchPtr->tree.Root);
    //     cout << endl;
    //     searchPtr = searchPtr->next;
    // } while (searchPtr != dht.machines.head);

    dht.insertMachineOnRuntime(0);

    dht.clearAVLTreeListMemory();   // Release all unwanted memory from the AVL Lists
    //dht.clearAVLTreeMemory();   // Release all unwanted memory from AVL trees
    dht.clearAllMachineMemory(); // Release all unwanted memory from the machines

    _CrtDumpMemoryLeaks(); // This line is required to debug memory leaks
	return 0;
}