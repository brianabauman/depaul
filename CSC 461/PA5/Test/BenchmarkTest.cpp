//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------- 

#include "Framework.h"
#include "_UnitTestConfiguration.h"

#include "Bloated.h"
#include "Vect2D.h"

void MemoryTest();
Vect2D MathTest();

#define MEMORY_COUNT 100000
#define MATH_COUNT 20000000

#define eq(a,b) UnitUtility::AreEqual(a,b)

#if Benchmark_Timing_Test_Enable
TEST(Timing, Benchmark, Benchmark_Timing_Test_Enable)
{
	
	CHECK(true);
	
	// Create a timer objects
	PerformanceTimer t1;

	// start timer
	t1.Tic();

		Bloated *pBloated = new Bloated();

	// stop timer
	t1.Toc();

	// Create a timer objects
	PerformanceTimer t2;
	
	CHECK(pBloated != 0);

	// start timer
	t2.Tic();

		OriginalNode foundNode;
		bool foundFlag = Bloated::findKey(0x30431daa, foundNode);

	// stop timer
	t2.Toc();

	CHECK(foundFlag == true);
	delete pBloated;


	// Create a timer objects
	PerformanceTimer t3;

	// start timer
	t3.Tic();

	for (int i = 0; i < MEMORY_COUNT; i++)
	{
		MemoryTest();
	}

	// stop timer
	t3.Toc();

	// Create a timer objects
	PerformanceTimer t4;
	
	Vect2D A;

	// start timer
	t4.Tic();

	for (int i = 0; i < MATH_COUNT; i++)
	{
		Vect2D B = MathTest();
		A = A + B;
	}

	// stop timer
	t4.Toc();

	CHECK(eq(A.getX(), -33554432.000f));
	CHECK(eq(A.getY(), 134217728.000f));

	Trace::out("\n");
	Trace::out("A: %f %f  \n", A.getX(), A.getY());
	Trace::out("\n");
	Trace::out("Benchmarks: \n");
	Trace::out("    ---Bloated---\n");
	Trace::out("         Create Bloated: %f s\n", t1.TimeInSeconds());
	double convertMS = 1000.0f*t2.TimeInSeconds();
	Trace::out("                Find Key: %f ms\n", convertMS);
	Trace::out("    ---Memory---\n");
	Trace::out("           Memory Stress: %f s\n", t3.TimeInSeconds());
	Trace::out("    ---Math----\n");
	Trace::out("             Math Stress: %f s\n", t4.TimeInSeconds());
	Trace::out("\n");

} TEST_END

#endif

// ---  End of File ---------------
