#pragma once
#include <iostream>

using namespace std;

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
