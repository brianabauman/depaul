//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------- 

#include "Framework.h"

// Users
#include "Bloated.h"
#include "Node.h"
#include "hotcold.h"

#define STUB_PLEASE_REPLACE(x) (x)

HotCold::HotCold(const Bloated * const pBloated)
{
	unsigned int size = pBloated->GetSize();

	this->pHotHead = new HotNode[size];
	this->pColdHead = new ColdNode[size];
	this->Size = size;

	Node *pCurrentNode = pBloated->GetListHead();
	HotNode *pCurrentHotNode = pHotHead;
	ColdNode *pCurrentColdNode = pColdHead;

	while (pCurrentNode != 0)
	{	
		pCurrentHotNode->key = pCurrentNode->key;
		pCurrentHotNode->pPrev = pCurrentHotNode - 1;
		pCurrentHotNode->pNext = pCurrentHotNode + 1;		
		pCurrentHotNode->pCold = pCurrentColdNode;
		
		pCurrentColdNode->x = pCurrentNode->x;
		pCurrentColdNode->y = pCurrentNode->y;
		pCurrentColdNode->z = pCurrentNode->z;
		pCurrentColdNode->A = pCurrentNode->A;
		pCurrentColdNode->B = pCurrentNode->B;
		pCurrentColdNode->C = pCurrentNode->C;
		pCurrentColdNode->MA = pCurrentNode->MA;
		pCurrentColdNode->MB = pCurrentNode->MB;
		pCurrentColdNode->MC = pCurrentNode->MC;
		pCurrentColdNode->MD = pCurrentNode->MD;
		memcpy(pCurrentColdNode->name, pCurrentNode->name, Node::NAME_SIZE);
		pCurrentColdNode->pHot = pCurrentHotNode;

		pCurrentNode = pCurrentNode->pNext;
		pCurrentHotNode++;
		pCurrentColdNode++;
	}

	pHotHead->pPrev = 0;
	pHotHead[size - 1].pNext = 0;
}

HotCold::~HotCold()
{
	delete this->pHotHead;
	delete this->pColdHead;
}

//----------------------------------------------------------------------------------
// Find Key using linked lists (pointers only) 
//    Hint: use ->pNext
//    YOU MUST - iterate through the nodes in a linked list fashion or 0 credit
//
// Return true if you find the node
// Return the pointer in the argument list to the HotNode and ColdNode (if found)
//----------------------------------------------------------------------------------
bool HotCold::FindKey(int key, ColdNode *&pFoundColdNode, HotNode *&pFoundHotNode)
{
	HotNode *pCurrentHotNode = this->pHotHead;
	while (pCurrentHotNode != 0)
	{
		if (pCurrentHotNode->key == key)
		{
			pFoundHotNode = pCurrentHotNode;
			pFoundColdNode = pCurrentHotNode->pCold;
			return true;
		}
		else
		{
			pCurrentHotNode = pCurrentHotNode->pNext;
		}
	}

	return false;
}

HotNode *HotCold::GetHotHead() const
{
	return this->pHotHead;
}

// ---  End of File ---------------
