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
	Free *pFree = new(pFreeStart) Free(blockSize, false);
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
void *Mem::malloc(const uint32_t size)
{
	Heap *pHeapTemp = this->pHeap;
	Free *pCurrentFree = pHeapTemp->pNextFit;
	Used *pUsed = nullptr;

	//find a Free block to use
	while (pCurrentFree != nullptr)
	{
		if (pCurrentFree->mBlockSize >= size)
		{
			uint32_t freeBlockSize = pCurrentFree->mBlockSize;

			removeFreeBlock(pHeapTemp, pCurrentFree);

			//create a new used block
			PLACEMENT_NEW_BEGIN
			#undef new
			pUsed = new(pCurrentFree) Used(size);
			PLACEMENT_NEW_END

			placeUsedBlock(pHeapTemp, pUsed);

			//leftover space becomes a new free block
			if (freeBlockSize - size > sizeof(Free))
			{
				Free *pFreeStart = (Free *)((uint32_t)(pUsed + 1) + size);
				PLACEMENT_NEW_BEGIN
				#undef new
				Free *pFree = new(pFreeStart) Free(freeBlockSize - size - sizeof(Free), false);
				PLACEMENT_NEW_END

				placeFreeBlock(pHeapTemp, pFree, false, true);
			}

			break;
		}
		else pCurrentFree = pCurrentFree->pFreeNext;
		
		if (pCurrentFree == nullptr) pCurrentFree = pHeapTemp->pFreeHead;
	}

	return (Used *)(pUsed + 1);
}

// ----------------------------------------------------
//  Do your Magic here:
// Return the free block to the system
// May require coalescing
// Correct the heap links (used,free) headers 
// Update stats
//-----------------------------------------------------
void Mem::free(void * const data)
{
	Heap *pHeapTemp = this->pHeap;
	Used *pUsed = (Used *)data - 1;

	removeUsedBlock(pHeapTemp, pUsed);

	PLACEMENT_NEW_BEGIN
	#undef new
	Free *pFree = new(pUsed) Free(pUsed->mBlockSize, pUsed->mAboveBlockFree);
	PLACEMENT_NEW_END
	
	placeFreeBlock(pHeap, pFree, pFree->mAboveBlockFree, false);
}

void Mem::placeUsedBlock(Heap *pHeapTemp, Used *pUsed)
{
	//place used block at the head of the list
	if (pHeapTemp->pUsedHead == nullptr) pHeapTemp->pUsedHead = pUsed;
	else
	{
		pUsed->pUsedNext = pHeapTemp->pUsedHead;
		pHeapTemp->pUsedHead->pUsedPrev = pUsed;
		pHeapTemp->pUsedHead = pUsed;
	}

	//update stats
	pHeapTemp->mStats.currUsedMem += pUsed->mBlockSize;
	pHeapTemp->mStats.currNumUsedBlocks += 1;
	if (pHeapTemp->mStats.currUsedMem > pHeapTemp->mStats.peakUsedMemory)
	{
		pHeapTemp->mStats.peakUsedMemory = pHeapTemp->mStats.currUsedMem;
	}
	if (pHeapTemp->mStats.currNumUsedBlocks > pHeapTemp->mStats.peakNumUsed)
	{
		pHeapTemp->mStats.peakNumUsed = pHeapTemp->mStats.currNumUsedBlocks;
	}
}

void Mem::removeUsedBlock(Heap *pHeapTemp, Used *pUsed)
{
	//remove used block from chain
	if (pHeapTemp->pUsedHead == pUsed)
	{
		pHeapTemp->pUsedHead = pUsed->pUsedNext;
		if (pUsed->pUsedNext != nullptr) pUsed->pUsedNext->pUsedPrev = 0;
	}
	else
	{
		if (pUsed->pUsedPrev != nullptr) pUsed->pUsedPrev->pUsedNext = pUsed->pUsedNext;
		if (pUsed->pUsedNext != nullptr) pUsed->pUsedNext->pUsedPrev = pUsed->pUsedPrev;
	}

	//update stats
	pHeapTemp->mStats.currUsedMem -= pUsed->mBlockSize;
	pHeapTemp->mStats.currNumUsedBlocks -= 1;
}

