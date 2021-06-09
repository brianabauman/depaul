//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------- 

#include "Framework.h"
#include "_UnitTestConfiguration.h"

#include "ReworkData.h"

#if Rework_Alignment_Test_Enable
TEST(Rework, Alignment, Rework_Alignment_Test_Enable)
{
	// Make sure you go to ReworkData.h
	// Rearrange to make size smaller (use alignment rules)
	// make Explicit padding

	DataA AA;
	DataB BB;
	DataC CC;
	DataD DD;
	DataE EE;
	Vect  VV;
	DataF FF;

	CHECK(sizeof(FF) == 32);
	CHECK(sizeof(VV) == 20);
	CHECK(sizeof(EE) == 32);
	CHECK(sizeof(DD) == 16);
	CHECK(sizeof(CC) == 16);
	CHECK(sizeof(BB) == 24);
	CHECK(sizeof(AA) == 16);

} TEST_END

#endif

// ---  End of File ---------------
