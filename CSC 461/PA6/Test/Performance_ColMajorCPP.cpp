//----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------

#include "Framework.h"
#include "PerformanceTest.h"

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

extern PerformanceTimer tACol;

Vect4D colMajor_test()
{
	Matrix Rx(Vect4D(1.000000f,  0.000000f,  0.000000f, 0.000000f),
			  Vect4D(0.000000f, -0.500000f,  0.866025f, 0.000000f),
			  Vect4D(0.000000f, -0.866025f, -0.500000f, 0.000000f),
			  Vect4D(0.000000f,  0.000000f,  0.000000f, 1.000000f));

	Matrix Ry(Vect4D(0.707107f,  0.000000f, -0.707107f, 0.000000f),
			  Vect4D(0.000000f,  1.000000f,  0.000000f, 0.000000f),
			  Vect4D(0.707107f,  0.000000f,  0.707107f, 0.000000f),
			  Vect4D(0.000000f,  0.000000f,  0.000000f, 1.000000f));

	Matrix Rz(Vect4D(0.500000f, -0.866025f,  0.000000f, 0.000000f),
			  Vect4D(0.866025f,  0.500000f,  0.000000f, 0.000000f),
			  Vect4D(0.000000f,  0.000000f,  1.000000f, 0.000000f),
			  Vect4D(0.000000f,  0.000000f,  0.000000f, 1.000000f));
										     
	Matrix  T(Vect4D(1.000000f,  0.000000f,  0.000000f, 0.000000f),
			  Vect4D(0.000000f,  1.000000f,  0.000000f, 0.000000f),
			  Vect4D(0.000000f,  0.000000f,  1.000000f, 0.000000f),
			  Vect4D(4.000000f,  5.000000f,  6.000000f, 1.000000f));
								 		     
	Matrix  S(Vect4D(1.000000f,  0.000000f,  0.000000f, 0.200000f),
			  Vect4D(0.000000f,  2.000000f,  0.000000f, 0.300000f),
			  Vect4D(0.000000f,  0.000000f,  0.500000f, 0.500000f),
			  Vect4D(0.000000f,  0.000000f,  0.000000f, 0.130000f));

	Vect4D  v(0.500000f, 0.600000f, 0.700000f, 0.900000f);
	Vect4D  vOut;

	tACol.Tic();
	
	for (int i = 0; i < COL_MAJOR_COUNT; i++)
	{
		vOut = S * Rx *Ry * Rz * T * v;
	}

	tACol.Toc();

	return vOut;
}

// ---  End of File ---------------
