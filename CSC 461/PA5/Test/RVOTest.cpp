//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------- 

#include "Framework.h"
#include "_UnitTestConfiguration.h"

#include "RVO.h"
#include "No_RVO.h"

#if NDEBUG
#define COUNT 10000000
#else
#define COUNT 1500000
#endif


#define eq(a,b) UnitUtility::AreEqual(a,b)

Vect2D_No_RVO NoRVOStress(void)
{
	float v1 = 2.0f;
	float v2 = 3.0f;
	float v3 = 7.0f;
	float v4 = -5.7f;
	float v5 = 1.0f/109.0f;
	float v6 = 4.0f;
	float v7 = 22.23f;

	Vect2D_No_RVO A;
	Vect2D_No_RVO B(v1, v2);
	Vect2D_No_RVO C(v3, v4);
	Vect2D_No_RVO D(v5, v6);

	Vect2D_No_RVO sum;

	sum = A + B + C + D;

	A = B + C;
	A = A - B*5 - C * 2;
	A = A * v4;
	A = A / v5 + sum;

	A = B + C;
	A = A + B*7 - C * 3;
	A = A * v4;
	A = A / v5;

	A = B + C;
	A = A - B*9 - D *1.2f;
	A = A * v4;
	A = A / (v7 * 100.0f);

	return A;
}

Vect2D RVOStress(void)
{
	float v1 = 2.0f;
	float v2 = 3.0f;
	float v3 = 7.0f;
	float v4 = -5.7f;
	float v5 = 1.0f / 109.0f;
	float v6 = 4.0f;
	float v7 = 22.23f;

	Vect2D A;
	Vect2D B(v1, v2);
	Vect2D C(v3, v4);
	Vect2D D(v5, v6);

	Vect2D sum;

	sum = A + B + C + D;

	A = B + C;
	A = A - B * 5 - C * 2;
	A = A * v4;
	A = A / v5 + sum;

	A = B + C;
	A = A + B * 7 - C * 3;
	A = A * v4;
	A = A / v5;

	A = B + C;
	A = A - B * 9 - D *1.2f;
	A = A * v4;
	A = A / (v7 * 100.0f);

	return A;
}

#if RVO_Timing_Test_Enable 
TEST(Timing, RVO, RVO_Timing_Test_Enable)
{
	CHECK(true);
	
	// Create a timer objects
	PerformanceTimer t1;

	Vect2D A;
	// start timer
	t1.Tic();

	for (int i = 0; i < COUNT; i++)
	{
		Vect2D B = RVOStress();
		A = A + B;
	}

	// stop timer
	t1.Toc();

#ifdef _DEBUG
	CHECK(eq(A.getX(), 35017.105f));
	CHECK(eq(A.getY(), 131204.656f));
#else
	CHECK(eq(A.getX(), 199847.906f));
	CHECK(eq(A.getY(), 793482.438f));
#endif

	// Create a timer objects
	PerformanceTimer t2;

	Vect2D_No_RVO AA;

	// start timer
	t2.Tic();

	for (int i = 0; i < COUNT; i++)
	{
		Vect2D_No_RVO BB = NoRVOStress();
		AA = AA + BB;
	}

	// stop timer
	t2.Toc();

#ifdef _DEBUG
	CHECK(eq(AA.getX(), 35017.105f));
	CHECK(eq(AA.getY(), 131204.656f));
#else
	CHECK(eq(AA.getX(), 199847.906f));
	CHECK(eq(AA.getY(), 793482.438f));
#endif

	Trace::out("\n");
	Trace::out(" A: %f %f \n", A.getX(), A.getY() );
	Trace::out("AA: %f %f \n", AA.getX(), AA.getY());
	Trace::out("\n");
	Trace::out("   No_RVO: %f s\n", t2.TimeInSeconds());
	Trace::out("using_RVO: %f s\n", t1.TimeInSeconds());
	double ratio = (t2.TimeInSeconds() / t1.TimeInSeconds());
	Trace::out("    Ratio: %f \n", (double)ratio);

} TEST_END
#endif

// ---  End of File ---------------
