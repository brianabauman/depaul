//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------- 

#ifndef BLOATED_H
#define BLOATED_H

// DO NOT CHANGE THIS FILE

#include "Node.h"

// needs to be this value, do not change in final submission
#define NUM_NODES 1000000

class Bloated
{
public:
	Bloated();
	~Bloated();

	static void CreateLinkedList();
	static bool findKey(int key, OriginalNode &foundNode);
	static OriginalNode *getListHead();
private:
	static OriginalNode *head;
};


#endif

// ---  End of File ---------------