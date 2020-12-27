#pragma once

#include <iostream>

using namespace std;

struct Routing_Table_Node
{
	void* data; // This void pointer is responsible for storing address Machine_Node
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

	/*
		Insert the Machine_Node address value into the linked list
		of routing tables
	*/
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

	/*
		This function returns the address of Machine_Node pointer whose row in the routing
		table is passed as argument. This void*  address needs to be type casted back to 
		Machine_Node*
	*/
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

	/*
		This function clears the memory occupied by the routing
		table after the machine is removed. Call this function while
		removing a machine
	*/
	void clearRoutingTable()
	{
		Routing_Table_Node* curr = head;
		Routing_Table_Node* temp;
		while(curr != NULL)
		{
			temp = curr;
			curr = curr->next;
			delete temp;
		};
		head = NULL;
	}
};
