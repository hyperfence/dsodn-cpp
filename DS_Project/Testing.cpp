#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>
#include "SinglyLinkedList.h"
using namespace std;

class MachineFile {
    string path, fileName;
    int lineNumber;
public:
    MachineFile() {
        lineNumber = 0;
        path = "";
        fileName = "";
    }

    void setFileName(int machineID) {
        fileName = "Machine_" + to_string(machineID) + ".txt";
    }

    void insert(string value) {
        ofstream out;
        out.open(path + fileName, ios::app);
        out << value << endl;
        out.close();
    }

};


template <class U>
struct node
{
    U data;
    node<U>* next;
    unsigned long long int beforeHash;
    MachineFile file;
};
template <class T>
class List
{
public:
    node<T>* head;
    List()
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
            cout << "Empty List";
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

    ~List() {
        delete head;
    }
};


/////// AVL CLass ///////
template <class T>
struct AVL {
    template <class U>
    struct Node {
        List<U> l;
        Node<U>* Left;
        Node<U>* Right;
        int height;
    };
    Node<T>* Root = NULL;

    int getHeight(Node<T>* n)
    {
        if (n != NULL)
            return n->height;
        else
            return 0;
    }

    int max(int val1, int val2)
    {
        if (val1 > val2)
            return val1;
        return val2;
    }

    Node<T>* rotateRight(Node<T>* n) {
        Node<T>* temp1 = n->Left;
        Node<T>* T2 = temp1->Right;

        temp1->Right = n;
        n->Left = T2;

        n->height = max(getHeight(n->Left), getHeight(n->Right)) + 1;
        temp1->height = max(getHeight(temp1->Left), getHeight(temp1->Right)) + 1;

        return temp1;
    }

    Node<T>* rotateLeft(Node<T>* n)
    {
        Node<T>* temp1 = n->Right;
        Node<T>* temp2 = temp1->Left;

        temp1->Left = n;
        n->Right = temp2;

        n->height = max(getHeight(n->Left), getHeight(n->Right)) + 1;
        temp1->height = max(getHeight(temp1->Left), getHeight(temp1->Right)) + 1;

        return temp1;
    }

    int Balance(Node<T>* n)
    {
        if (n == NULL)
            return 0;
        return getHeight(n->Left) - getHeight(n->Right);
    }

    Node<T>* insert(Node<T>* n, T value) {
        if (n == NULL) {
            n = new Node<T>;
            //n->l.head->data = value;
            n->l.insert(value);
            n->Left = NULL;
            n->Right = NULL;
            n->height = 1;
            return n;
        }
        else if (value < n->l.head->data) {
            n->Left = insert(n->Left, value);
        }
        else if (value > n->l.head->data) {
            n->Right = insert(n->Right, value);
        }
        else
            return n;

        n->height = 1 + max(getHeight(n->Left), getHeight(n->Right));
        int balance = Balance(n);

        if (balance > 1 && value < n->Left->l.head->data)
            return rotateRight(n);

        if (balance < -1 && value > n->Right->l.head->data)
            return rotateLeft(n);

        if (balance > 1 && value > n->Left->l.head->data)
        {
            n->Left = rotateLeft(n->Left);
            return rotateRight(n);
        }

        if (balance < -1 && value < n->Right->l.head->data)
        {
            n->Right = rotateRight(n->Right);
            return rotateLeft(n);
        }

        return n;
    }

    Node<T>* leftMostNode(Node<T>* n)
    {
        Node<T>* current = n;

        while (current->Left != NULL)
            current = current->Left;

        return current;
    }

