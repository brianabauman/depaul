//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
// Optimized C++
//----------------------------------------------------------------------------- 

#include <malloc.h>
#include <new>

#include "Framework.h"

#include "Mem.h"
#include "Heap.h"
#include "Block.h"

#define STUB_PLEASE_REPLACE(x) (x)

// To help with coalescing... not required
struct SecretPtr
{
	Free *pFree;
};

// ----------------------------------------------------
//  Initialized the memory block:
// Format the heap
// Create a free block
// Heap structure links to free hdr
//-----------------------------------------------------
void Mem::initialize()
{
	Heap *pHeapTemp = this->getHeap();

	Free *pFreeStart = (Free *)(pHeapTemp + 1);
	Free *pFreeEnd = pFreeStart + 1;
	uint32_t blockSize = (uint32_t)pHeapTemp->mStats.heapBottomAddr - (uint32_t)pFreeEnd;

	PLACEMENT_NEW_BEGIN
	#undef new

	Free *pFree = new(pFreeStart) Free(blockSize);

	PLACEMENT_NEW_END

	pHeapTemp->pFreeHead = pFree;
	pHeapTemp->pUsedHead = nullptr;
	pHeapTemp->pNextFit = pFree;

	Heap::Stats *pStats = &pHeapTemp->mStats;
	pStats->currFreeMem = blockSize;
	pStats->currNumFreeBlocks = 1;
}

// ----------------------------------------------------
//  Do your Magic here:
// Find a free block that fits
// Change it to Used (may require subdivision)
// Correct the heap links (used,free) headers 
// Update stats
// Return pointer to block
//-----------------------------------------------------
void *Mem::malloc( const uint32_t size )
{
	Heap *pHeapTemp = this->pHeap;
	Free *pCurrentFree = pHeapTemp->pFreeHead;
	Used *pUsedStart = nullptr;

	//find a Free block to use
	while (pCurrentFree != nullptr)
	{
		if (pCurrentFree->mBlockSize >= size)
		{
			//remember initial Free block size
			uint32_t freeBlockSize = pCurrentFree->mBlockSize;

			//create a new Used block
			pUsedStart = (Used *)pCurrentFree;
			Used *pUsedEnd = pUsedStart + 1;

			PLACEMENT_NEW_BEGIN
			#undef new

			Used *pUsed = new(pUsedStart) Used(size);

			PLACEMENT_NEW_END
			
			placeUsedBlock(pHeapTemp, pUsed);
			
			//remove Free block
			removeFreeBlock(pHeapTemp, pCurrentFree);

			//update stats
			pHeapTemp->mStats.currFreeMem -= size;
			pHeapTemp->mStats.currUsedMem += size;
			if (pHeapTemp->mStats.currUsedMem > pHeapTemp->mStats.peakUsedMemory)
			{
				pHeapTemp->mStats.peakUsedMemory = pHeapTemp->mStats.currUsedMem;
			}
			pHeapTemp->mStats.currNumFreeBlocks -= 1;
			pHeapTemp->mStats.currNumUsedBlocks += 1;
			if (pHeapTemp->mStats.currNumUsedBlocks > pHeapTemp->mStats.peakNumUsed)
			{
				pHeapTemp->mStats.peakNumUsed = pHeapTemp->mStats.currNumUsedBlocks;
			}

			//leftover space becomes a new Free block
			if (freeBlockSize - size > sizeof(Free))
			{
				Free *pFreeStart = (Free *)((uint32_t)pUsedEnd + size);

				PLACEMENT_NEW_BEGIN
				#undef new

				Free *pFree = new(pFreeStart) Free(freeBlockSize - size - sizeof(Free));

				PLACEMENT_NEW_END

				//place Free block in appropriate position in Heap's Free block list
				placeFreeBlock(pHeapTemp, pFree);

				//update stats
				pHeapTemp->mStats.currFreeMem -= sizeof(Free);
				pHeapTemp->mStats.currNumFreeBlocks += 1;
			}
			
			break;
		}
		else
		{
			//check the next Free block
			pCurrentFree = pCurrentFree->pFreeNext;
		}
	}

	return (Used *)(pUsedStart + 1);
}

