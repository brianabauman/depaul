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

#include "Vect_vM_SIMD.h"
#include "Matrix_vM_SIMD.h"

#ifdef _DEBUG
	#define VM_COUNT 40000000
#else
	#define VM_COUNT 100000000
#endif

#define f_eq(A,B) (  fabs(A - B) < 0.001f)
#define V_EQ(A,B) ((f_eq(A.x,B.x) ) && ( f_eq(A.y, B.y)) && (f_eq(A.z,B.z)) && (f_eq(A.w,B.w) ))

#if VectMatrix_Test_Enable
TEST(VectMatrix, SIMD_Tests, VectMatrix_Test_Enable)
{

	// ---------------------------------------------------
	// Vect * Matrix tests
	// ---------------------------------------------------
	{
		Vect4D A(1, 2, 3, 4);
		Vect4D B(11, 12, 13, 14);
		Vect4D C(21, 22, 23, 24);

		Vect4D MV0(1, 2, 3, 4);
		Vect4D MV1(5, 6, 7, 8);
		Vect4D MV2(9, 10, 11, 12);
		Vect4D MV3(13, 14, 15, 16);

		Matrix M(MV0, MV1, MV2, MV3);

		Vect4D vout1;
		Vect4D vout2;
		Vect4D vout3;

		vout1 = A * M;
		vout2 = B * M;
		vout3 = C * M;

		Vect_vM_SIMD A_simd;
		A_simd = Vect_vM_SIMD(1, 2, 3, 4);
		Vect_vM_SIMD B_simd;
		B_simd = Vect_vM_SIMD(11, 12, 13, 14);
		Vect_vM_SIMD C_simd;
		C_simd = Vect_vM_SIMD(21, 22, 23, 24);

		Vect_vM_SIMD MV0_simd(1, 2, 3, 4);
		Vect_vM_SIMD MV1_simd(5, 6, 7, 8);
		Vect_vM_SIMD MV2_simd(9, 10, 11, 12);
		Vect_vM_SIMD MV3_simd(13, 14, 15, 16);

		CHECK(M.v0.x == 1.0f);

		Matrix_vM_SIMD M_simd;
		M_simd = Matrix_vM_SIMD(MV0_simd, MV1_simd, MV2_simd, MV3_simd);

		Vect_vM_SIMD vout1_simd;
		Vect_vM_SIMD vout2_simd;
		Vect_vM_SIMD vout3_simd;

		vout1_simd = A_simd * M_simd;
		vout2_simd = B_simd * M_simd;
		vout3_simd = C_simd * M_simd;

		//Trace::out("%ff %ff %ff %ff \n", M.m0,  M.m1,  M.m2,  M.m3);
		//Trace::out("%ff %ff %ff %ff \n", M.m4,  M.m5,  M.m6,  M.m7);
		//Trace::out("%ff %ff %ff %ff \n", M.m8,  M.m9,  M.m10, M.m11);
		//Trace::out("%ff %ff %ff %ff \n", M.m12, M.m13, M.m14, M.m15);

		CHECK(V_EQ(M.v0, M_simd.v0));
		CHECK(V_EQ(M.v1, M_simd.v1));
		CHECK(V_EQ(M.v2, M_simd.v2));
		CHECK(V_EQ(M.v3, M_simd.v3));

		Vect4D VR0(1, 2, 3, 4);
		Vect4D VR1(5, 6, 7, 8);
		Vect4D VR2(9, 10, 11, 12);
		Vect4D VR3(13, 14, 15, 16);

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

		//Trace::out("%ff %ff %ff %ff \n", vout1.x, vout1.y, vout1.z, vout1.w);
		//Trace::out("%ff %ff %ff %ff \n", vout2.x, vout2.y, vout2.z, vout2.w);
		//Trace::out("%ff %ff %ff %ff \n", vout3.x, vout3.y, vout3.z, vout3.w);

	}


	//Trace::out("\n");
	PerformanceTimer tA;
	PerformanceTimer tB;

	// --------------- Vect * Matrix ----------------------------------------------

	Vect4D A(0.010f, 0.020f, 00.30f, 0.040f);

	Vect4D VA0(0.556670f, -0.321394f, -0.766044f, 0.000000f);
	Vect4D VA1(0.696747f, 0.682796f, 0.219846f, 0.000000f);
	Vect4D VA2(0.452395f, -0.656121f, 0.604023f, 0.000000f);
	Vect4D VA3(1.000000f, 2.000000f, 3.000000f, 1.000000f);

	Matrix M(VA0, VA1, VA2, VA3);

	Vect4D v1;
	Vect4D v2;

	Trace::out("\n---------- Vect * Matrix ----------------\n");
	printf("           : Vect * Matrix\n");
	tA.Tic();

		for (int i = 0; i < VM_COUNT; i++)
		{
			v1 = A * M;
			v2 = v1 * M;
			A = v2 * M;
		}

	tA.Toc();

	// --------------- Vect * Matrix (SIMD) ----------------------------------------------

	Vect_vM_SIMD A_simd(0.010f, 0.020f, 00.30f, 0.040f);
	Vect_vM_SIMD VA0_simd(0.556670f, -0.321394f, -0.766044f, 0.000000f);
	Vect_vM_SIMD VA1_simd(0.696747f, 0.682796f, 0.219846f, 0.000000f);
	Vect_vM_SIMD VA2_simd(0.452395f, -0.656121f, 0.604023f, 0.000000f);
	Vect_vM_SIMD VA3_simd(1.000000f, 2.000000f, 3.000000f, 1.000000f);
	Matrix_vM_SIMD M_simd(VA0_simd, VA1_simd, VA2_simd, VA3_simd);

	Vect_vM_SIMD v1_simd;
	Vect_vM_SIMD v2_simd;

	printf("           : Vect * Matrix (SIMD)\n");
	tB.Tic();

		for (int i = 0; i < VM_COUNT; i++)
		{
			v1_simd = A_simd * M_simd;
			v2_simd = v1_simd * M_simd;
			A_simd = v2_simd * M_simd;
		}

	tB.Toc();

	Trace::out("  Vect * Matrix Orig: %f s   :%f %f %f %f\n", tA.TimeInSeconds(), A.x, A.y, A.z, A.w);
	Trace::out("                SIMD: %f s   :%f %f %f %f\n", tB.TimeInSeconds(), A_simd.x, A_simd.y, A_simd.z, A_simd.w);
	Trace::out("             vM SIMD: %f s \n", tB.TimeInSeconds());

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