    Node<T>* remove(Node<T>* n, int value)
    {
        if (n == NULL)
            return n;

        if (value < n->data)
            n->Left = remove(n->Left, value);

        else if (value > n->data)
            n->Right = remove(n->Right, value);

        else
        {
            if (n->Left == NULL) {
                Node<T>* temp = n->Right;
                delete n;
                return temp;
            }
            else if (n->Right == NULL) {
                Node<T>* temp = n->Left;
                delete n;
                return temp;
            }

            Node<T>* temp = n->Right;

            while (temp && temp->Left != NULL)
                temp = temp->Left;

            n->data = temp->data;
            n->Right = remove(n->Right, temp->data);
        }

        if (n == NULL)
            return n;

        n->height = 1 + max(getHeight(n->Left), getHeight(n->Right));
        int balance = Balance(n);

        if (balance > 1 && Balance(n->Left) >= 0)
            return rotateRight(n);

        if (balance > 1 && Balance(n->Left) < 0)
        {
            n->Left = rotateLeft(n->Left);
            return rotateRight(n);
        }

        if (balance < -1 && Balance(n->Right) <= 0)
            return rotateLeft(n);

        if (balance < -1 && Balance(n->Right) > 0)
        {
            n->Right = rotateRight(n->Right);
            return rotateLeft(n);
        }

        return n;
    }

    void inOrder(Node<T>* n) {
        if (n != NULL) {
            inOrder(n->Left);
            cout << n->l.head->data << " ";
            inOrder(n->Right);
        }
    }

};
/////// Routing_Table ///////

struct Routing_Table_Node
{
    void* data;
    Routing_Table_Node* next;
};

class RoutingTable
{
private:
    Routing_Table_Node* head;

public:
    RoutingTable()
    {
        head = NULL;
    }
    void* getHead()
    {
        return head;
    }
    void insert(void* data)
    {
        Routing_Table_Node* temp = new Routing_Table_Node();
        temp->data = data;
        temp->next = NULL;
        if (head == NULL)
        {
            head = temp;
        }
        else
        {
            Routing_Table_Node* n = head;
            for (int i = 0; ; i++)
            {
                if (n->next == NULL)
                {
                    n->next = temp;
                    break;
                }
                n = n->next;
            }
        }
    }
    void* getElement(int elementID)
    {
        Routing_Table_Node* n = head;
        for (int i = 0; ; i++)
        {
            if (n == NULL)
            {
                return NULL;
            }
            if (i == elementID)
            {
                return n->data;
            }
            n = n->next;
        }
        return NULL;
    }
    void display()
    {
        Routing_Table_Node* n = head;
        while (n != NULL)
        {
            cout << " " << n->data;
            n = n->next;
        }
    }
    bool isEmpty()
    {
        bool flag = true;
        if (head != NULL)
        {
            flag = false;
        }
        return flag;
    }
};


/// ////////////////////////////////// machine node ///////////////////////////

template <typename N>
struct Machine_Node
{
    N data;
    Machine_Node<N>* next;
    RoutingTable* routingTable;
    AVL<N> tree;
};

template <class T>
struct Machines {
    int routingTableSize;
    Machine_Node<T>* head;

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

    /*
        This function takes the key of the machine and returns that specific machine if
        found else this function will return NULL if machine not found.
    */
    Machine_Node<T>* getMachine(T value)
    {
        Machine_Node<T>* successor = new Machine_Node<T>();
        successor = NULL;
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
        This function takes the key of the machine and finds the immediate active successor
        and then return that machine else this function will return NULL if machine not found.
    */
    Machine_Node<T>* getSuccessorMachine(T value)
    {
        Machine_Node<T>* successor = new Machine_Node<T>();
        successor = NULL;
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
        This function takes hashed key of data and machine from the Ring_DHT class and then
        performs the search according to the given keys
    */
    Machine_Node<T>* searchData(T dataKey, T machineKey, Machine_Node<T>* startingMachine = NULL)
    {
        if (startingMachine == NULL)
        {
            startingMachine = this->getMachine(machineKey);
        }
        for (int i = 0; i < routingTableSize; i++)
        {
            Machine_Node<T>* temp = new Machine_Node<T>();
            Machine_Node<T>* temp2 = new Machine_Node<T>();
            temp = static_cast<Machine_Node<T>*>(startingMachine->routingTable->getElement(i));
            temp2 = static_cast<Machine_Node<T>*>(startingMachine->routingTable->getElement(i + 1));
            if (temp->data == dataKey)
            {
                cout << "Reached Machine: " << temp->data << endl;
                return startingMachine;
            }
            else if (dataKey > startingMachine->data && dataKey <= temp->data)
            {
                cout << "Reached Machine: " << temp->data << endl;
                startingMachine = temp;
                return startingMachine;
            }
            else if (dataKey > temp->data && temp2 != NULL && dataKey < temp2->data)
            {
                cout << "Reached Machine: " << temp->data << endl;
                startingMachine = temp;
                Machine_Node<T>* machineFound = new Machine_Node<T>();
                machineFound = searchData(dataKey, machineKey, startingMachine);
                if (machineFound != NULL)
                {
                    return machineFound;
                }
            }
            else if (dataKey > temp->data && temp2 == NULL)
            {
                cout << "Reached Machine: " << temp->data << endl;
                startingMachine = temp;
                Machine_Node<T>* machineFound = new Machine_Node<T>();
                machineFound = searchData(dataKey, machineKey, startingMachine);
                if (machineFound != NULL)
                {
                    return machineFound;
                }
            }
        }
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
                Machine_Node<T>* nearestActive = this->getSuccessorMachine(routingTable[i]);
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
        } while (temp != head);
    }
};


template <class T>
struct ringDHT {
    int noOfmachines;
    int identifierSpace;
    Machines<int> machines;
public:
    ringDHT(int space, int no_machines) {
        identifierSpace = space;
        noOfmachines = no_machines;
    }

