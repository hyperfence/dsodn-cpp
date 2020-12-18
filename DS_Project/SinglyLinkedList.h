#pragma once
#include <iostream>

using namespace std;

template <class T>
struct Singly_List_Node
{
	T data;
	Singly_List_Node<T>* next;
};

template <class T>
class SinglyLinkedList
{
private:
	Singly_List_Node<T>* head;
public:
	SinglyLinkedList()
	{
		this->head = NULL;
	}
	int sizeOfList()
	{
		int size = 0;
		Singly_List_Node<T>* n = head;
		for (int i = 0; ; i++)
		{
			if (n->next == NULL)
			{
				break;
			}
			n = n->next;
			size++;
		}
		return size;
	}
	void insertStart(T data)
	{
		Singly_List_Node<T>* temp = new Singly_List_Node<T>();
		temp->data = data;
		temp->next = NULL;
		if (head == NULL)
		{
			head = temp;
		}
		else
		{
			temp->next = head;
			head = temp;
		}
	}
	void insertEnd(T data)
	{
		Singly_List_Node<T>* temp = new Singly_List_Node<T>();
		temp->data = data;
		temp->next = NULL;
		if (head == NULL)
		{
			head = temp;
		}
		else
		{
			Singly_List_Node<T>* n = head;
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
	void middle(int data)
	{
		int j = 1;
		int g = 0;
		Singly_List_Node<T>* n = head;
		Singly_List_Node<T>* m = head;
		for (int i = 0; ; i++)
		{
			if (n->next == NULL)
			{
				Singly_List_Node<T>* temp = new Singly_List_Node<T>();
				temp->data = data;
				temp->next = m;
				Singly_List_Node<T>* f = head;
				for (int h = 0; h < g; h++)
				{
					f = f->next;
				}
				f->next = temp;
				break;
			}
			n = n->next;
			if (j % 2 == 0)
			{
				m = m->next;
			}
			j++;
			g++;
		}
	}
	void removeAt(int index)
	{
		int j = 0;
		Singly_List_Node<T>* n = head;
		for (int i = 0; ; i++)
		{
			if (j == index)
			{
				if (n->next == NULL)
				{
					n = NULL;
				}
				else
				{

					Singly_List_Node<T>* m = head;
					for (int k = 0; k < j - 1; k++)
					{
						m = m->next;
					}
					m->next = n->next;
					n = NULL;
				}
				break;
			}
			n = n->next;
			j++;
		}
	}
	void replaceAt(int data, int index)
	{
		int j = 0;
		Singly_List_Node<T>* n = head;
		for (int i = 0; ; i++)
		{
			if (j == index)
			{
				n->data = data;
				break;
			}
			n = n->next;
			j++;
		}
	}
	void remove()
	{
		Singly_List_Node<T>* n = head;
		for (int i = 0; ; i++)
		{
			if (n->next->next == NULL)
			{
				n->next = NULL;
				break;
			}
			n = n->next;
		}
	}
	void insertAt(int data, int index)
	{
		int j = 0;
		Singly_List_Node<T>* n = head;
		for (int i = 0; ; i++)
		{
			if (j == index)
			{
				Singly_List_Node<T>* temp = new Singly_List_Node<T>();
				temp->data = data;
				temp->next = n;
				Singly_List_Node<T>* m = head;
				for (int k = 0; k < j - 1; k++)
				{
					m = m->next;
				}
				m->next = temp;

				break;
			}
			n = n->next;
			j++;
		}
	}
	void sort()
	{
		Singly_List_Node<T>* n = head;
		for (int i = 0; ; i++)
		{
			if (n->next == NULL)
			{
				break;
			}
			Singly_List_Node<T>* m = head;
			for (int j = 0; ; j++)
			{
				if (m->next == NULL)
				{
					break;
				}
				if (m->data > (m->next)->data)
				{
					Singly_List_Node<T>* temp = new Singly_List_Node<T>();
					temp->data = m->data;
					m->data = (m->next)->data;
					(m->next)->data = temp->data;
				}
				m = m->next;
			}
			n = n->next;
		}
	}
	void display()
	{
		Singly_List_Node<T>* n = head;
		while (n != NULL)
		{
			cout << " " << n->data;
			n = n->next;
		}
	}
};