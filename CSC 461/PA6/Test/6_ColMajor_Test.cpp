//----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------

#include "Framework.h"
#include "_UnitTestConfiguration.h"
#include "PerformanceTest.h"

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

#include "Vect4D.h"
#include "Matrix.h"

#include "Vect_Col_SIMD.h"
#include "Matrix_Col_SIMD.h"

PerformanceTimer tACol;
PerformanceTimer tBCol;

#define f_eq(A,B) (  fabs(A - B) < 0.001f)
#define V_EQ(A,B) ((f_eq(A.x,B.x) ) && ( f_eq(A.y, B.y)) && (f_eq(A.z,B.z)) && (f_eq(A.w,B.w) ))

#if ColMajor_Test_Enable
TEST(ColMajor, SIMD_Tests, ColMajor_Test_Enable)
{
	// ---------------------------------------------------
	// Col major tests
	// ---------------------------------------------------
	{
		{
			Matrix Rx(Vect4D(1.000000f, 0.000000f, 0.000000f, 0.000000f),
					  Vect4D(0.000000f, -0.500000f, -0.866025f, 0.000000f),
					  Vect4D(0.000000f, 0.866025f, -0.500000f, 0.000000f),
					  Vect4D(0.000000f, 0.000000f, 0.000000f, 1.000000f));

			Matrix Ry(Vect4D(0.707107f, 0.000000f, 0.707107f, 0.000000f),
					  Vect4D(0.000000f, 1.000000f, 0.000000f, 0.000000f),
					  Vect4D(-0.707107f, 0.000000f, 0.707107f, 0.000000f),
					  Vect4D(0.000000f, 0.000000f, 0.000000f, 1.000000f));

			Matrix Rz(Vect4D(0.500000f, 0.866025f, 0.000000f, 0.000000f),
					  Vect4D(-0.866025f, 0.500000f, 0.000000f, 0.000000f),
					  Vect4D(0.000000f, 0.000000f, 1.000000f, 0.000000f),
					  Vect4D(0.000000f, 0.000000f, 0.000000f, 1.000000f));

			Matrix  T(Vect4D(1.000000f, 0.000000f, 0.000000f, 4.000000f),
					  Vect4D(0.000000f, 1.000000f, 0.000000f, 5.000000f),
					  Vect4D(0.000000f, 0.000000f, 1.000000f, 6.000000f),
					  Vect4D(0.000000f, 0.000000f, 0.000000f, 1.000000f));

			Matrix  S(Vect4D(1.000000f, 0.000000f, 0.000000f, 0.000000f),
					  Vect4D(0.000000f, 2.000000f, 0.000000f, 0.000000f),
					  Vect4D(0.000000f, 0.000000f, 0.500000f, 0.000000f),
					  Vect4D(0.200000f, 0.300000f, 0.500000f, 0.130000f));

			Vect4D  v(0.500000f, 0.600000f, 0.700000f, 0.900000f);
			Vect4D vOut;

			vOut = T * Rz * Ry * Rx * S * v;

			CHECK(S.m0 == 1.0f);

			Vect4D Ans;
			Ans = Vect4D(2.688213f, 2.448028f, 4.739550f, 0.747000f);

			CHECK(V_EQ(vOut, Ans));
		}

		{
			Matrix_Col_SIMD Rx(Vect_Col_SIMD(1.000000f, 0.000000f, 0.000000f, 0.000000f),
							   Vect_Col_SIMD(0.000000f, -0.500000f, -0.866025f, 0.000000f),
							   Vect_Col_SIMD(0.000000f, 0.866025f, -0.500000f, 0.000000f),
							   Vect_Col_SIMD(0.000000f, 0.000000f, 0.000000f, 1.000000f));

			Matrix_Col_SIMD Ry(Vect_Col_SIMD(0.707107f, 0.000000f, 0.707107f, 0.000000f),
							   Vect_Col_SIMD(0.000000f, 1.000000f, 0.000000f, 0.000000f),
							   Vect_Col_SIMD(-0.707107f, 0.000000f, 0.707107f, 0.000000f),
							   Vect_Col_SIMD(0.000000f, 0.000000f, 0.000000f, 1.000000f));

			Matrix_Col_SIMD Rz(Vect_Col_SIMD(0.500000f, 0.866025f, 0.000000f, 0.000000f),
							   Vect_Col_SIMD(-0.866025f, 0.500000f, 0.000000f, 0.000000f),
							   Vect_Col_SIMD(0.000000f, 0.000000f, 1.000000f, 0.000000f),
							   Vect_Col_SIMD(0.000000f, 0.000000f, 0.000000f, 1.000000f));

			Matrix_Col_SIMD  T(Vect_Col_SIMD(1.000000f, 0.000000f, 0.000000f, 4.000000f),
							   Vect_Col_SIMD(0.000000f, 1.000000f, 0.000000f, 5.000000f),
							   Vect_Col_SIMD(0.000000f, 0.000000f, 1.000000f, 6.000000f),
							   Vect_Col_SIMD(0.000000f, 0.000000f, 0.000000f, 1.000000f));

			Matrix_Col_SIMD  S(Vect_Col_SIMD(1.000000f, 0.000000f, 0.000000f, 0.000000f),
							   Vect_Col_SIMD(0.000000f, 2.000000f, 0.000000f, 0.000000f),
							   Vect_Col_SIMD(0.000000f, 0.000000f, 0.500000f, 0.000000f),
							   Vect_Col_SIMD(0.200000f, 0.300000f, 0.500000f, 0.130000f));

			Vect_Col_SIMD v(0.500000f, 0.600000f, 0.700000f, 0.900000f);
			Vect_Col_SIMD vOut;

			vOut = T * Rz * Ry * Rx * S * v;

			Vect_Col_SIMD Ans;
			Ans = Vect_Col_SIMD(2.688213f, 2.448028f, 4.739550f, 0.747000f);

			CHECK(V_EQ(vOut, Ans));
		}
	}


	// --------------- ColMajor ----------------------------------------------

	Trace::out("\n---------- colMajor ----------------\n");
	printf("           : colMajor\n");

	Vect4D vOut = colMajor_test();

	// --------------- colMajor SIMD ----------------------------------------------

	printf("           : colMajor SIMD\n");

	Vect_Col_SIMD  vOut_simd = colMajor_SIMD_test();

	Trace::out("       colMajor Orig: %f s    :%f %f %f %f\n", tACol.TimeInSeconds(), vOut.x, vOut.y, vOut.z, vOut.w);
	Trace::out("                SIMD: %f s    :%f %f %f %f\n", tBCol.TimeInSeconds(), vOut_simd.x, vOut_simd.y, vOut_simd.z, vOut_simd.w);
	Trace::out("       colMajor SIMD: %f s\n", tBCol.TimeInSeconds());

	if (tBCol.TimeInSeconds() < 0.3f)
	{
		Trace::out("\n");
		Trace::out("----> ERROR make sure there is no implementation in header \n");
	}
	else
	{
		Trace::out("               Ratio: %f\n", tACol.TimeInSeconds() / tBCol.TimeInSeconds());
	}


} TEST_END
#endif

// ---  End of File ---------------
