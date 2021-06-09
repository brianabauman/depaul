//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
// Optimized C++
//----------------------------------------------------------------------------- 

#ifndef USED_H
#define USED_H

#include "Types.h"
#include "Block.h"

class Free;

class Used
{
public:
	// ------------------------------------------------
	// Do not reorder, change or add data fields
	// You can add methods if you wish
	// ------------------------------------------------
	Used() = delete;
	~Used() = delete;
	Used(const Used &) = delete;
	Used & operator=(const Used &tmp) = delete;

	Used(uint32_t blockSize);

	Used       *pUsedNext;       // next used block
	Used       *pUsedPrev;       // prev used block
	uint32_t   mBlockSize;       // size of block
	bool       mAboveBlockFree;  // AboveBlock flag:
								 // if(AboveBlock is type free) -> true 
								 // if(AboveBlock is type used) -> false
	Block		mType;	// block type 
	uint16_t	pad;	// future use

};

#endif 

// ---  End of File ---------------
