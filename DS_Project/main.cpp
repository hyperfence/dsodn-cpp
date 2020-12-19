//#include <iostream>
//#include "Machines.h"
//
//int main()
//{
//	int identifierSpace = 32;
//	Machines<int> m(identifierSpace);
//	m.insert(1);
//	m.insert(28);
//	m.insert(9);
//	m.insert(11);
//	m.insert(4);
//	m.insert(21);
//	m.insert(20);
//	m.insert(14);
//	m.insert(18);
//	m.display();
//	m.configureRoutingTable();
//	Machine_Node<int>* temp = m.searchResponsibleMachine(26, 1);
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