    // our finalized HashFunction..
    int HashFunction(string key)
    {
        unsigned long long int hashedValue = 0;
        int length = key.size();
        if (key.size() > 8)
             length = 8;
        for (int i = 0; i < length; i++)
        {
            hashedValue = 37 * hashedValue + key[i];
        }
        
        //if (hashedValue < 0)
        //    hashedValue *= -1;
        return hashedValue % (int)pow(2, identifierSpace);
    }

    //int HashFunction(string const& s) {
    //    const int p = 31;
    //    const int m = 1e9 + 9;
    //    long long hash_value = 0;
    //    long long p_pow = 1;
    //    for (char c : s) {
    //        hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
    //        p_pow = (p_pow * p) % m;
    //    }
    //    if (hash_value < 0)
    //        hash_value *= -1;
    //    //cout << "Hash Value: " << (long long) hash_value << endl;
    //    return hash_value % 16;
    //}
    //int HashFunction(string s) {
    //    int sum = 0;
    //    for (int i = 0; s[i] != '\0'; i++)
    //        sum += int(s[i]);        
    //    return sum % int(pow(2, identifierSpace));
    //}

    void insert(string key, string value) {
        int hash = HashFunction(key);
        Machine_Node<int>* curr = machines.head;
        while (curr->data < hash) {
            curr = curr->next;
        }
        curr->tree.Root = curr->tree.insert(curr->tree.Root, hash);
    }

    void insert(int key, string value) {
        Machine_Node<int>* curr = machines.head;
        while (curr->data < key) {
            curr = curr->next;
        }
        curr->tree.Root = curr->tree.insert(curr->tree.Root, key);
    }

    void autoAssigning()
    {
        for (int i = 0; i < noOfmachines; i++) {
            machines.insert(-1);
        }
        Machine_Node<int>* searchPtr = machines.head;
        do {
            int value = -1;
            ostringstream address;
            address << searchPtr;
            string addressInString = address.str();
            value = HashFunction(addressInString);
            while (machines.machineExists(value) == true)
            {
                value++;
                value = value % (int)pow(2, identifierSpace);
            }

            if (value != -1)
                searchPtr->data = value;
            else
                cout << "Hashing wasn't succesfull you noob!\n";
            searchPtr = searchPtr->next;
        } while (searchPtr != machines.head);
        machines.sort();
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
            machines.insert(value);
        }
    }
    ~ringDHT()
    {
        machines.clear();
    }
};




int main() {
    ringDHT<string> dht(4, 5);
    dht.autoAssigning();
    dht.machines.display();
   // dht.insert("Hammad Ahmed is a goodest badest boy!", "i190582");
    dht.insert("sdasdasfasfdsgafdgadrdfhadfhdfdhadfherfh", "i190582");
   // dht.insert("Hammad Ahmed is a goodest badest boy!", "i190582");


    Machine_Node<int>* searchPtr = dht.machines.head;
    do {
        cout << searchPtr->data << " ";
        searchPtr->tree.inOrder(searchPtr->tree.Root);
        cout << endl;
        searchPtr = searchPtr->next;
    } while (searchPtr != dht.machines.head);

    return 0;
}
