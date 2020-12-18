#pragma once
#include "Machines.h"

template <class T>
class Ring_DHT {
private:
	int identifierSpace;
	Machines<T>* machines; // We are using pointer here so that we can store all the machines on the heap memory rather program execution stack

public:
	Ring_DHT()
	{
		identifierSpace = 0;
		machines = NULL;
	}
	Ring_DHT(int space)
	{
		this->identifierSpace = space;
		identifierSpace = 0;
		machines = new Machines<T>(space);
	}

	void setIdentifierSpace(int space)
	{
		this->identifierSpace = space;
		identifierSpace = 0;
		machines = new Machines<T>(space);
	}

	// All the hashing and inserting functions will go here

	~Ring_DHT()
	{
		delete machines;
	}
};