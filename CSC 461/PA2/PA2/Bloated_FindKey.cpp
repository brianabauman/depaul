//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------- 

#include "Framework.h"

// user headers
#include "bloated.h"
#include "Node.h"

#define STUB_PLEASE_REPLACE(x) (x)

//----------------------------------------------------------------------------------
// Find Key using linked lists (pointers only) 
//    Hint: use ->pNext
//    YOU MUST - iterate through the nodes in a linked list fashion or 0 credit
//               starting from the head until you find it
//
// Return true if you find the node
// Return the pointer in the argument list to the node (if found)
//----------------------------------------------------------------------------------

bool Bloated::FindKey(int key, Node *&foundNode) const
{
	Node *currentNode = this->pHead;
	while (currentNode != 0) 
	{
		if (currentNode->key == key)
		{
			foundNode = currentNode;
			return true;
		}
		else
		{
			currentNode = currentNode->pNext;
		}
	}

	return false;
}

// End of File
