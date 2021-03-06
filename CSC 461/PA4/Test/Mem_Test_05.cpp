//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------- 

#include "Framework.h"
#include "_UnitTestConfiguration.h"

#include "Mem.h"

// ---------------------------------------
//  DO NOT MODIFY this FILE
// ---------------------------------------

#define PTR_FIX(x)  (unsigned int)(x == 0) ? 0: ((unsigned int)x - (unsigned int)h) 
#define UNUSED_VAR(p) ((void *)p)

#if Mem5_Partial_allocate_free_Test_Enable
TEST(Partial_allocate_free, MemoryShakeOut, Mem5_Partial_allocate_free_Test_Enable)
{
	FileIO::Open("Student_", "Test_05");

	fprintf(FileIO::GetHandle(), "Test5: \n\n");

	fprintf(FileIO::GetHandle(), " 1) allocate block                    \n");
	fprintf(FileIO::GetHandle(), " 2) free block                        \n\n");

	fprintf(FileIO::GetHandle(), "     Mem mem;                   \n");
	fprintf(FileIO::GetHandle(), "     mem.initialize();          \n");
	fprintf(FileIO::GetHandle(), "     void *p = mem.malloc( 0x200 );     \n");
	fprintf(FileIO::GetHandle(), "     mem.dump();                      \n");
	fprintf(FileIO::GetHandle(), "     mem.free( p );                   \n");
	fprintf(FileIO::GetHandle(), "     mem.dump();                      \n");

	// Part A:
	Mem mem1;
	mem1.initialize();
	void *p1 = mem1.malloc(0x200);
	mem1.dump();

	// Part B:
	mem1.free(p1);
	mem1.dump();

	FileIO::Close();

	// ----  GENERAL CHECK ------------------------------------------------------

	// ---- Part A: -------------------------------------------------------------

	Mem mem;
	mem.initialize();
	void *p = mem.malloc(0x200);

	// ---- Verify A: -----------------------------------------------------------

	Heap *h = mem.getHeap();

	// Sanit check, make sure everything is heap relative for testing
	CHECK_EQUAL(PTR_FIX(h), 0);

	// Heap Start / Heap Bottom
	CHECK_EQUAL(PTR_FIX(h->mStats.heapTopAddr), 0x30);
	CHECK_EQUAL(PTR_FIX(h->mStats.heapBottomAddr), Mem::HEAP_SIZE);

	// Used / Free
	CHECK_EQUAL(PTR_FIX(h->pFreeHead), 0x240);
	CHECK_EQUAL(PTR_FIX(h->pNextFit), 0x240);
	CHECK_EQUAL(PTR_FIX(h->pUsedHead), 0x30);

	// ---- Heap Stats ------------------------------------------------------

	CHECK_EQUAL(h->mStats.peakNumUsed, 1);
	CHECK_EQUAL(h->mStats.peakUsedMemory, 0x200);

	CHECK_EQUAL(h->mStats.currNumUsedBlocks, 1);
	CHECK_EQUAL(h->mStats.currUsedMem, 0x200);

	CHECK_EQUAL(h->mStats.currNumFreeBlocks, 1);
	CHECK_EQUAL(h->mStats.currFreeMem, 0xc5b0);

	CHECK_EQUAL(h->mStats.sizeHeap, 0xc800);

	CHECK_EQUAL(PTR_FIX(h->mStats.heapTopAddr), 0x30);
	CHECK_EQUAL(PTR_FIX(h->mStats.heapBottomAddr), 0xc800);


	// ---- Heap Walk ------------------------------------------------------

	// ---- Heap Hdr -------------------------------------------------------

	// HeapHdr Start
	CHECK_EQUAL(PTR_FIX((uint32_t)h->mStats.heapTopAddr - sizeof(Heap)), 0);
	// HeapHdr End
	CHECK_EQUAL(PTR_FIX(h->mStats.heapTopAddr), sizeof(Heap));

	// ----  Block walk ------------------------------------------------------

	uint32_t hdrStart;
	uint32_t hdrEnd;
	uint32_t blkStart;
	uint32_t blkEnd;

	// ---- USED HDR -------------------------------------------

		// Check type
	Used *used = (Used *)h->mStats.heapTopAddr;
	// Should be USED
	CHECK_EQUAL(used->mType, Block::Used);
	CHECK_EQUAL(used->pad, 0);
	// Above Free
	CHECK_EQUAL(used->mAboveBlockFree, false);

	hdrStart = (uint32_t)used;
	hdrEnd = (uint32_t)used + sizeof(Used);

	// Hdr Start
	CHECK_EQUAL(PTR_FIX(hdrStart), 0x30);
	// Hdr End
	CHECK_EQUAL(PTR_FIX(hdrEnd), 0x40);
	// Prev
	CHECK_EQUAL(used->pUsedPrev, 0);
	// Next
	CHECK_EQUAL(used->pUsedNext, 0);
	// Hdr Size
	CHECK_EQUAL(hdrEnd - hdrStart, sizeof(Used));

	// ---- USED BLOCK ----------------------------------------------------

	blkStart = hdrEnd;
	blkEnd = blkStart + used->mBlockSize;

	CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
	CHECK_EQUAL(PTR_FIX(p), PTR_FIX(hdrEnd));
	CHECK_EQUAL(PTR_FIX(blkEnd), 0x240);
	CHECK_EQUAL(used->mBlockSize, 0x200);

	// ---- FREE HDR -------------------------------------------

		// Check type
	Free *free = (Free *)blkEnd;
	// Should be USED
	CHECK_EQUAL(free->mType, Block::Free);
	CHECK_EQUAL(free->pad, 0);
	// Above Free
	CHECK_EQUAL(free->mAboveBlockFree, false);

	hdrStart = (uint32_t)free;
	hdrEnd = (uint32_t)free + sizeof(Free);

	// Hdr Start
	CHECK_EQUAL(PTR_FIX(hdrStart), 0x240);
	// Hdr End
	CHECK_EQUAL(PTR_FIX(hdrEnd), 0x250);
	// Prev
	CHECK_EQUAL(free->pFreePrev, 0);
	// Next
	CHECK_EQUAL(free->pFreeNext, 0);
	// Hdr Size
	CHECK_EQUAL(hdrEnd - hdrStart, sizeof(Free));

	// ---- FREE BLOCK ----------------------------------------------------

	blkStart = hdrEnd;
	blkEnd = blkStart + free->mBlockSize;

	CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
	CHECK_EQUAL(PTR_FIX(blkEnd), 0xc800);
	CHECK_EQUAL(free->mBlockSize, 0xc5b0);


	// ---- Part B: -------------------------------------------------------------

	mem.free(p);

	// ---- Verify B: -----------------------------------------------------------


		// Sanit check, make sure everything is heap relative for testing
	CHECK_EQUAL(PTR_FIX(h), 0);

	// Used / Free
	CHECK_EQUAL(PTR_FIX(h->pFreeHead), 0x30);
	CHECK_EQUAL(PTR_FIX(h->pNextFit), 0x30);
	CHECK_EQUAL(h->pUsedHead, 0x0);

	// ---- Heap Stats ------------------------------------------------------

	CHECK_EQUAL(h->mStats.peakNumUsed, 1);
	CHECK_EQUAL(h->mStats.peakUsedMemory, 0x200);

	CHECK_EQUAL(h->mStats.currNumUsedBlocks, 0);
	CHECK_EQUAL(h->mStats.currUsedMem, 0x0);

	CHECK_EQUAL(h->mStats.currNumFreeBlocks, 1);
	CHECK_EQUAL(h->mStats.currFreeMem, 0xc7c0);

	CHECK_EQUAL(h->mStats.sizeHeap, 0xc800);

	CHECK_EQUAL(PTR_FIX(h->mStats.heapTopAddr), 0x30);
	CHECK_EQUAL(PTR_FIX(h->mStats.heapBottomAddr), 0xc800);


	// ---- Heap Walk ------------------------------------------------------

	// ---- Heap Hdr -------------------------------------------------------

	// HeapHdr Start
	CHECK_EQUAL(PTR_FIX((uint32_t)h->mStats.heapTopAddr - sizeof(Heap)), 0);
	// HeapHdr End
	CHECK_EQUAL(PTR_FIX(h->mStats.heapTopAddr), sizeof(Heap));

	// ----  Block walk ------------------------------------------------------

	// ---- FREE HDR -------------------------------------------

	// Check type
	free = (Free *)h->mStats.heapTopAddr;
	// Should be USED
	CHECK_EQUAL(free->mType, Block::Free);
	CHECK_EQUAL(free->pad, 0);
	// Above Free
	CHECK_EQUAL(free->mAboveBlockFree, false);

	hdrStart = (uint32_t)free;
	hdrEnd = (uint32_t)free + sizeof(Free);

	// Hdr Start
	CHECK_EQUAL(PTR_FIX(hdrStart), 0x30);
	// Hdr End
	CHECK_EQUAL(PTR_FIX(hdrEnd), 0x40);
	// Prev
	CHECK_EQUAL(free->pFreePrev, 0);
	// Next
	CHECK_EQUAL(free->pFreeNext, 0);
	// Hdr Size
	CHECK_EQUAL(hdrEnd - hdrStart, sizeof(Free));

	// ---- FREE BLOCK ----------------------------------------------------

	blkStart = hdrEnd;
	blkEnd = blkStart + free->mBlockSize;

	CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
	CHECK_EQUAL(PTR_FIX(blkEnd), 0xc800);
	CHECK_EQUAL(free->mBlockSize, 0xc7c0);

}  TEST_END
#endif

// ---  End of File ---------------