// ----------------------------------------------------
//  Do your Magic here:
// Return the free block to the system
// May require coalescing
// Correct the heap links (used,free) headers 
// Update stats
//-----------------------------------------------------
void Mem::free( void * const data )
{
	Heap *pHeapTemp = this->pHeap;
	Used *pUsed = (Used *)data - 1;
	uint32_t usedSize = pUsed->mBlockSize;

	//remove Used block
	removeUsedBlock(pHeapTemp, pUsed);
	
	//create a new Free block
	Free *pFreeStart = (Free *)(pUsed);

	PLACEMENT_NEW_BEGIN
	#undef new

	Free *pFree = new(pFreeStart) Free(usedSize);

	PLACEMENT_NEW_END

	placeFreeBlock(pHeap, pFree);

	//update stats
	pHeap->mStats.currFreeMem += usedSize;
	pHeap->mStats.currUsedMem -= usedSize;
	pHeapTemp->mStats.currNumFreeBlocks += 1;
	pHeapTemp->mStats.currNumUsedBlocks -= 1;
}

void Mem::placeUsedBlock(Heap *pHeapTemp, Used *pUsed)
{
	Used *pCurrentUsed = pHeapTemp->pUsedHead;
	if (pCurrentUsed == nullptr)
	{
		pHeapTemp->pUsedHead = pUsed;
	}
	else if (pCurrentUsed > pUsed)
	{
		pCurrentUsed->pUsedPrev = pUsed;
		pUsed->pUsedNext = pCurrentUsed;
		pHeapTemp->pUsedHead = pUsed;
	}
	else
	{
		do
		{
			if (pCurrentUsed->pUsedNext == nullptr)
			{
				pUsed->pUsedPrev = pCurrentUsed;
				pCurrentUsed->pUsedNext = pUsed;
				break;
			}
			else if (pCurrentUsed->pUsedNext > pUsed)
			{
				pUsed->pUsedPrev = pCurrentUsed;
				pUsed->pUsedNext = pCurrentUsed->pUsedNext;
				pCurrentUsed->pUsedNext = pUsed;
				pCurrentUsed->pUsedNext->pUsedPrev = pUsed;
				break;
			}

			pCurrentUsed = pCurrentUsed->pUsedNext;
		} while (pCurrentUsed < pUsed);
	}
}

void Mem::removeUsedBlock(Heap *pHeapTemp, Used *pUsed)
{
	Used *pCurrentUsed = pHeapTemp->pUsedHead;
	while (pCurrentUsed != nullptr)
	{
		if (pCurrentUsed == pUsed)
		{
			if (pCurrentUsed->pUsedNext == nullptr && pCurrentUsed->pUsedPrev == nullptr)
			{
				pHeapTemp->pUsedHead = nullptr;
			}
			if (pCurrentUsed->pUsedPrev != nullptr)
			{
				pCurrentUsed->pUsedPrev->pUsedNext = pCurrentUsed->pUsedNext;
			}
			if (pCurrentUsed->pUsedNext != nullptr)
			{
				pCurrentUsed->pUsedNext->pUsedPrev = pCurrentUsed->pUsedPrev;
				if (pHeapTemp->pUsedHead == pCurrentUsed)
				{
					pHeapTemp->pUsedHead = pCurrentUsed->pUsedNext;
				}
			}
			break;
		}

		pCurrentUsed = pCurrentUsed->pUsedNext;
	}
}