void Mem::placeFreeBlock(Heap *pHeapTemp, Free *pFree, bool aboveBlockFree, bool mallocInd)
{
	Free *pAboveBlock = *(Free **)((uint32_t)pFree - 4);
	Free *pBelowBlock = (Free *)((uint32_t)(pFree + 1) + pFree->mBlockSize);
	bool belowBlockFree = pBelowBlock->mType == Block::Free;

	//placing a free block in between two free blocks
	if (aboveBlockFree && belowBlockFree)
	{
		//increase the size of the top block to contain all three blocks
		pAboveBlock->mBlockSize += (pFree->mBlockSize + pBelowBlock->mBlockSize + 2 * sizeof(Free));

		//remove the bottom block from the chain
		pAboveBlock->pFreeNext = pBelowBlock->pFreeNext;
		if (pAboveBlock->pFreeNext != nullptr) pAboveBlock->pFreeNext->pFreePrev = pAboveBlock;
		
		//update secret pointer
		Free **pSecretPointerAddress = (Free **)((uint32_t)(pBelowBlock + 1) + pBelowBlock->mBlockSize - 4);
		*pSecretPointerAddress = pAboveBlock;

		//update next fit
		if (pHeapTemp->pNextFit == pBelowBlock) pHeapTemp->pNextFit = pAboveBlock;

		//update stats
		pHeapTemp->mStats.currFreeMem += (pFree->mBlockSize + 2 * sizeof(Free));
		pHeapTemp->mStats.currNumFreeBlocks -= 1;
	}
	//placing a free block below a free block
	else if (aboveBlockFree)
	{
		//increase the size of the top block to include the new free block
		pAboveBlock->mBlockSize += (pFree->mBlockSize + sizeof(Free));

		//update secret pointer
		Free **pSecretPointerAddress = (Free **)((uint32_t)(pFree + 1) + pFree->mBlockSize - 4);
		*pSecretPointerAddress = pAboveBlock;

		//update below block info
		if (pBelowBlock->mType == Block::Used) pBelowBlock->mAboveBlockFree = true;

		//upate stats
		pHeapTemp->mStats.currFreeMem += (pFree->mBlockSize + sizeof(Free));
	}
	//placing a free block above a free block
	else if (belowBlockFree)
	{
		//increase the size of the new free block
		pFree->mBlockSize += (pBelowBlock->mBlockSize + sizeof(Free));

		//place the new free block in front of the below block
		pFree->pFreePrev = pBelowBlock->pFreePrev;
		pFree->pFreeNext = pBelowBlock->pFreeNext;
		if (pBelowBlock->pFreePrev == nullptr) pHeapTemp->pFreeHead = pFree;
		else pFree->pFreePrev->pFreeNext = pFree;
		if (pFree->pFreeNext != nullptr) pFree->pFreeNext->pFreePrev = pFree;

		//update secret pointer
		Free **pSecretPointerAddress = (Free **)((uint32_t)(pBelowBlock + 1) + pBelowBlock->mBlockSize - 4);
		*pSecretPointerAddress = pFree;

		//update next fit
		if (pHeapTemp->pNextFit == pBelowBlock) pHeapTemp->pNextFit = pFree;

		//update stats
		pHeapTemp->mStats.currFreeMem += (pFree->mBlockSize - pBelowBlock->mBlockSize);
	}
	//placing a free block between two used blocks
	else
	{
		//iterate through free blocks until its place arrives
		Free *pCurrentFree = pHeapTemp->pFreeHead;
		if (pCurrentFree == nullptr) pHeapTemp->pFreeHead = pFree;
		while (pCurrentFree != nullptr)
		{
			if (pCurrentFree > pFree)
			{
				pFree->pFreeNext = pCurrentFree;
				pFree->pFreePrev = pCurrentFree->pFreePrev;
				pCurrentFree->pFreePrev = pFree;
				if (pFree->pFreePrev != nullptr) pFree->pFreePrev->pFreeNext = pFree;
				else pHeapTemp->pFreeHead = pFree;
				break;
			}
			else if (pCurrentFree->pFreeNext == nullptr)
			{
				pCurrentFree->pFreeNext = pFree;
				pFree->pFreePrev = pCurrentFree;
				break;
			}

			pCurrentFree = pCurrentFree->pFreeNext;
		}

		//update below block info
		if (pBelowBlock->mType == Block::Used) pBelowBlock->mAboveBlockFree = true;

		//update next fit
		if (mallocInd) pHeapTemp->pNextFit = pFree;

		//update stats
		pHeapTemp->mStats.currFreeMem += pFree->mBlockSize;
		pHeapTemp->mStats.currNumFreeBlocks += 1;
	}

	if (pHeapTemp->pNextFit == nullptr) pHeapTemp->pNextFit = pHeapTemp->pFreeHead;
}

void Mem::removeFreeBlock(Heap *pHeapTemp, Free *pFree)
{
	//remove the block from the list
	if (pHeapTemp->pFreeHead == pFree) 
	{ 
		pHeapTemp->pFreeHead = pFree->pFreeNext;
	}
	else
	{
		if (pFree->pFreePrev != nullptr) pFree->pFreePrev->pFreeNext = pFree->pFreeNext;
		if (pFree->pFreeNext != nullptr) pFree->pFreeNext->pFreePrev = pFree->pFreePrev;
	}

	//set next fit
	if (pHeapTemp->pNextFit == pFree)
	{
		if (pFree->pFreeNext != nullptr) pHeapTemp->pNextFit = pFree->pFreeNext;
		else pHeapTemp->pNextFit = pHeapTemp->pFreeHead;
	}

	//update stats
	pHeapTemp->mStats.currFreeMem -= pFree->mBlockSize;
	pHeapTemp->mStats.currNumFreeBlocks -= 1;
}

// ---  End of File ---------------
