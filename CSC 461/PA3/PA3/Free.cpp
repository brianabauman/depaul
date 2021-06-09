//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
// Optimized C++
//----------------------------------------------------------------------------- 

#include "Framework.h"

#include "Used.h"
#include "Free.h"
#include "Block.h"

Free::Free(uint32_t blockSize)
	: pFreeNext(nullptr),
	  pFreePrev(nullptr),
	  mBlockSize(blockSize),
	  mAboveBlockFree(false),
	  mType(Block::Free),
	  pad(0)
{

}

// ---  End of File ---------------
