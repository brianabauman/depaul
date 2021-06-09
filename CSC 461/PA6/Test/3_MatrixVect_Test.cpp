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

#include "Vect_Mv_SIMD.h"
#include "Matrix_Mv_SIMD.h"

#ifdef _DEBUG
	#define MV_COUNT 40000000
#else
	#define MV_COUNT 100000000
#endif

#define f_eq(A,B) (  fabs(A - B) < 0.001f)
#define V_EQ(A,B) ((f_eq(A.x,B.x) ) && ( f_eq(A.y, B.y)) && (f_eq(A.z,B.z)) && (f_eq(A.w,B.w) ))

#if MatrixVect_Test_Enable
TEST(MatrixVect, SIMD_Tests, MatrixVect_Test_Enable)
{
	// ---------------------------------------------------
	// Matrix * Vect tests
	// ---------------------------------------------------
	{
		Vect4D A(1, 2, 3, 4);
		Vect4D B(11, 12, 13, 14);
		Vect4D C(21, 22, 23, 24);

		Vect4D MV0(1, 5, 9, 13);
		Vect4D MV1(2, 6, 10, 14);
		Vect4D MV2(3, 7, 11, 15);
		Vect4D MV3(4, 8, 12, 16);

		Matrix M(MV0, MV1, MV2, MV3);

		Vect4D vout1;
		Vect4D vout2;
		Vect4D vout3;

		vout1 = M * A;
		vout2 = M * B;
		vout3 = M * C;

		Vect_Mv_SIMD A_simd;
		A_simd = Vect_Mv_SIMD(1, 2, 3, 4);
		Vect_Mv_SIMD B_simd;
		B_simd = Vect_Mv_SIMD(11, 12, 13, 14);
		Vect_Mv_SIMD C_simd;
		C_simd = Vect_Mv_SIMD(21, 22, 23, 24);

		Vect_Mv_SIMD MV0_simd(1, 5, 9, 13);
		Vect_Mv_SIMD MV1_simd(2, 6, 10, 14);
		Vect_Mv_SIMD MV2_simd(3, 7, 11, 15);
		Vect_Mv_SIMD MV3_simd(4, 8, 12, 16);

		CHECK(M.v0.x == 1.0f);

		Matrix_Mv_SIMD M_simd;
		M_simd = Matrix_Mv_SIMD(MV0_simd, MV1_simd, MV2_simd, MV3_simd);

		Vect_Mv_SIMD vout1_simd;
		Vect_Mv_SIMD vout2_simd;
		Vect_Mv_SIMD vout3_simd;

		vout1_simd = M_simd * A_simd;
		vout2_simd = M_simd * B_simd;
		vout3_simd = M_simd * C_simd;

		CHECK(V_EQ(M.v0, M_simd.v0));
		CHECK(V_EQ(M.v1, M_simd.v1));
		CHECK(V_EQ(M.v2, M_simd.v2));
		CHECK(V_EQ(M.v3, M_simd.v3));


		//	//Trace::out("%ff %ff %ff %ff \n", M.m0,  M.m1,  M.m2,  M.m3);
		//	//Trace::out("%ff %ff %ff %ff \n", M.m4,  M.m5,  M.m6,  M.m7);
		//	//Trace::out("%ff %ff %ff %ff \n", M.m8,  M.m9,  M.m10, M.m11);
		//	//Trace::out("%ff %ff %ff %ff \n", M.m12, M.m13, M.m14, M.m15);

		Vect4D VR0(1, 5, 9, 13);
		Vect4D VR1(2, 6, 10, 14);
		Vect4D VR2(3, 7, 11, 15);
		Vect4D VR3(4, 8, 12, 16);

		CHECK(V_EQ(M.v0, VR0));
		CHECK(V_EQ(M.v1, VR1));
		CHECK(V_EQ(M.v2, VR2));
		CHECK(V_EQ(M.v3, VR3));

		CHECK(V_EQ(A, A_simd));
		CHECK(V_EQ(B, B_simd));
		CHECK(V_EQ(C, C_simd));

		Vect4D VA(1, 2, 3, 4);
		Vect4D VB(11,12,13,14);
		Vect4D VC(21, 22, 23, 24);

		CHECK(V_EQ(A, VA));
		CHECK(V_EQ(B, VB));
		CHECK(V_EQ(C, VC));

		CHECK(V_EQ(vout1, vout1_simd));
		CHECK(V_EQ(vout2, vout2_simd));
		CHECK(V_EQ(vout3, vout3_simd));

		Vect4D VO1(90.0f, 100.0f, 110.0f, 120.0f);
		Vect4D VO2(370.0f, 420.0f, 470.0f, 520.0f);
		Vect4D VO3(650.0f, 740.0f, 830.0f, 920.0f);

		CHECK(V_EQ(vout1, VO1));
		CHECK(V_EQ(vout2, VO2));
		CHECK(V_EQ(vout3, VO3));

		//	//Trace::out("%ff %ff %ff %ff \n", vout1.x, vout1.y, vout1.z, vout1.w);
		//	//Trace::out("%ff %ff %ff %ff \n", vout2.x, vout2.y, vout2.z, vout2.w);
		//	//Trace::out("%ff %ff %ff %ff \n", vout3.x, vout3.y, vout3.z, vout3.w);

	}


	//Trace::out("\n");
	PerformanceTimer tA;
	PerformanceTimer tB;

	// --------------- Matrix * Vector ----------------------------------------------

	Vect4D A(0.01f, 0.02f, 0.03f, 0.04f);

	Vect4D VA0(0.556670f, 0.696747f, 0.452395f, 1.000000f);
	Vect4D VA1(-0.321394f, 0.682796f, -0.656121f, 2.000000f);
	Vect4D VA2(-0.766044f, 0.219846f, 0.604023f, 3.000000f);
	Vect4D VA3(0.000000f, 0.000000f, 0.000000f, 1.000000f);

	Matrix M(VA0, VA1, VA2, VA3);

	Vect4D v1;
	Vect4D v2;

	Trace::out("\n---------- Matrix * Vect ----------------\n");
	printf("           : Matrix * Vect\n");
	tA.Tic();

		for (int i = 0; i < MV_COUNT; i++)
		{
			v1 = M * A;
			v2 = M * v1;
			A = M * v2;
		}

	tA.Toc();

	// --------------- Matrix * Vector (SIMD) ----------------------------------------------

	Vect_Mv_SIMD A_simd(0.01f, 0.02f, 0.03f, 0.04f);

	Vect_Mv_SIMD VA0_simd(0.556670f, 0.696747f, 0.452395f, 1.000000f);
	Vect_Mv_SIMD VA1_simd(-0.321394f, 0.682796f, -0.656121f, 2.000000f);
	Vect_Mv_SIMD VA2_simd(-0.766044f, 0.219846f, 0.604023f, 3.000000f);
	Vect_Mv_SIMD VA3_simd(0.000000f, 0.000000f, 0.000000f, 1.000000f);

	Matrix_Mv_SIMD M_simd(VA0_simd, VA1_simd, VA2_simd, VA3_simd);

	Vect_Mv_SIMD v1_simd;
	Vect_Mv_SIMD v2_simd;


	printf("           : Matrix * Vect (SIMD)\n");
	tB.Tic();

		for (int i = 0; i < MV_COUNT; i++)
		{
			v1_simd = M_simd * A_simd;
			v2_simd = M_simd * v1_simd;
			A_simd = M_simd * v2_simd;
		}

	tB.Toc();

	Trace::out("  Matrix * Vect Orig: %f s   :%f %f %f %f\n", tA.TimeInSeconds(), A.x, A.y, A.z, A.w);
	Trace::out("                SIMD: %f s   :%f %f %f %f\n", tB.TimeInSeconds(), A_simd.x, A_simd.y, A_simd.z, A_simd.w);
	Trace::out("             Mv SIMD: %f s\n", tB.TimeInSeconds());

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
