//#include <iostream>
//#include "Machines.h"
//
//int main()
//{
//	int identifierSpace = 32;
//	Machines<int> m(identifierSpace);
//	m.insert(12);
//	m.insert(2);
//	m.insert(5);
//	m.insert(8);
//	m.insert(7);
//	m.display();
//	m.configureRoutingTable();
//	Machine_Node<int>* temp = m.searchResponsibleMachine(26, 7);
//	if (temp != NULL)
//	{
//		cout << "Data is at Machine: " << temp->data << endl;
//	}
//	else
//	{
//		cout << "Couldn't find the data!" << endl;
//	}
//	return 0;
//}