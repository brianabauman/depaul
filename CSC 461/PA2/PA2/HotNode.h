//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------- 

#ifndef HOT_NODE_H
#define HOT_NODE_H

class ColdNode;

class HotNode
{
public:
	int			key;
	HotNode		*pNext;
	HotNode		*pPrev;
	ColdNode	*pCold;
};

#endif

// ---  End of File ---------------
