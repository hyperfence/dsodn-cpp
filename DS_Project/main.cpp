#include <iostream>
#include "Machines.h"

int main()
{
	int identifierSpace = 32;
	Machines<int> m(identifierSpace);
	m.insert(1);
	m.insert(28);
	m.insert(9);
	m.insert(11);
	m.insert(4);
	m.insert(21);
	m.insert(20);
	m.insert(14);
	m.insert(18);
	m.display();
	m.configureRoutingTable();
	return 0;
}





















//#include <iostream>
//#include <string>
//#include <sstream>
//#include <math.h>
//using namespace std;
//
//
//template <class T>
//struct AVL {
//    template <class U>
//    struct Node {
//        U data;
//        Node<U>* Left;
//        Node<U>* Right;
//        int height;
//    };
//    Node<T>* Root = NULL;
//
//    int getHeight(Node<T>* n)
//    {
//        if (n != NULL)
//            return n->height;
//        else
//            return 0;
//    }
//
//    int max(int val1, int val2)
//    {
//        if (val1 > val2)
//            return val1;
//        return val2;
//    }
//
//    Node<T>* rotateRight(Node<T>* n) {
//        Node<T>* temp1 = n->Left;
//        Node<T>* T2 = temp1->Right;
//
//        temp1->Right = n;
//        n->Left = T2;
//
//        n->height = max(getHeight(n->Left), getHeight(n->Right)) + 1;
//        temp1->height = max(getHeight(temp1->Left), getHeight(temp1->Right)) + 1;
//
//        return temp1;
//    }
//
//    Node<T>* rotateLeft(Node<T>* n)
//    {
//        Node<T>* temp1 = n->Right;
//        Node<T>* temp2 = temp1->Left;
//
//        temp1->Left = n;
//        n->Right = temp2;
//
//        n->height = max(getHeight(n->Left), getHeight(n->Right)) + 1;
//        temp1->height = max(getHeight(temp1->Left), getHeight(temp1->Right)) + 1;
//
//        return temp1;
//    }
//
//    int Balance(Node<T>* n)
//    {
//        if (n == NULL)
//            return 0;
//        return getHeight(n->Left) - getHeight(n->Right);
//    }
//
//    Node<T>* insert(Node<T>* n, T value) {
//        if (n == NULL) {
//            n = new Node<T>;
//            n->data = value;
//            n->Left = NULL;
//            n->Right = NULL;
//            n->height = 1;
//            return n;
//        }
//        else if (value < n->data) {
//            n->Left = insert(n->Left, value);
//        }
//        else if (value > n->data) {
//            n->Right = insert(n->Right, value);
//        }
//        else
//            return n;
//
//        n->height = 1 + max(getHeight(n->Left), getHeight(n->Right));
//        int balance = Balance(n);
//
//        if (balance > 1 && value < n->Left->data)
//            return rotateRight(n);
//
//        if (balance < -1 && value > n->Right->data)
//            return rotateLeft(n);
//
//        if (balance > 1 && value > n->Left->data)
//        {
//            n->Left = rotateLeft(n->Left);
//            return rotateRight(n);
//        }
//
//        if (balance < -1 && value < n->Right->data)
//        {
//            n->Right = rotateRight(n->Right);
//            return rotateLeft(n);
//        }
//
//        return n;
//    }
//
//    Node<T>* leftMostNode(Node<T>* n)
//    {
//        Node<T>* current = n;
//
//        while (current->Left != NULL)
//            current = current->Left;
//
//        return current;
//    }
//
//    Node<T>* remove(Node<T>* n, int value)
//    {
//        if (n == NULL)
//            return n;
//
//        if (value < n->data)
//            n->Left = remove(n->Left, value);
//
//        else if (value > n->data)
//            n->Right = remove(n->Right, value);
//
//        else
//        {
//            if (n->Left == NULL) {
//                Node<T>* temp = n->Right;
//                delete n;
//                return temp;
//            }
//            else if (n->Right == NULL) {
//                Node<T>* temp = n->Left;
//                delete n;
//                return temp;
//            }
//
//            Node<T>* temp = n->Right;
//
//            while (temp && temp->Left != NULL)
//                temp = temp->Left;
//
//            n->data = temp->data;
//            n->Right = remove(n->Right, temp->data);
//        }
//
//        if (n == NULL)
//            return n;
//
//        n->height = 1 + max(getHeight(n->Left), getHeight(n->Right));
//        int balance = Balance(n);
//
//        if (balance > 1 && Balance(n->Left) >= 0)
//            return rotateRight(n);
//
//        if (balance > 1 && Balance(n->Left) < 0)
//        {
//            n->Left = rotateLeft(n->Left);
//            return rotateRight(n);
//        }
//
//        if (balance < -1 && Balance(n->Right) <= 0)
//            return rotateLeft(n);
//
//        if (balance < -1 && Balance(n->Right) > 0)
//        {
//            n->Right = rotateRight(n->Right);
//            return rotateLeft(n);
//        }
//
//        return n;
//    }
//
//    void inOrder(Node<T>* n) {
//        if (n != NULL) {
//            inOrder(n->Left);
//            cout << n->data << " ";
//            inOrder(n->Right);
//        }
//    }
//
//};
//
//class Hash {
//private:
//    int size;
//    int capacity;
//    int* arr;
//
//public:
//    Hash(int cap) {
//        size = 0;
//        capacity = cap;
//        arr = new int[cap];
//        for (int i = 0; i < capacity; i++)
//        {
//            arr[i] = 0;
//        }
//    }
//
//    int HashFunction(string s) {
//        int sum = 0;
//        for (int i = 0; s[i] != '\0'; i++)
//            sum += int(s[i]);
//        return sum % capacity;
//    }
//
//    //     int HashFunction(string s) {
//    // 	    int hash = 7;
//    //         for(int i=0; s[i]!='\0'; i++)
//    //             hash = hash*31 + int(s[i]);
//    //         return hash%capacity;    
//
//    // 	}
//
//    void insert(string s)
//    {
//        int index = HashFunction(s);
//        arr[index] = index;
//        size++;
//    }
//
//    void Delete(string s) {
//        int ind = Search(s);
//        arr[ind] = 0;
//    }
//
//    void display() {
//        for (int i = 0; i < capacity; i++) {
//            cout << arr[i] << " ";
//        }
//        cout << endl;
//    }
//
//    int Search(string s) {
//        int ind = HashFunction(s);
//        while (arr[ind] != 0 && arr[ind] != ind) {
//            ind = HashFunction(s);
//        }
//        if (arr[ind] == 0)
//            return -1;
//        else
//            return ind;
//    }
//
//    bool isEmpty() {
//        return (size == 0);
//    }
//
//    void Clear()
//    {
//        delete[] arr;
//    }
//
//};
//
//
//template <class T>
//struct node
//{
//    T data;
//    node* next;
//    AVL<T> tree;
//};
//
//template <class T>
//struct singlyCircularLinkedList
//{
//    node<T>* head;
//
//    singlyCircularLinkedList()
//    {
//        head = NULL;
//    }
//
//    void insert(T value)
//    {
//        node<T>* temp = new node<T>;
//        temp->data = value;
//        temp->next = NULL;
//        node<T>* curr = head;
//
//        if (head == NULL)
//        {
//            head = temp;
//            temp->next = head;
//        }
//        else
//        {
//            do {
//                curr = curr->next;
//            } while (curr->next != head);
//
//            curr->next = temp;
//            temp->next = head;
//        }
//    }
//
//    void Remove(T value) {
//        node<T>* pre = new node<T>;
//        node<T>* curr = head;
//        while (curr->data != value) {
//            pre = curr;
//            curr = curr->next;
//        }
//        pre->next = curr->next;
//        curr->next = NULL;
//        delete curr;
//    }
//
//    void clear() {
//        node<T>* curr = head;
//        node<T>* temp;
//        do
//        {
//            temp = curr;
//            curr = curr->next;
//            delete temp;
//        } while (curr != head);
//        head = NULL;
//    }
//
//    void display() {
//        node<T>* curr = head;
//        if (head == NULL)
//        {
//            cout << "Empty List" << endl;
//            return;
//        }
//        do
//        {
//            cout << curr->data << " ";
//            curr = curr->next;
//        } while (curr != head);
//    }
//
//    // adding a new function - Hammad 
//    bool search(int value)
//    {
//        node <T>* ptr = head;
//        do {
//            if (ptr->data == value)
//                return true;
//            ptr = ptr->next;
//        } while (ptr != head);
//        return false;
//    }
//};
//
//
//
//
//template <class T>
//struct ringDHT {
//    int noOfmachines;
//    int identifierSpace;
//    singlyCircularLinkedList<int> machines;
//public:
//    ringDHT(int space, int no_machines) {
//        identifierSpace = space;
//        noOfmachines = no_machines;
//        for (int i = 0; i < no_machines; i++) {
//            machines.insert(-1);
//        }
//    }
//
//    int HashFunction(string s) {
//        int sum = 0;
//        for (int i = 0; s[i] != '\0'; i++)
//            sum += int(s[i])* pow(i, i);
//        cout << "\nSum: " << sum << endl;
//        cout << "\n-------\n";
//        while (machines.search(sum % int(pow(2, identifierSpace)) == true))
//        {
//            sum += 1;
//        }
//        return (sum % int(pow(2, identifierSpace)));
//    }
//
//    void insert(string key, string value) {
//        int hash = HashFunction(key);
//        node<int>* curr = machines.head;
//        while (curr->data < hash) {
//            curr = curr->next;
//        }
//        curr->tree.Root = curr->tree.insert(curr->tree.Root, hash);
//    }
//    void insert(int key, string value) {
//        node<int>* curr = machines.head;
//        while (curr->data < key) {
//            curr = curr->next;
//        }
//        curr->tree.Root = curr->tree.insert(curr->tree.Root, key);
//    }
//
//    void autoAssigning()
//    {
//        node <int>* searchPtr = machines.head;
//        do {
//            int value = -1;
//            ostringstream address;
//            address << searchPtr;
//            string addressInString = address.str();
//            value = HashFunction(addressInString);
//
//            if (value != -1)
//                searchPtr->data = value;
//            else
//                cout << "Hashing wasn't succesfull you noob!\n";
//            searchPtr = searchPtr->next;
//        } while (searchPtr != machines.head);
//    }
//    ~ringDHT()
//    {
//
//    }
//};
//
////int main()
////{
////    //Hash h(s.length());
////    //h.insert(s);
////    ringDHT<string> dht(4, 5);
////    dht.autoAssigning();
////    dht.machines.display();
////    dht.machines.clear();
////    //dht.insert(2, "value");
////    //dht.insert(3, "value");
////    //dht.insert(4, "value");
////   // node<int>* curr = dht.machines.head;
////
////
////    //ostringstream address;
////    //address << curr;
////    //string s1 = address.str();
////    //cout << s1 << endl;
////    //cout << dht.HashFunction(s1);
////
////
////    // curr= curr->next;
////    // curr->tree.inOrder(curr->tree.Root);
////
////    // cout<<endl;
////    // dht.insert(7,"value");
////    // dht.insert(5,"value");
////    // curr= curr->next;
////    // curr->tree.inOrder(curr->tree.Root);
////
////    // cout<<endl;
////    // dht.insert(8,"value");
////    // dht.insert(12,"value");
////    // dht.insert(9,"value");
////    // dht.insert(10,"value");
////    // dht.insert(11,"value");
////    // curr= curr->next;
////    // curr->tree.inOrder(curr->tree.Root);
////
////    //cout<< h.HashFunction(s)<<endl;
////    //cout<<h.Search(s);
////
////    return 0;
////}
