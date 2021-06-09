//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
// Optimized C++
//----------------------------------------------------------------------------- 

#include "Framework.h"

#include "Free.h"
#include "Used.h"

Used::Used(uint32_t blockSize)
	: pUsedNext(nullptr),
	pUsedPrev(nullptr),
	mBlockSize(blockSize),
	mAboveBlockFree(false),
	mType(Block::Used),
	pad(0)
{

}

// ---  End of File ---------------
