//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------- 

#include "Framework.h"
#include "_UnitTestConfiguration.h"

#include "AlignData.h"
#include "Align.h"

static char *pBuff = 0;

#if Print_Alignment_Test_Enable
TEST_WITH_TEARDOWN(Print, Alignment, Print_Alignment_Test_Enable)
{
	Align::Info Info;

	// Create a tmp buffer
	const unsigned int BUFF_SIZE = 256;
	pBuff = new char[BUFF_SIZE];
	assert(pBuff != 0);
	
	//-------------------------------------------
	// Structure A:
	//-------------------------------------------

	// Fill tmp buffer with 0xAA
	memset(pBuff, 0xAA, BUFF_SIZE);

	// Construct structure in the memory
	PLACEMENT_NEW_BEGIN
	#undef new

		A *pA = new(pBuff) A();

	PLACEMENT_NEW_END

	// Print it
	Trace::out("\n");
	Info = Align::PrintME(pA, sizeof(A), "data A");
	Trace::out("\n");

	CHECK(Info.NumTotalBytes == 8);
	CHECK(Info.NumBytesOfPadding == 3);

	//-------------------------------------------
	// Structure B:
	//-------------------------------------------

	memset(pBuff, 0xAA, BUFF_SIZE);

	PLACEMENT_NEW_BEGIN
	#undef new

		B *pB = new(pBuff) B();

	PLACEMENT_NEW_END

	Info = Align::PrintME(pB, sizeof(B), "data B");
	Trace::out("\n");

	CHECK(Info.NumTotalBytes == 16);
	CHECK(Info.NumBytesOfPadding == 3);

	//-------------------------------------------
	// Structure C:
	//-------------------------------------------

	memset(pBuff, 0xAA, BUFF_SIZE);

	PLACEMENT_NEW_BEGIN
	#undef new

		C *pC = new(pBuff) C();

	PLACEMENT_NEW_END

	Info = Align::PrintME(pC, sizeof(C), "data C");
	Trace::out("\n");

	CHECK(Info.NumTotalBytes == 24);
	CHECK(Info.NumBytesOfPadding == 14);

	//-------------------------------------------
	// Structure D:
	//-------------------------------------------

	memset(pBuff, 0xAA, BUFF_SIZE);
	
	PLACEMENT_NEW_BEGIN
	#undef new

		D *pD = new(pBuff) D();

	PLACEMENT_NEW_END

	Info = Align::PrintME(pD, sizeof(D), "data D");
	Trace::out("\n");

	CHECK(Info.NumTotalBytes == 64);
	CHECK(Info.NumBytesOfPadding == 27);


} TEST_END



TEST_TEARDOWN(Print, Alignment)
{
	delete[] pBuff;
}
#endif

// ---  End of File ---------------
