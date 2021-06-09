//----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------

#include "Framework.h"
#include "PerformanceTest.h"

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

extern PerformanceTimer tBCol;

Vect_Col_SIMD colMajor_SIMD_test()
{
	Matrix_Col_SIMD Rx(
		Vect_Col_SIMD(1.000000f,  0.000000f,  0.000000f, 0.000000f),
		Vect_Col_SIMD(0.000000f, -0.500000f,  0.866025f, 0.000000f),
		Vect_Col_SIMD(0.000000f, -0.866025f, -0.500000f, 0.000000f),
		Vect_Col_SIMD(0.000000f,  0.000000f,  0.000000f, 1.000000f));

	Matrix_Col_SIMD Ry(
		Vect_Col_SIMD(0.707107f,  0.000000f, -0.707107f, 0.000000f),
		Vect_Col_SIMD(0.000000f,  1.000000f,  0.000000f, 0.000000f),
		Vect_Col_SIMD(0.707107f,  0.000000f,  0.707107f, 0.000000f),
		Vect_Col_SIMD(0.000000f,  0.000000f,  0.000000f, 1.000000f));
								  			  
	Matrix_Col_SIMD Rz(						  
		Vect_Col_SIMD(0.500000f, -0.866025f,  0.000000f, 0.000000f),
		Vect_Col_SIMD(0.866025f,  0.500000f,  0.000000f, 0.000000f),
		Vect_Col_SIMD(0.000000f,  0.000000f,  1.000000f, 0.000000f),
		Vect_Col_SIMD(0.000000f,  0.000000f,  0.000000f, 1.000000f));
								 			  
	Matrix_Col_SIMD  T(			 			  
		Vect_Col_SIMD(1.000000f,  0.000000f,  0.000000f, 0.000000f),
		Vect_Col_SIMD(0.000000f,  1.000000f,  0.000000f, 0.000000f),
		Vect_Col_SIMD(0.000000f,  0.000000f,  1.000000f, 0.000000f),
		Vect_Col_SIMD(4.000000f,  5.000000f,  6.000000f, 1.000000f));

	Matrix_Col_SIMD  S(
		Vect_Col_SIMD(1.000000f,  0.000000f,  0.000000f, 0.200000f),
		Vect_Col_SIMD(0.000000f,  2.000000f,  0.000000f, 0.300000f),
		Vect_Col_SIMD(0.000000f,  0.000000f,  0.500000f, 0.500000f),
		Vect_Col_SIMD(0.000000f,  0.000000f,  0.000000f, 0.130000f));

	Vect_Col_SIMD  v(0.500000f, 0.600000f, 0.700000f, 0.900000f);
	Vect_Col_SIMD  vOut;

	tBCol.Tic();

	for (int i = 0; i < COL_MAJOR_COUNT; i++)
	{
		vOut = S * Rx *Ry * Rz * T * v;
	}

	tBCol.Toc();

	return vOut;
}
// ---  End of File ---------------
