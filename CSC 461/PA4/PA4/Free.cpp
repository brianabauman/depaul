//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
// Optimized C++
//----------------------------------------------------------------------------- 

#include "Framework.h"

#include "Used.h"
#include "Free.h"
#include "Block.h"

Free::Free(uint32_t blockSize, bool aboveBlockFree)
	: pFreeNext(nullptr),
	pFreePrev(nullptr),
	mBlockSize(blockSize),
	mAboveBlockFree(aboveBlockFree),
	mType(Block::Free),
	pad(0)
{
	//where does the secret pointer go?
	Free **pSecretPointerAddress = (Free **)((uint32_t)(this + 1) + blockSize - 4);
	*pSecretPointerAddress = this;
}

// ---  End of File ---------------
