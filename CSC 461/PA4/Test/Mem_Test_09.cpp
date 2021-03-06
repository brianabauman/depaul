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

#if Mem9_Allocate_3_middle_down_free_Test_Enable
TEST( Allocate_3_middle_down_free , MemoryShakeOut, Mem9_Allocate_3_middle_down_free_Test_Enable)
{
	FileIO::Open("Student_", "Test_09");

	fprintf(FileIO::GetHandle(),"Test9: \n\n");

	fprintf(FileIO::GetHandle()," 1) used                  \n");
	fprintf(FileIO::GetHandle()," 2) used                  \n");
	fprintf(FileIO::GetHandle()," 3) used                  \n");
   	fprintf(FileIO::GetHandle()," 4) free middle down    \n\n");


	fprintf(FileIO::GetHandle(),"     Mem mem;                     \n");
	fprintf(FileIO::GetHandle(),"     mem.initialize();            \n");

   	fprintf(FileIO::GetHandle(),"     void *a = mem.malloc( 0x200 );       \n");
   	fprintf(FileIO::GetHandle(),"     void *b = mem.malloc( 0x200 );       \n");
	fprintf(FileIO::GetHandle(),"     void *c = mem.malloc( 0x200 );       \n");
       
	fprintf(FileIO::GetHandle(),"     mem.dump();                        \n");
	fprintf(FileIO::GetHandle(),"     mem.free( b );                     \n");
	fprintf(FileIO::GetHandle(),"     mem.dump();                        \n");
	fprintf(FileIO::GetHandle(),"     mem.free( c );                     \n");
	fprintf(FileIO::GetHandle(),"     mem.dump();                        \n");
	fprintf(FileIO::GetHandle(),"     mem.free( a );                     \n");
	fprintf(FileIO::GetHandle(),"     mem.dump();                        \n");

	// Part A:
	Mem mem1;
	mem1.initialize();

   	void *a1 = mem1.malloc( 0x200 );
   	void *b1 = mem1.malloc( 0x200 );
	void *c1 = mem1.malloc( 0x200 );

	mem1.dump();

	// Part B:
	mem1.free( b1 );
	mem1.dump();

	// Part C:
	mem1.free( c1 );
	mem1.dump();

	// Part D:
	mem1.free( a1 );
	mem1.dump();

	FileIO::Close();

	// ----  GENERAL CHECK ------------------------------------------------------

	// ---- Part A: -------------------------------------------------------------
	
	Mem mem;
	mem.initialize();

   	void *a = mem.malloc( 0x200 );
   	void *b = mem.malloc( 0x200 );
	void *c = mem.malloc( 0x200 );

	// ---- Verify A: -----------------------------------------------------------

		Heap *h = mem.getHeap();

		// Sanit check, make sure everything is heap relative for testing
		CHECK_EQUAL( PTR_FIX(h), 0 );

		// Heap Start / Heap Bottom
		CHECK_EQUAL( PTR_FIX(h->mStats.heapTopAddr), 0x30 );
		CHECK_EQUAL( PTR_FIX(h->mStats.heapBottomAddr), Mem::HEAP_SIZE);

		// Used / Free
		CHECK_EQUAL( PTR_FIX(h->pFreeHead), 0x660 );
		CHECK_EQUAL( PTR_FIX(h->pUsedHead), 0x450 );

	// ---- Heap Stats ------------------------------------------------------

		CHECK_EQUAL( h->mStats.peakNumUsed, 3 );
		CHECK_EQUAL( h->mStats.peakUsedMemory, 0x600);

		CHECK_EQUAL( h->mStats.currNumUsedBlocks, 3);
		CHECK_EQUAL( h->mStats.currUsedMem, 0x600 );
		
		CHECK_EQUAL( h->mStats.currNumFreeBlocks, 1 );
		CHECK_EQUAL( h->mStats.currFreeMem, 0xc190 );

		CHECK_EQUAL( h->mStats.sizeHeap, 0xc800 );

		CHECK_EQUAL( PTR_FIX( h->mStats.heapTopAddr), 0x30 );
		CHECK_EQUAL( PTR_FIX(h->mStats.heapBottomAddr), 0xc800 );

	// ---- Heap Hdr -------------------------------------------------------

		// HeapHdr Start
		CHECK_EQUAL( PTR_FIX( (uint32_t)h->mStats.heapTopAddr-sizeof(Heap) ), 0 );
		// HeapHdr End
		CHECK_EQUAL( PTR_FIX(h->mStats.heapTopAddr), sizeof(Heap) );


	// ----  Block walk ------------------------------------------------------
		
		uint32_t hdrStart;
		uint32_t hdrEnd;
		uint32_t blkStart;
		uint32_t blkEnd; 
		uint32_t secret;

	// ---- USED HDR 1 -------------------------------------------

		// Check type
		Used *used = (Used *) h->mStats.heapTopAddr;
		// Should be USED
		CHECK_EQUAL( used->mType, Block::Used );
		CHECK_EQUAL(used->pad, 0);
		// Above Free
		CHECK_EQUAL(used->mAboveBlockFree, false);
		
		hdrStart = (uint32_t)used;
		hdrEnd   = (uint32_t)used + sizeof(Used);
	
		// Hdr Start
		CHECK_EQUAL( PTR_FIX(hdrStart), 0x30  );
		// Hdr End
		CHECK_EQUAL( PTR_FIX(hdrEnd), 0x40 );
		// Prev
		CHECK_EQUAL( PTR_FIX(used->pUsedPrev), 0x240 );
		// Next
		CHECK_EQUAL( used->pUsedNext, 0 );
		// Hdr Size
		CHECK_EQUAL( hdrEnd - hdrStart, sizeof(Used) );
	
		blkStart = hdrEnd;
		blkEnd   = blkStart + used->mBlockSize; 
		
		CHECK_EQUAL( PTR_FIX(blkStart), PTR_FIX(hdrEnd) );
		CHECK_EQUAL( PTR_FIX(blkEnd), 0x240);
		CHECK_EQUAL( used->mBlockSize, 0x200 );
	
	// ---- Used HDR 2 -------------------------------------------

		// Check type
		used = (Used *) blkEnd;
		// Should be USED
		CHECK_EQUAL( used->mType, Block::Used );
		CHECK_EQUAL(used->pad, 0);
		// Above Free
		CHECK_EQUAL(used->mAboveBlockFree, false);
		
		hdrStart = (uint32_t)used;
		hdrEnd   = (uint32_t)used + sizeof(Used);
	
		// Hdr Start
		CHECK_EQUAL( PTR_FIX(hdrStart), 0x240 );
		// Hdr End
		CHECK_EQUAL( PTR_FIX(hdrEnd), 0x250 );
		// Prev
		CHECK_EQUAL( PTR_FIX(used->pUsedPrev), 0x450 );
		// Next
		CHECK_EQUAL( PTR_FIX(used->pUsedNext), 0x30 );
		// Hdr Size
		CHECK_EQUAL( hdrEnd - hdrStart, sizeof(Used) );
	
		blkStart = hdrEnd;
		blkEnd   = blkStart + used->mBlockSize; 
		
		CHECK_EQUAL( PTR_FIX(blkStart), PTR_FIX(hdrEnd) );
		CHECK_EQUAL( PTR_FIX(blkEnd), 0x450);
		CHECK_EQUAL( used->mBlockSize, 0x200 );

	// ---- Used HDR 3 -------------------------------------------

		// Check type
		used = (Used *) blkEnd;
		// Should be USED
		CHECK_EQUAL( used->mType, Block::Used );
		CHECK_EQUAL(used->pad, 0);
		// Above Free
		CHECK_EQUAL(used->mAboveBlockFree, false);
		
		hdrStart = (uint32_t)used;
		hdrEnd   = (uint32_t)used + sizeof(Used);
	
		// Hdr Start
		CHECK_EQUAL( PTR_FIX(hdrStart), 0x450 );
		// Hdr End
		CHECK_EQUAL( PTR_FIX(hdrEnd), 0x460 );
		// Prev
		CHECK_EQUAL( used->pUsedPrev, 0);
		// Next
		CHECK_EQUAL( PTR_FIX(used->pUsedNext), 0x240 );
		// Hdr Size
		CHECK_EQUAL( hdrEnd - hdrStart, sizeof(Used) );
	
		blkStart = hdrEnd;
		blkEnd   = blkStart + used->mBlockSize; 
		
		CHECK_EQUAL( PTR_FIX(blkStart), PTR_FIX(hdrEnd) );
		CHECK_EQUAL( PTR_FIX(blkEnd), 0x660);
		CHECK_EQUAL( used->mBlockSize, 0x200 );

	// ---- free HDR 4 -------------------------------------------

		// Check type
		Free *free = (Free *) blkEnd;
		// Should be USED
		CHECK_EQUAL( free->mType, Block::Free );
		CHECK_EQUAL(free->pad, 0);
		// Above Free
		CHECK_EQUAL(free->mAboveBlockFree, false);
		
		hdrStart = (uint32_t)free;
		hdrEnd   = (uint32_t)free + sizeof(Free);
	
		// Hdr Start
		CHECK_EQUAL( PTR_FIX(hdrStart), 0x660 );
		// Hdr End
		CHECK_EQUAL( PTR_FIX(hdrEnd), 0x670 );
		// Prev
		CHECK_EQUAL( free->pFreePrev, 0x0 );
		// Next
		CHECK_EQUAL( free->pFreeNext, 0x0 );
		// Hdr Size
		CHECK_EQUAL( hdrEnd - hdrStart, sizeof(Free) );
	
		blkStart = hdrEnd;
		blkEnd   = blkStart + free->mBlockSize; 
		
		CHECK_EQUAL( PTR_FIX(blkStart), PTR_FIX(hdrEnd) );
		CHECK_EQUAL( PTR_FIX(blkEnd), 0xc800);
		CHECK_EQUAL( free->mBlockSize, 0xc190 );

		secret = *((uint32_t *)(blkEnd - 4));
		CHECK_EQUAL(PTR_FIX(secret), PTR_FIX(hdrStart));

		CHECK_EQUAL(PTR_FIX(h->pNextFit), PTR_FIX(hdrStart));

	// ---- Part B: -------------------------------------------------------------
	
	mem.free( b );
	
	// ---- Verify B: -----------------------------------------------------------

		h = mem.getHeap();

		// Sanit check, make sure everything is heap relative for testing
		CHECK_EQUAL( PTR_FIX(h), 0 );

		// Heap Start / Heap Bottom
		CHECK_EQUAL( PTR_FIX(h->mStats.heapTopAddr), 0x30 );
		CHECK_EQUAL( PTR_FIX(h->mStats.heapBottomAddr), Mem::HEAP_SIZE);

		// Used / Free
		CHECK_EQUAL( PTR_FIX(h->pFreeHead), 0x240  );
		CHECK_EQUAL( PTR_FIX(h->pUsedHead), 0x450 );

	// ---- Heap Stats ------------------------------------------------------

		CHECK_EQUAL( h->mStats.peakNumUsed, 3 );
		CHECK_EQUAL( h->mStats.peakUsedMemory, 3*0x200);

		CHECK_EQUAL( h->mStats.currNumUsedBlocks, 2);
		CHECK_EQUAL( h->mStats.currUsedMem, 2*0x200 );
		
		CHECK_EQUAL( h->mStats.currNumFreeBlocks, 2 );
		CHECK_EQUAL( h->mStats.currFreeMem, 0xc390 );

		CHECK_EQUAL( h->mStats.sizeHeap, 0xc800 );

		CHECK_EQUAL( PTR_FIX( h->mStats.heapTopAddr), 0x30 );
		CHECK_EQUAL( PTR_FIX(h->mStats.heapBottomAddr), 0xc800 );

	// ---- Heap Hdr -------------------------------------------------------

		// HeapHdr Start
		CHECK_EQUAL( PTR_FIX( (uint32_t)h->mStats.heapTopAddr-sizeof(Heap) ), 0 );
		// HeapHdr End
		CHECK_EQUAL( PTR_FIX(h->mStats.heapTopAddr), sizeof(Heap) );


	// ---- HDR 1 -------------------------------------------

		// Check type
		used = (Used *) h->mStats.heapTopAddr;
		// Should be USED
		CHECK_EQUAL( used->mType, Block::Used );
		CHECK_EQUAL(used->pad, 0);
		// Above Free
		CHECK_EQUAL(used->mAboveBlockFree, false);
		
		hdrStart = (uint32_t)used;
		hdrEnd   = (uint32_t)used + sizeof(Used);
	
		// Hdr Start
		CHECK_EQUAL( PTR_FIX(hdrStart), 0x30  );
		// Hdr End
		CHECK_EQUAL( PTR_FIX(hdrEnd), 0x40 );
		// Prev
		CHECK_EQUAL( PTR_FIX(used->pUsedPrev), 0x450 );
		// Next
		CHECK_EQUAL( used->pUsedNext, 0x0 );
		// Hdr Size
		CHECK_EQUAL( hdrEnd - hdrStart, sizeof(Used) );
	
		blkStart = hdrEnd;
		blkEnd   = blkStart + used->mBlockSize; 
		
		CHECK_EQUAL( PTR_FIX(blkStart), PTR_FIX(hdrEnd) );
		CHECK_EQUAL( PTR_FIX(blkEnd), 0x240);
		CHECK_EQUAL( used->mBlockSize, 0x200 );
	
	// ---- HDR 2 -------------------------------------------

		// Check type
		free = (Free *) blkEnd;
		// Should be USED
		CHECK_EQUAL( free->mType, Block::Free );
		CHECK_EQUAL(free->pad, 0);
		// Above Free
		CHECK_EQUAL(free->mAboveBlockFree, false);
		
		hdrStart = (uint32_t)free;
		hdrEnd   = (uint32_t)free + sizeof(Free);
	
		// Hdr Start
		CHECK_EQUAL( PTR_FIX(hdrStart), 0x240 );
		// Hdr End
		CHECK_EQUAL( PTR_FIX(hdrEnd), 0x250 );
		// Prev
		CHECK_EQUAL( free->pFreePrev, 0x0 );
		// Next
		CHECK_EQUAL( PTR_FIX(free->pFreeNext), 0x660 );
		// Hdr Size
		CHECK_EQUAL( hdrEnd - hdrStart, sizeof(Used) );
	
		blkStart = hdrEnd;
		blkEnd   = blkStart + used->mBlockSize; 
		
		CHECK_EQUAL( PTR_FIX(blkStart), PTR_FIX(hdrEnd) );
		CHECK_EQUAL( PTR_FIX(blkEnd), 0x450 );
		CHECK_EQUAL( used->mBlockSize, 0x200 );

	// ---- Hdr 3 -------------------------------------------

		// Check type
		used = (Used *) blkEnd;
		// Should be free
		CHECK_EQUAL( used->mType, Block::Used );
		CHECK_EQUAL(used->pad, 0);
		// Above Free
		CHECK_EQUAL(used->mAboveBlockFree, true);
		
		hdrStart = (uint32_t)used;
		hdrEnd   = (uint32_t)used + sizeof(Used);
	
		// Hdr Start
		CHECK_EQUAL( PTR_FIX(hdrStart), 0x450 );
		// Hdr End
		CHECK_EQUAL( PTR_FIX(hdrEnd), 0x460 );
		// Prev
		CHECK_EQUAL( used->pUsedPrev, 0);
		// Next
		CHECK_EQUAL( PTR_FIX(used->pUsedNext), 0x30 );
		// Hdr Size
		CHECK_EQUAL( hdrEnd - hdrStart, sizeof(Free) );
	
		blkStart = hdrEnd;
		blkEnd   = blkStart + used->mBlockSize; 
		
		CHECK_EQUAL( PTR_FIX(blkStart), PTR_FIX(hdrEnd) );
		CHECK_EQUAL( PTR_FIX(blkEnd), 0x660);
		CHECK_EQUAL( used->mBlockSize, 0x200 );
	
	// ---- HDR 4 -------------------------------------------

		// Check type
		free = (Free *) blkEnd;
		// Should be USED
		CHECK_EQUAL( free->mType, Block::Free );
		CHECK_EQUAL(free->pad, 0);
		// Above Free
		CHECK_EQUAL(free->mAboveBlockFree, false);
		
		hdrStart = (uint32_t)free;
		hdrEnd   = (uint32_t)free + sizeof(Free);
	
		// Hdr Start
		CHECK_EQUAL( PTR_FIX(hdrStart), 0x660 );
		// Hdr End
		CHECK_EQUAL( PTR_FIX(hdrEnd), 0x670 );
		// Prev
		CHECK_EQUAL( PTR_FIX(free->pFreePrev), 0x240 );
		// Next
		CHECK_EQUAL( free->pFreeNext, 0x0 );
		// Hdr Size
		CHECK_EQUAL( hdrEnd - hdrStart, sizeof(Free) );
		
		blkStart = hdrEnd;
		blkEnd   = blkStart + free->mBlockSize; 

		CHECK_EQUAL( PTR_FIX(blkStart), PTR_FIX(hdrEnd) );
		CHECK_EQUAL( PTR_FIX(blkEnd), 0xc800);
		CHECK_EQUAL( free->mBlockSize, 0xc190 );

		secret = *((uint32_t *)(blkEnd - 4));
		CHECK_EQUAL(PTR_FIX(secret), PTR_FIX(hdrStart));

		CHECK_EQUAL(PTR_FIX(h->pNextFit), PTR_FIX(hdrStart));

	// ---- Part C: -------------------------------------------------------------
	
	mem.free( c );
	
	// ---- Verify C: -----------------------------------------------------------

		h = mem.getHeap();

		// Sanit check, make sure everything is heap relative for testing
		CHECK_EQUAL( PTR_FIX(h), 0 );

		// Heap Start / Heap Bottom
		CHECK_EQUAL( PTR_FIX(h->mStats.heapTopAddr), 0x30 );
		CHECK_EQUAL( PTR_FIX(h->mStats.heapBottomAddr), Mem::HEAP_SIZE);

		// Used / Free
		CHECK_EQUAL( PTR_FIX(h->pFreeHead), 0x240);
		CHECK_EQUAL( PTR_FIX(h->pUsedHead), 0x30  );

	// ---- Heap Stats ------------------------------------------------------

		CHECK_EQUAL( h->mStats.peakNumUsed, 3 );
		CHECK_EQUAL( h->mStats.peakUsedMemory, 0x600);

		CHECK_EQUAL( h->mStats.currNumUsedBlocks, 1);
		CHECK_EQUAL( h->mStats.currUsedMem, 0x200 );
		
		CHECK_EQUAL( h->mStats.currNumFreeBlocks, 1 );
		CHECK_EQUAL( h->mStats.currFreeMem, 0xc5b0 );

		CHECK_EQUAL( h->mStats.sizeHeap, 0xc800 );

		CHECK_EQUAL( PTR_FIX( h->mStats.heapTopAddr), 0x30 );
		CHECK_EQUAL( PTR_FIX(h->mStats.heapBottomAddr), 0xc800 );

		// ---- Heap Hdr -------------------------------------------------------

		// HeapHdr Start
		CHECK_EQUAL( PTR_FIX( (uint32_t)h->mStats.heapTopAddr-sizeof(Heap) ), 0 );
		// HeapHdr End
		CHECK_EQUAL( PTR_FIX(h->mStats.heapTopAddr), sizeof(Heap) );


	// ---- HDR 1 -------------------------------------------

		// Check type
		used = (Used *) h->mStats.heapTopAddr;
		CHECK_EQUAL( used->mType, Block::Used);
		CHECK_EQUAL(used->pad, 0);
		// Above Free
		CHECK_EQUAL(used->mAboveBlockFree, false);
		
		hdrStart = (uint32_t)used;
		hdrEnd   = (uint32_t)used + sizeof(Used);
	
		// Hdr Start
		CHECK_EQUAL( PTR_FIX(hdrStart), 0x30  );
		// Hdr End
		CHECK_EQUAL( PTR_FIX(hdrEnd), 0x40 );
		// Prev
		CHECK_EQUAL( used->pUsedPrev, 0x0 );
		// Next
		CHECK_EQUAL( used->pUsedNext, 0x0 );
		// Hdr Size
		CHECK_EQUAL( hdrEnd - hdrStart, sizeof(Used) );

		blkStart = hdrEnd;
		blkEnd   = blkStart + used->mBlockSize; 
		
		CHECK_EQUAL( PTR_FIX(blkStart), PTR_FIX(hdrEnd) );
		CHECK_EQUAL( PTR_FIX(blkEnd), 0x240);
		CHECK_EQUAL( used->mBlockSize, 0x200 );
	
	// ---- HDR 2 -------------------------------------------

		// Check type
		free = (Free *) blkEnd;
		// Should be free
		CHECK_EQUAL( free->mType, Block::Free );
		CHECK_EQUAL(free->pad, 0);
		// Above Free
		CHECK_EQUAL(free->mAboveBlockFree, false);
		
		hdrStart = (uint32_t)free;
		hdrEnd   = (uint32_t)free + sizeof(Free);
	
		// Hdr Start
		CHECK_EQUAL( PTR_FIX(hdrStart), 0x240 );
		// Hdr End
		CHECK_EQUAL( PTR_FIX(hdrEnd), 0x250 );
		// Prev
		CHECK_EQUAL( free->pFreePrev, 0);
		// Next
		CHECK_EQUAL( free->pFreeNext, 0 );
		// Hdr Size
		CHECK_EQUAL( hdrEnd - hdrStart, sizeof(Free) );
	
	// ---- Free Block ----------------------------------------------------

		blkStart = hdrEnd;
		blkEnd   = blkStart + free->mBlockSize; 
		
		CHECK_EQUAL( PTR_FIX(blkStart), PTR_FIX(hdrEnd) );
		CHECK_EQUAL( PTR_FIX(blkEnd), 0xc800);
		CHECK_EQUAL( free->mBlockSize, 0xc5b0 );
	
		secret = *((uint32_t *)(blkEnd - 4));
		CHECK_EQUAL(PTR_FIX(secret), PTR_FIX(hdrStart));

		CHECK_EQUAL(PTR_FIX(h->pNextFit), PTR_FIX(hdrStart));
	
	// ---- Part D: -------------------------------------------------------------
	
	mem.free( a );
	
	// ---- Verify D: -----------------------------------------------------------

		h = mem.getHeap();

		// Sanit check, make sure everything is heap relative for testing
		CHECK_EQUAL( PTR_FIX(h), 0 );

		// Heap Start / Heap Bottom
		CHECK_EQUAL( PTR_FIX(h->mStats.heapTopAddr), 0x30 );
		CHECK_EQUAL( PTR_FIX(h->mStats.heapBottomAddr), Mem::HEAP_SIZE);

		// Used / Free
		CHECK_EQUAL( PTR_FIX(h->pFreeHead), 0x30 );
		CHECK_EQUAL( h->pUsedHead, 0x0 );

	// ---- Heap Stats ------------------------------------------------------

		CHECK_EQUAL( h->mStats.peakNumUsed, 3 );
		CHECK_EQUAL( h->mStats.peakUsedMemory, 0x600);

		CHECK_EQUAL( h->mStats.currNumUsedBlocks, 0);
		CHECK_EQUAL( h->mStats.currUsedMem, 0x0 );
		
		CHECK_EQUAL( h->mStats.currNumFreeBlocks, 1 );
		CHECK_EQUAL( h->mStats.currFreeMem, 0xc7c0 );

		CHECK_EQUAL( h->mStats.sizeHeap, 0xc800 );

		CHECK_EQUAL( PTR_FIX( h->mStats.heapTopAddr), 0x30 );
		CHECK_EQUAL( PTR_FIX(h->mStats.heapBottomAddr), 0xc800 );

	// ---- Heap Hdr -------------------------------------------------------

		// HeapHdr Start
		CHECK_EQUAL( PTR_FIX( (uint32_t)h->mStats.heapTopAddr-sizeof(Heap) ), 0 );
		// HeapHdr End
		CHECK_EQUAL( PTR_FIX(h->mStats.heapTopAddr), sizeof(Heap) );


	// ---- FREE HDR 1 -------------------------------------------

		// Check type
		free = (Free *) h->mStats.heapTopAddr;
		// Should be free
		CHECK_EQUAL( free->mType, Block::Free );
		CHECK_EQUAL(free->pad, 0);
		// Above Free
		CHECK_EQUAL(free->mAboveBlockFree, false);
		
		hdrStart = (uint32_t)free;
		hdrEnd   = (uint32_t)free + sizeof(Free);
	
		// Hdr Start
		CHECK_EQUAL( PTR_FIX(hdrStart), 0x30  );
		// Hdr End
		CHECK_EQUAL( PTR_FIX(hdrEnd), 0x40 );
		// Prev
		CHECK_EQUAL( free->pFreePrev, 0x0 );
		// Next
		CHECK_EQUAL( free->pFreeNext, 0x0 );
		// Hdr Size
		CHECK_EQUAL( hdrEnd - hdrStart, sizeof(Free) );
	
	// ---- free BLOCK ----------------------------------------------------

		blkStart = hdrEnd;
		blkEnd   = blkStart + free->mBlockSize; 
		
		CHECK_EQUAL( PTR_FIX(blkStart), PTR_FIX(hdrEnd) );
		CHECK_EQUAL( PTR_FIX(blkEnd), 0xc800);
		CHECK_EQUAL( free->mBlockSize, 0xc7c0 );
	
		secret = *((uint32_t *)(blkEnd - 4));
		CHECK_EQUAL(PTR_FIX(secret), PTR_FIX(hdrStart));

		CHECK_EQUAL(PTR_FIX(h->pNextFit), PTR_FIX(hdrStart));
}  TEST_END
#endif

// ---  End of File ---------------
