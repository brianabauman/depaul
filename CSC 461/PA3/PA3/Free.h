//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
// Optimized C++
//----------------------------------------------------------------------------- 

#ifndef FREE_H
#define FREE_H

#include "Types.h"
#include "Block.h"

class Used;

class Free
{
public:
	// ------------------------------------------------
	// Do not reorder, change or add data fields
	// You can add methods if you wish
	// ------------------------------------------------
	Free() = delete;
	~Free() = delete;
	Free(const Free &) = delete;
	Free & operator=(const Free &tmp) = delete;

	Free(uint32_t blockSize);

	Free	 *pFreeNext;		// next free block
	Free	 *pFreePrev;		// prev free block
	uint32_t mBlockSize;		// size of block
	bool	mAboveBlockFree;	// AboveBlock flag:
								// if(AboveBlock is type free) -> true 
								// if(AboveBlock is type used) -> false 
	Block	 mType;				// block type 
	uint16_t pad;				// future use

};

#endif 

// ---  End of File ---------------
