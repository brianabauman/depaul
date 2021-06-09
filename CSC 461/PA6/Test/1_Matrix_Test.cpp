//----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------

#include "Framework.h"
#include "_UnitTestConfiguration.h"

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

#include "Vect4D.h"
#include "Matrix.h"

#include "Vect_M_SIMD.h"
#include "Matrix_M_SIMD.h"

#ifdef _DEBUG
#define MATRIX_COUNT 30000000
#else
#define MATRIX_COUNT 200000000
#endif

#define f_eq(A,B) (  fabs(A - B) < 0.001f)
#define V_EQ(A,B) ((f_eq(A.x,B.x) ) && ( f_eq(A.y, B.y)) && (f_eq(A.z,B.z)) && (f_eq(A.w,B.w) ))

#if Matrix_Test_Enable
TEST(Matrix, SIMD_Tests, Matrix_Test_Enable)
{
	// ---------------------------------------------------
	// Matrix * Matrix tests
	// ---------------------------------------------------
	{
		Vect4D VA0(-1.0f, -2.0f, -3.0f, -4.0f);
		Vect4D VA1(4.0f, 5.0f, 6.0f, 7.0f);
		Vect4D VA2(1.0f, -2.0f, 3.0f, 4.0f);
		Vect4D VA3(-4.0f, -3.0f, 5.0f, -1.0f);
		Vect4D VB0(-0.1f, -4.2f, -7.3f, -0.4f);
		Vect4D VB1(7.4f, 0.5f, 5.6f, 0.7f);
		Vect4D VB2(3.7f, 7.8f, 8.9f, 1.0f);
		Vect4D VB3(-0.2f, -0.4f, -7.8f, -1.2f);

		CHECK(VA0.x == -1.0f);
		CHECK(VA0.y == -2.0f);
		CHECK(VA0.z == -3.0f);
		CHECK(VA0.w == -4.0f);

		Matrix A(VA0, VA1, VA2, VA3);
		Matrix B(VB0, VB1, VB2, VB3);
		Matrix C;

		C = A * B;

		Vect_M_SIMD VA0_simd(-1.0f, -2.0f, -3.0f, -4.0f);
		Vect_M_SIMD VA1_simd(4.0f, 5.0f, 6.0f, 7.0f);
		Vect_M_SIMD VA2_simd(1.0f, -2.0f, 3.0f, 4.0f);
		Vect_M_SIMD VA3_simd(-4.0f, -3.0f, 5.0f, -1.0f);
		Vect_M_SIMD VB0_simd(-0.1f, -4.2f, -7.3f, -0.4f);
		Vect_M_SIMD VB1_simd(7.4f, 0.5f, 5.6f, 0.7f);
		Vect_M_SIMD VB2_simd(3.7f, 7.8f, 8.9f, 1.0f);
		Vect_M_SIMD VB3_simd(-0.2f, -0.4f, -7.8f, -1.2f);

		Matrix_M_SIMD A_simd(VA0_simd, VA1_simd, VA2_simd, VA3_simd);
		Matrix_M_SIMD B_simd(VB0_simd, VB1_simd, VB2_simd, VB3_simd);
		Matrix_M_SIMD C_simd;

		CHECK(VA0_simd.x == -1.0f);
		CHECK(VA0_simd.y == -2.0f);
		CHECK(VA0_simd.z == -3.0f);
		CHECK(VA0_simd.w == -4.0f);

		C_simd = A_simd * B_simd;

		CHECK(V_EQ(A.v0, A_simd.v0));
		CHECK(V_EQ(A.v1, A_simd.v1));
		CHECK(V_EQ(A.v2, A_simd.v2));
		CHECK(V_EQ(A.v3, A_simd.v3));

		CHECK(V_EQ(A.v0, VA0));
		CHECK(V_EQ(A.v1, VA1));
		CHECK(V_EQ(A.v2, VA2));
		CHECK(V_EQ(A.v3, VA3));

		CHECK(V_EQ(B.v0, B_simd.v0));
		CHECK(V_EQ(B.v1, B_simd.v1));
		CHECK(V_EQ(B.v2, B_simd.v2));
		CHECK(V_EQ(B.v3, B_simd.v3));

		CHECK(V_EQ(B.v0, VB0));
		CHECK(V_EQ(B.v1, VB1));
		CHECK(V_EQ(B.v2, VB2));
		CHECK(V_EQ(B.v3, VB3));

		CHECK(V_EQ(C.v0, C_simd.v0));
		CHECK(V_EQ(C.v1, C_simd.v1));
		CHECK(V_EQ(C.v2, C_simd.v2));
		CHECK(V_EQ(C.v3, C_simd.v3));

		CHECK(V_EQ(C.v0, C_simd.v0));
		CHECK(V_EQ(C.v1, C_simd.v1));
		CHECK(V_EQ(C.v2, C_simd.v2));
		CHECK(V_EQ(C.v3, C_simd.v3));

		Vect4D VR0(-25.000000f, -18.600000f, 0.600002f, 0.800000f);
		Vect4D VR1(57.399998f, 29.700005f, -2.400005f, -0.500000f);
		Vect4D VR2(-4.600000f, 16.600000f, -23.000002f, -3.600000f);
		Vect4D VR3(-3.100001f, 54.700001f, 64.700005f, 5.700000f);

		CHECK(V_EQ(C.v0, VR0));
		CHECK(V_EQ(C.v1, VR1));
		CHECK(V_EQ(C.v2, VR2));
		CHECK(V_EQ(C.v3, VR3));
	}

	//Trace::out("\n");
	PerformanceTimer tA;
	PerformanceTimer tB;

	// --------------- MATRIX ----------------------------------------------

	Vect4D VA0(0.556670f, -0.321394f, -0.766044f, 0.000000f);
	Vect4D VA1(0.696747f, 0.682796f, 0.219846f, 0.000000f);
	Vect4D VA2(0.452395f, -0.656121f, 0.604023f, 0.000000f);
	Vect4D VA3(1.000000f, 2.000000f, 3.000000f, 1.000000f);

	Vect4D VB0(-0.01f, -0.02f, -0.03f, -0.04f);
	Vect4D VB1(0.04f, 0.05f, 0.06f, 0.07f);
	Vect4D VB2(0.01f, 0.02f, 0.03f, 0.04f);
	Vect4D VB3(-0.04f, -0.03f, -0.02f, -0.01f);

	Matrix A(VA0, VA1, VA2, VA3);
	Matrix B(VB0, VB1, VB2, VB3);
	Matrix C = B;
	
	Trace::out("\n---------- Matrix ----------------\n");
	printf("           : Matrix\n");

	tA.Tic();

	for (int i = 0; i < MATRIX_COUNT; i++)
	{
		C = C * A;
	}

	tA.Toc();

	// --------------- Matrix SIMD ----------------------------------------------

	Vect_M_SIMD VA0_SIMD(0.556670f, -0.321394f, -0.766044f, 0.000000f);
	Vect_M_SIMD VA1_SIMD(0.696747f, 0.682796f, 0.219846f, 0.000000f);
	Vect_M_SIMD VA2_SIMD(0.452395f, -0.656121f, 0.604023f, 0.000000f);
	Vect_M_SIMD VA3_SIMD(1.000000f, 2.000000f, 3.000000f, 1.000000f);

	Vect_M_SIMD VB0_SIMD(-0.01f, -0.02f, -0.03f, -0.04f);
	Vect_M_SIMD VB1_SIMD(0.04f, 0.05f, 0.06f, 0.07f);
	Vect_M_SIMD VB2_SIMD(0.01f, 0.02f, 0.03f, 0.04f);
	Vect_M_SIMD VB3_SIMD(-0.04f, -0.03f, -0.02f, -0.01f);

	Matrix_M_SIMD A_SIMD(VA0_SIMD, VA1_SIMD, VA2_SIMD, VA3_SIMD);
	Matrix_M_SIMD B_SIMD(VB0_SIMD, VB1_SIMD, VB2_SIMD, VB3_SIMD);
	Matrix_M_SIMD C_SIMD = B_SIMD;

	printf("           : Matrix_SIMD\n");

	tB.Tic();

	for (int i = 0; i < MATRIX_COUNT; i++)
	{
		C_SIMD = C_SIMD * A_SIMD;
	}

	tB.Toc();

	Trace::out("         Matrix Orig: %2.5f s   :%f %f %f %f\n", tA.TimeInSeconds(), C.v0.x, C.v0.y, C.v0.z, C.v0.w);
	Trace::out("                                  :%f %f %f %f\n", C.v1.x, C.v1.y, C.v1.z, C.v1.w);
	Trace::out("                                  :%f %f %f %f\n", C.v2.x, C.v2.y, C.v2.z, C.v2.w);
	Trace::out("                                  :%f %f %f %f\n", C.v3.x, C.v3.y, C.v3.z, C.v3.w);

	Trace::out("                SIMD: %2.5f s   :%f %f %f %f\n", tB.TimeInSeconds(), C_SIMD.v0.x, C_SIMD.v0.y, C_SIMD.v0.z, C_SIMD.v0.w);
	Trace::out("                                  :%f %f %f %f\n", C_SIMD.v1.x, C_SIMD.v1.y, C_SIMD.v1.z, C_SIMD.v1.w);
	Trace::out("                                  :%f %f %f %f\n", C_SIMD.v2.x, C_SIMD.v2.y, C_SIMD.v2.z, C_SIMD.v2.w);
	Trace::out("                                  :%f %f %f %f\n", C_SIMD.v3.x, C_SIMD.v3.y, C_SIMD.v3.z, C_SIMD.v3.w);

	Trace::out("         Matrix SIMD: %f s \n", tB.TimeInSeconds());

	if (tB.TimeInSeconds() < 0.3f)
	{
		Trace::out("\n");
		Trace::out("----> ERROR make sure there is no implementation in header \n");
	}
	else
	{
		Trace::out("               Ratio: %f\n", tA.TimeInSeconds() / tB.TimeInSeconds());
	}

} TEST_END
#endif

// ---  End of File ---------------
