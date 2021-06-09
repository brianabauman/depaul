//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------- 

#ifndef HOTCOLD_H
#define HOTCOLD_H

#include "ColdNode.h"
#include "HotNode.h"

class HotCold
{
public:
	HotCold() = delete;
	HotCold(const HotCold &) = delete;
	HotCold & operator = (const HotCold &) = delete;

	HotCold( const Bloated * const pBloated );	
	~HotCold();

	bool FindKey(int key, ColdNode *&pFoundColdNode, HotNode *&pFoundHotNode);

	HotNode *GetHotHead() const;

private:
	unsigned int Size;
	HotNode		*pHotHead;
	ColdNode	*pColdHead;
};

#endif

// ---  End of File ---------------