void Mem::placeFreeBlock(Heap *pHeapTemp, Free *pFree)
{
	Free *pCurrentFree = pHeapTemp->pFreeHead;
	if (pCurrentFree == nullptr)
	{
		pHeapTemp->pFreeHead = pFree;
	}
	else if (pCurrentFree > pFree)
	{
		pCurrentFree->pFreePrev = pFree;
		pFree->pFreeNext = pCurrentFree;
		pHeapTemp->pFreeHead = pFree;
		if ((uint32_t)pCurrentFree - pFree->mBlockSize - sizeof(Free) == (uint32_t)pFree)
		{
			pCurrentFree->mAboveBlockFree = true;
		}
	}
	else
	{
		do
		{
			if (pCurrentFree->pFreeNext == nullptr)
			{
				pFree->pFreePrev = pCurrentFree;
				pCurrentFree->pFreeNext = pFree;
				if ((uint32_t)pFree - pCurrentFree->mBlockSize - sizeof(Free) == (uint32_t)pCurrentFree)
				{
					pFree->mAboveBlockFree = true;
				}
				break;
			}
			else if (pCurrentFree->pFreeNext > pFree)
			{
				pFree->pFreePrev = pCurrentFree;
				pCurrentFree->pFreeNext = pFree;
				pFree->pFreeNext = pCurrentFree->pFreeNext;
				pCurrentFree->pFreeNext->pFreePrev = pFree;
				if ((uint32_t)pFree - pCurrentFree->mBlockSize - sizeof(Free) == (uint32_t)pCurrentFree)
				{
					pFree->mAboveBlockFree = true;
				}
				if ((uint32_t)pCurrentFree->pFreeNext - pFree->mBlockSize - sizeof(Free) == (uint32_t)pFree)
				{
					pCurrentFree->pFreeNext->mAboveBlockFree = true;
				}
				break;
			}

			pCurrentFree = pCurrentFree->pFreeNext;
		} while (pCurrentFree < pFree);
	}

	coalesceFreeBlocks(pHeapTemp);

	pHeapTemp->pNextFit = pFree;
}

void Mem::removeFreeBlock(Heap *pHeapTemp, Free *pFree)
{
	Free *pCurrentFree = pHeapTemp->pFreeHead;
	while (pCurrentFree != nullptr)
	{
		if (pCurrentFree == pFree)
		{
			if (pCurrentFree->pFreeNext == nullptr && pCurrentFree->pFreePrev == nullptr)
			{
				pHeapTemp->pFreeHead = nullptr;
			}
			if (pCurrentFree->pFreePrev != nullptr) 
			{ 
				pCurrentFree->pFreePrev->pFreeNext = pCurrentFree->pFreeNext; 
			}
			if (pCurrentFree->pFreeNext != nullptr) 
			{
				pCurrentFree->pFreeNext->pFreePrev = pCurrentFree->pFreePrev;
				if (pHeapTemp->pFreeHead == pCurrentFree)
				{
					pHeapTemp->pFreeHead = pCurrentFree->pFreeNext;
				}
			}
			break;
		}
		
		pCurrentFree = pCurrentFree->pFreeNext;
	}

	if (pCurrentFree == nullptr)
	{
		pHeapTemp->pNextFit = pHeapTemp->pFreeHead;
	}
	else
	{
		pHeapTemp->pNextFit = pCurrentFree->pFreeNext;
	}
}

void Mem::coalesceFreeBlocks(Heap *pHeapTemp)
{
	Free *pCurrentFree = pHeapTemp->pFreeHead;
	while (pCurrentFree != nullptr)
	{
		if (pCurrentFree->pFreeNext != nullptr &&
			pCurrentFree->pFreeNext->mAboveBlockFree)
		{
			//combine the following Free block with this one
			Free *pPrevFreeBlock = pCurrentFree->pFreePrev;
			Free *pNextFreeBlock = pCurrentFree->pFreeNext->pFreeNext;

			PLACEMENT_NEW_BEGIN
			#undef new

			Free *pCombinedFree = new(pCurrentFree) Free(pCurrentFree->mBlockSize + sizeof(Free) + pCurrentFree->pFreeNext->mBlockSize);

			PLACEMENT_NEW_END

			pCombinedFree->pFreeNext = pNextFreeBlock;
			pCombinedFree->pFreePrev = pPrevFreeBlock;

			if (pPrevFreeBlock != nullptr)
			{
				pPrevFreeBlock->pFreeNext = pCombinedFree;
			}
			if (pNextFreeBlock != nullptr)
			{
				pNextFreeBlock->pFreePrev = pCombinedFree;
			}

			//update stats
			pHeapTemp->mStats.currFreeMem += sizeof(Free);
			pHeapTemp->mStats.currNumFreeBlocks -= 1;
		}
		else
		{
			pCurrentFree = pCurrentFree->pFreeNext;
		}
	}
}

// ---  End of File ---------------
