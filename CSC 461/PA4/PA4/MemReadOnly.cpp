//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------- 

#include <malloc.h>
#include <new>

#include "Framework.h"

#include "Mem.h"
#include "Heap.h"
#include "Block.h"

#define STUB_PLEASE_REPLACE(x) (x)

#define HEAP_ALIGNMENT			16
#define HEAP_ALIGNMENT_MASK		(HEAP_ALIGNMENT-1)

#define ALLOCATION_ALIGNMENT		16
#define ALLOCATION_ALIGNMENT_MASK	(ALLOCATION_ALIGNMENT-1)

#define UNUSED_VAR(v)  ((void *)v)

#ifdef _DEBUG
	#define HEAP_HEADER_GUARDS  32
	#define HEAP_SET_GUARDS  	uint32_t *pE = (uint32_t *)((uint32_t)pRawMem + HEAP_SIZE); \
								*pE++ = 0xEEEEEEEE;*pE++ = 0xEEEEEEEE;*pE++ = 0xEEEEEEEE;*pE++ = 0xEEEEEEEE; \
								*pE++ = 0xEEEEEEEE;*pE++ = 0xEEEEEEEE;*pE++ = 0xEEEEEEEE;*pE++ = 0xEEEEEEEE; 

	#define HEAP_TEST_GUARDS	uint32_t *pE = (uint32_t *)((uint32_t)pRawMem + HEAP_SIZE); \
								assert(*pE++ == 0xEEEEEEEE);assert(*pE++ == 0xEEEEEEEE); \
								assert(*pE++ == 0xEEEEEEEE);assert(*pE++ == 0xEEEEEEEE); \
								assert(*pE++ == 0xEEEEEEEE);assert(*pE++ == 0xEEEEEEEE); \
								assert(*pE++ == 0xEEEEEEEE);assert(*pE++ == 0xEEEEEEEE); 
#else
	#define HEAP_HEADER_GUARDS  0
	#define HEAP_SET_GUARDS  	
	#define HEAP_TEST_GUARDS			 
#endif
							
Mem::~Mem()
{
	// do not modify this function
	HEAP_TEST_GUARDS
	_aligned_free(this->pRawMem);
}


Heap *Mem::getHeap()
{
	return this->pHeap;
}

Mem::Mem()
{
	// now initialize it.
	this->pHeap = 0;
	this->pRawMem = 0;

	// Do a land grab --- get the space for the whole heap
	// Since OS have different alignments... I forced it to 16 byte aligned
	pRawMem = _aligned_malloc(HEAP_SIZE + HEAP_HEADER_GUARDS, HEAP_ALIGNMENT);
	HEAP_SET_GUARDS

	// verify alloc worked
	assert(pRawMem != 0);

	// Guarantee alignemnt
	assert( ((uint32_t)pRawMem & HEAP_ALIGNMENT_MASK) == 0x0 ); 

	// ------------------------------------------------------------------------
	// Instantiate the heap header on the raw memory
	//
	// Placement new will interact with the memory tracking system:
	//
	//      No memory tracking __SHOULD__ take place on placement new
	//      So you need to tell the Memory Tracking system to ignore this placement new
	//      Add 3 lines around placement new to allow it to compile
	//
	//      example:  Dog *pDog = new(address) Dog();  // original (new way below)
	//
	//      PLACEMENT_NEW_BEGIN <----- Add 1/3 --------------
	//      #undef new  <----- Add 2/3 --------------
	// 
	//    Dog *pDog = new(address) Dog();
	//
	//      PLACEMENT_NEW_END   <----- Add 3/3 --------------
	//
	// -----------------------------------------------------------------------
	PLACEMENT_NEW_BEGIN
	#undef new

		Heap *p = new(pRawMem) Heap(pRawMem);

	PLACEMENT_NEW_END    

	// update it
	this->pHeap = p;
}

void Mem::dump()
{

	fprintf(FileIO::GetHandle(),"\n------- dump -------------\n\n");

	fprintf(FileIO::GetHandle(), "heapStart: 0x%p     \n", this->pHeap );
	fprintf(FileIO::GetHandle(), "  heapEnd: 0x%p   \n\n", this->pHeap->mStats.heapBottomAddr );
	fprintf(FileIO::GetHandle(), "pUsedHead: 0x%p     \n", this->pHeap->pUsedHead );
	fprintf(FileIO::GetHandle(), "pFreeHead: 0x%p     \n", this->pHeap->pFreeHead );
	fprintf(FileIO::GetHandle(), " pNextFit: 0x%p   \n\n", this->pHeap->pNextFit);

	fprintf(FileIO::GetHandle(),"Heap Hdr   s: %p  e: %p \t\t\t\t\t  size: 0x%x \n",(void *)((uint32_t)this->pHeap->mStats.heapTopAddr-sizeof(Heap)), this->pHeap->mStats.heapTopAddr, sizeof(Heap) );

	uint32_t p = (uint32_t)pHeap->mStats.heapTopAddr;

	char *type;
	char *typeHdr;

	while( p < (uint32_t)pHeap->mStats.heapBottomAddr )
	{
		Used *used = (Used *)p;
		if( used->mType == Block::Used )
		{
			typeHdr = "USED HDR ";
			type    = "USED     ";
		}
		else
		{
			typeHdr = "FREE HDR ";
			type    = "FREE     ";
		}

		uint32_t hdrStart = (uint32_t)used;
		uint32_t hdrEnd   = (uint32_t)used + sizeof(Used);
		fprintf(FileIO::GetHandle(),"%s  s: %p  e: %p  p: %p  n: %p  size: 0x%x    AF: %d \n",typeHdr, (void *)hdrStart, (void *)hdrEnd, used->pUsedPrev, used->pUsedNext, sizeof(Used), used->mAboveBlockFree );
		uint32_t blkStart = hdrEnd;
		uint32_t blkEnd   = blkStart + used->mBlockSize; 
		fprintf(FileIO::GetHandle(),"%s  s: %p  e: %p \t\t\t\t\t  size: 0x%x \n",type, (void *)blkStart, (void *)blkEnd, used->mBlockSize );

		p = blkEnd;
	
	}
}

// ---  End of File ---------------
