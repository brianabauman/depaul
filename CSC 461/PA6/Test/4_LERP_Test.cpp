//----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------

#include "Framework.h"
#include "_UnitTestConfiguration.h"

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

#include "Vect4D.h"

#include "Vect_LERP_SIMD.h"

#ifdef _DEBUG
	#define LERP_COUNT 2000000
#else
	#define LERP_COUNT 5000000
#endif

#define f_eq(A,B) (  fabs(A - B) < 0.001f)
#define V_EQ(A,B) ((f_eq(A.x,B.x) ) && ( f_eq(A.y, B.y)) && (f_eq(A.z,B.z)) && (f_eq(A.w,B.w) ))

#if LERP_Test_Enable
TEST(LERP, SIMD_Tests, LERP_Test_Enable)
{
	// ---------------------------------------------------
	// LERP tests
	// ---------------------------------------------------
	{
		Vect4D va(0.0f, 0.0f, 0.0f, 0.0f);
		Vect4D vb(10.0f, 20.0f, 30.0f, 40.0f);
		Vect4D vout;

		vout = Vect4D::Lerp(va, vb, 0.0f);

		CHECK((vout.x == 0.0f));
		CHECK((vout.y == 0.0f));
		CHECK((vout.z == 0.0f));
		CHECK((vout.w == 0.0f));

		Vect4D vc(0.0f, 0.0f, 0.0f, 0.0f);
		Vect4D vd(10.0f, 20.0f, 30.0f, 40.0f);

		vout = Vect4D::Lerp(vc, vd, 0.5f);

		CHECK((vout.x == 5.0f));
		CHECK((vout.y == 10.0f));
		CHECK((vout.z == 15.0f));
		CHECK((vout.w == 20.0f));

		Vect4D ve(0.0f, 0.0f, 0.0f, 0.0f);
		Vect4D vf(10.0f, 20.0f, 30.0f, 40.0f);

		vout = Vect4D::Lerp(ve, vf, 0.25f);

		CHECK((vout.x == 2.5f));
		CHECK((vout.y == 5.0f));
		CHECK((vout.z == 7.50f));
		CHECK((vout.w == 10.0f));

		Vect4D vg(0.0f, 0.0f, 0.0f, 0.0f);
		Vect4D vh(10.0f, 20.0f, 30.0f, 40.0f);

		vout = Vect4D::Lerp(vg, vh, 1.0f);

		CHECK((vout.x == 10.0f));
		CHECK((vout.y == 20.0f));
		CHECK((vout.z == 30.0f));
		CHECK((vout.w == 40.0f));

		Vect_LERP_SIMD va_simd(0.0f, 0.0f, 0.0f, 0.0f);
		Vect_LERP_SIMD vb_simd(10.0f, 20.0f, 30.0f, 40.0f);
		Vect_LERP_SIMD vout_simd;

		vout_simd = Vect_LERP_SIMD::Lerp(va_simd, vb_simd, 0.0f);

		CHECK((vout_simd.x == 0.0f));
		CHECK((vout_simd.y == 0.0f));
		CHECK((vout_simd.z == 0.0f));
		CHECK((vout_simd.w == 0.0f));

		Vect_LERP_SIMD vc_simd(0.0f, 0.0f, 0.0f, 0.0f);
		Vect_LERP_SIMD vd_simd(10.0f, 20.0f, 30.0f, 40.0f);

		vout_simd = Vect_LERP_SIMD::Lerp(vc_simd, vd_simd, 0.5f);

		CHECK((vout_simd.x == 5.0f));
		CHECK((vout_simd.y == 10.0f));
		CHECK((vout_simd.z == 15.0f));
		CHECK((vout_simd.w == 20.0f));

		Vect_LERP_SIMD ve_simd(0.0f, 0.0f, 0.0f, 0.0f);
		Vect_LERP_SIMD vf_simd(10.0f, 20.0f, 30.0f, 40.0f);

		vout_simd = Vect_LERP_SIMD::Lerp(ve_simd, vf_simd, 0.25f);

		CHECK((vout_simd.x == 2.5f));
		CHECK((vout_simd.y == 5.0f));
		CHECK((vout_simd.z == 7.50f));
		CHECK((vout_simd.w == 10.0f));

		Vect_LERP_SIMD vg_simd(0.0f, 0.0f, 0.0f, 0.0f);
		Vect_LERP_SIMD vh_simd(10.0f, 20.0f, 30.0f, 40.0f);

		vout_simd = Vect_LERP_SIMD::Lerp(vg_simd, vh_simd, 1.0f);

		CHECK((vout_simd.x == 10.0f));
		CHECK((vout_simd.y == 20.0f));
		CHECK((vout_simd.z == 30.0f));
		CHECK((vout_simd.w == 40.0f));

		Vect_LERP_SIMD vOut;
		Vect_LERP_SIMD A(1.00f, 2.0f, 3.0f, 4.0f);
		Vect_LERP_SIMD B(21.00f, 12.0f, 23.0f, 40.0f);

		vOut = Vect_LERP_SIMD::Lerp(A, B, 0.5f);

		CHECK((vOut.x == 11.0f));
		CHECK((vOut.y == 7.0f));
		CHECK((vOut.z == 13.0f));
		CHECK((vOut.w == 22.0f));

		vOut = Vect_LERP_SIMD::Lerp(A, vOut, 0.5f);

		CHECK((vOut.x == 6.0f));
		CHECK((vOut.y == 4.5f));
		CHECK((vOut.z == 8.0f));
		CHECK((vOut.w == 13.0f));

		Vect_LERP_SIMD vOut_SIMD;
		Vect_LERP_SIMD A_SIMD(1.00f, 2.0f, 3.0f, 4.0f);
		Vect_LERP_SIMD B_SIMD(21.00f, 12.0f, 23.0f, 40.0f);

		vOut_SIMD = Vect_LERP_SIMD::Lerp(A_SIMD, B_SIMD, 0.5f);

		CHECK((vOut_SIMD.x == 11.0f));
		CHECK((vOut_SIMD.y == 7.0f));
		CHECK((vOut_SIMD.z == 13.0f));
		CHECK((vOut_SIMD.w == 22.0f))

		vOut_SIMD = Vect_LERP_SIMD::Lerp(A_SIMD, vOut_SIMD, 0.5f);

		CHECK((vOut_SIMD.x == 6.0f));
		CHECK((vOut_SIMD.y == 4.5f));
		CHECK((vOut_SIMD.z == 8.0f));
		CHECK((vOut_SIMD.w == 13.0f));
	}


	//Trace::out("\n");
	PerformanceTimer tA;
	PerformanceTimer tB;

	// --------------- LERP ----------------------------------------------

	Vect4D vOut;
	Vect4D A(1.00f, 2.0f, 3.0f, 4.0f);
	Vect4D B(21.00f, 12.0f, 23.0f, 40.0f);
	Vect4D C(13.00f, 24.0f, 33.0f, 40.0f);
	Vect4D D(0.50f, 22.0f, 43.0f, 40.0f);
	Vect4D E(1.30f, 23.0f, 35.0f, 40.0f);
	Vect4D F(15.00f, 72.0f, 35.0f, 40.0f);
	Vect4D G(21.00f, 92.0f, 33.0f, 40.0f);

	vOut = Vect4D::Lerp(A, B, 0.65f);

	Trace::out("\n---------- LERP ----------------\n");
	printf("           : LERP\n");

	tA.Tic();

	for (int i = 0; i < LERP_COUNT; i++)
	{
		vOut = Vect4D::Lerp(A, vOut, 0.65f);
		vOut = Vect4D::Lerp(B, vOut, 0.15f);
		vOut = Vect4D::Lerp(C, vOut, 0.25f);
		vOut = Vect4D::Lerp(D, vOut, 0.35f);
		vOut = Vect4D::Lerp(E, vOut, 0.45f);
		vOut = Vect4D::Lerp(F, vOut, 0.55f);
		vOut = Vect4D::Lerp(G, vOut, 0.65f);
		vOut = Vect4D::Lerp(A, vOut, 0.75f);
		vOut = Vect4D::Lerp(A, vOut, 0.85f);
		vOut = Vect4D::Lerp(B, vOut, 0.95f);
		vOut = Vect4D::Lerp(C, vOut, 0.05f);
		vOut = Vect4D::Lerp(D, vOut, 0.15f);
		vOut = Vect4D::Lerp(E, vOut, 0.25f);
		vOut = Vect4D::Lerp(F, vOut, 0.35f);
		vOut = Vect4D::Lerp(G, vOut, 0.45f);
		vOut = Vect4D::Lerp(A, vOut, 0.65f);
		vOut = Vect4D::Lerp(B, vOut, 0.15f);
		vOut = Vect4D::Lerp(C, vOut, 0.25f);
		vOut = Vect4D::Lerp(D, vOut, 0.35f);
		vOut = Vect4D::Lerp(E, vOut, 0.45f);
		vOut = Vect4D::Lerp(F, vOut, 0.55f);
		vOut = Vect4D::Lerp(G, vOut, 0.65f);
		vOut = Vect4D::Lerp(A, vOut, 0.75f);
		vOut = Vect4D::Lerp(A, vOut, 0.85f);
		vOut = Vect4D::Lerp(B, vOut, 0.95f);
		vOut = Vect4D::Lerp(C, vOut, 0.05f);
		vOut = Vect4D::Lerp(D, vOut, 0.15f);
		vOut = Vect4D::Lerp(E, vOut, 0.25f);
		vOut = Vect4D::Lerp(F, vOut, 0.35f);
		vOut = Vect4D::Lerp(G, vOut, 0.45f);
		vOut = Vect4D::Lerp(A, vOut, 0.65f);
		vOut = Vect4D::Lerp(B, vOut, 0.15f);
		vOut = Vect4D::Lerp(C, vOut, 0.25f);
		vOut = Vect4D::Lerp(D, vOut, 0.35f);
		vOut = Vect4D::Lerp(E, vOut, 0.45f);
		vOut = Vect4D::Lerp(F, vOut, 0.55f);
		vOut = Vect4D::Lerp(G, vOut, 0.65f);
		vOut = Vect4D::Lerp(A, vOut, 0.75f);
		vOut = Vect4D::Lerp(A, vOut, 0.85f);
		vOut = Vect4D::Lerp(B, vOut, 0.95f);
		vOut = Vect4D::Lerp(C, vOut, 0.05f);
		vOut = Vect4D::Lerp(D, vOut, 0.15f);
		vOut = Vect4D::Lerp(E, vOut, 0.25f);
		vOut = Vect4D::Lerp(F, vOut, 0.35f);
		vOut = Vect4D::Lerp(G, vOut, 0.45f);
	}

	tA.Toc();

	// --------------- LERP SIMD ----------------------------------------------

	Vect_LERP_SIMD vOut_simd;
	Vect_LERP_SIMD A_simd(1.00f, 2.0f, 3.0f, 4.0f);
	Vect_LERP_SIMD B_simd(21.00f, 12.0f, 23.0f, 40.0f);
	Vect_LERP_SIMD C_simd(13.00f, 24.0f, 33.0f, 40.0f);
	Vect_LERP_SIMD D_simd(0.50f, 22.0f, 43.0f, 40.0f);
	Vect_LERP_SIMD E_simd(1.30f, 23.0f, 35.0f, 40.0f);
	Vect_LERP_SIMD F_simd(15.00f, 72.0f, 35.0f, 40.0f);
	Vect_LERP_SIMD G_simd(21.00f, 92.0f, 33.0f, 40.0f);

	vOut_simd = Vect_LERP_SIMD::Lerp(A_simd, B_simd, 0.65f);

	printf("           : LERP SIMD\n");

	tB.Tic();

	for (int i = 0; i < LERP_COUNT; i++)
	{
		vOut_simd = Vect_LERP_SIMD::Lerp(A_simd, vOut_simd, 0.65f);
		vOut_simd = Vect_LERP_SIMD::Lerp(B_simd, vOut_simd, 0.15f);
		vOut_simd = Vect_LERP_SIMD::Lerp(C_simd, vOut_simd, 0.25f);
		vOut_simd = Vect_LERP_SIMD::Lerp(D_simd, vOut_simd, 0.35f);
		vOut_simd = Vect_LERP_SIMD::Lerp(E_simd, vOut_simd, 0.45f);
		vOut_simd = Vect_LERP_SIMD::Lerp(F_simd, vOut_simd, 0.55f);
		vOut_simd = Vect_LERP_SIMD::Lerp(G_simd, vOut_simd, 0.65f);
		vOut_simd = Vect_LERP_SIMD::Lerp(A_simd, vOut_simd, 0.75f);
		vOut_simd = Vect_LERP_SIMD::Lerp(A_simd, vOut_simd, 0.85f);
		vOut_simd = Vect_LERP_SIMD::Lerp(B_simd, vOut_simd, 0.95f);
		vOut_simd = Vect_LERP_SIMD::Lerp(C_simd, vOut_simd, 0.05f);
		vOut_simd = Vect_LERP_SIMD::Lerp(D_simd, vOut_simd, 0.15f);
		vOut_simd = Vect_LERP_SIMD::Lerp(E_simd, vOut_simd, 0.25f);
		vOut_simd = Vect_LERP_SIMD::Lerp(F_simd, vOut_simd, 0.35f);
		vOut_simd = Vect_LERP_SIMD::Lerp(G_simd, vOut_simd, 0.45f);
		vOut_simd = Vect_LERP_SIMD::Lerp(A_simd, vOut_simd, 0.65f);
		vOut_simd = Vect_LERP_SIMD::Lerp(B_simd, vOut_simd, 0.15f);
		vOut_simd = Vect_LERP_SIMD::Lerp(C_simd, vOut_simd, 0.25f);
		vOut_simd = Vect_LERP_SIMD::Lerp(D_simd, vOut_simd, 0.35f);
		vOut_simd = Vect_LERP_SIMD::Lerp(E_simd, vOut_simd, 0.45f);
		vOut_simd = Vect_LERP_SIMD::Lerp(F_simd, vOut_simd, 0.55f);
		vOut_simd = Vect_LERP_SIMD::Lerp(G_simd, vOut_simd, 0.65f);
		vOut_simd = Vect_LERP_SIMD::Lerp(A_simd, vOut_simd, 0.75f);
		vOut_simd = Vect_LERP_SIMD::Lerp(A_simd, vOut_simd, 0.85f);
		vOut_simd = Vect_LERP_SIMD::Lerp(B_simd, vOut_simd, 0.95f);
		vOut_simd = Vect_LERP_SIMD::Lerp(C_simd, vOut_simd, 0.05f);
		vOut_simd = Vect_LERP_SIMD::Lerp(D_simd, vOut_simd, 0.15f);
		vOut_simd = Vect_LERP_SIMD::Lerp(E_simd, vOut_simd, 0.25f);
		vOut_simd = Vect_LERP_SIMD::Lerp(F_simd, vOut_simd, 0.35f);
		vOut_simd = Vect_LERP_SIMD::Lerp(G_simd, vOut_simd, 0.45f);
		vOut_simd = Vect_LERP_SIMD::Lerp(A_simd, vOut_simd, 0.65f);
		vOut_simd = Vect_LERP_SIMD::Lerp(B_simd, vOut_simd, 0.15f);
		vOut_simd = Vect_LERP_SIMD::Lerp(C_simd, vOut_simd, 0.25f);
		vOut_simd = Vect_LERP_SIMD::Lerp(D_simd, vOut_simd, 0.35f);
		vOut_simd = Vect_LERP_SIMD::Lerp(E_simd, vOut_simd, 0.45f);
		vOut_simd = Vect_LERP_SIMD::Lerp(F_simd, vOut_simd, 0.55f);
		vOut_simd = Vect_LERP_SIMD::Lerp(G_simd, vOut_simd, 0.65f);
		vOut_simd = Vect_LERP_SIMD::Lerp(A_simd, vOut_simd, 0.75f);
		vOut_simd = Vect_LERP_SIMD::Lerp(A_simd, vOut_simd, 0.85f);
		vOut_simd = Vect_LERP_SIMD::Lerp(B_simd, vOut_simd, 0.95f);
		vOut_simd = Vect_LERP_SIMD::Lerp(C_simd, vOut_simd, 0.05f);
		vOut_simd = Vect_LERP_SIMD::Lerp(D_simd, vOut_simd, 0.15f);
		vOut_simd = Vect_LERP_SIMD::Lerp(E_simd, vOut_simd, 0.25f);
		vOut_simd = Vect_LERP_SIMD::Lerp(F_simd, vOut_simd, 0.35f);
		vOut_simd = Vect_LERP_SIMD::Lerp(G_simd, vOut_simd, 0.45f);
	}

	tB.Toc();

	Trace::out("           LERP Orig: %f s   :%f %f %f %f\n", tA.TimeInSeconds(), vOut.x, vOut.y, vOut.z, vOut.w);
	Trace::out("                SIMD: %f s   :%f %f %f %f\n", tB.TimeInSeconds(), vOut_simd.x, vOut_simd.y, vOut_simd.z, vOut_simd.w);
	Trace::out("           LERP SIMD: %f s  \n", tB.TimeInSeconds());

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
