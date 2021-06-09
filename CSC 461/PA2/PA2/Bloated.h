//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------- 

#ifndef BLOATED_H
#define BLOATED_H

#include "Node.h"

class Bloated
{
public:
	// specialized
	Bloated(const unsigned int NodeCount);

	// Big four
	~Bloated();
	Bloated() = delete;
	Bloated(const Bloated &) = delete;
	Bloated & operator = (const Bloated &) = delete;

	// methods
	bool FindKey(int key, Node *&foundNode) const;
	Node *GetListHead() const;
	unsigned int GetSize() const;

private:
	// data
	Node *pHead;
	unsigned int Size;
};


#endif 


// ---  End of File ---------------
