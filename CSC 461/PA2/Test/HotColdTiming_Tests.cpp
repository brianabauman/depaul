//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------- 

#include "Framework.h"
#include "_UnitTestConfiguration.h"

#include "Node.h"
#include "Bloated.h"
#include "HotCold.h"

static HotCold *pHotCold = 0;
static Bloated *pBloated = 0;

#if Timing_HotCold_Test_Enable
TEST_WITH_TEARDOWN(Timing, HotCold, Timing_HotCold_Test_Enable)
{
	//-----------------------------------------------------------------------------
	// Create Bloated
	//-----------------------------------------------------------------------------

	// Create a timer objects
	PerformanceTimer t1;

	// start timer
	t1.Tic();

		//-----------------------------------------------------------------------------
		// It initializes the data if a very bloated way do not modify it!
		//-----------------------------------------------------------------------------
		pBloated = new Bloated(300000);

	// stop timer
	t1.Toc();
	CHECK(pBloated != 0);

	//-----------------------------------------------------------------------------
	// Find a specific Key
	//-----------------------------------------------------------------------------

	Node *pFoundNode;
	bool foundFlag;

	// Create a timer objects
	PerformanceTimer t2;

	// start timer
	t2.Tic();

		// find a specific key
		foundFlag = pBloated->FindKey(0x104C37BE, pFoundNode);

	// stop timer
	t2.Toc();
	CHECK(foundFlag == true);

	//-----------------------------------------------------------------------------
	// Verify
	//-----------------------------------------------------------------------------

		CHECK(pFoundNode->x == 16949.7109f);
		CHECK(pFoundNode->y == 17853.2305f);
		CHECK(pFoundNode->z == 26587.0527f);

		CHECK(pFoundNode->A.x == 6247.274902f);
		CHECK(pFoundNode->A.y == 25425.746094f);
		CHECK(pFoundNode->A.z == 23551.759766f);

		CHECK(pFoundNode->B.x == 14479.426758f);
		CHECK(pFoundNode->B.y == 17492.029297f);
		CHECK(pFoundNode->B.z == 19202.816406f);

		CHECK(pFoundNode->C.x == 27231.945313f);
		CHECK(pFoundNode->C.y == 26241.130859f);
		CHECK(pFoundNode->C.z == 15572.863281f);

		CHECK(pFoundNode->MA.m00 == 21634.212891f);
		CHECK(pFoundNode->MA.m01 == 24311.041016f);
		CHECK(pFoundNode->MA.m02 == 20878.404297f);
		CHECK(pFoundNode->MA.m03 == 27057.738281f);
		CHECK(pFoundNode->MA.m10 == 30450.693359f);
		CHECK(pFoundNode->MA.m11 == 17123.791016f);
		CHECK(pFoundNode->MA.m12 == 27832.166016f);
		CHECK(pFoundNode->MA.m13 == 32506.955078f);
		CHECK(pFoundNode->MA.m20 == 30677.302734f);
		CHECK(pFoundNode->MA.m21 == 196.778442f);
		CHECK(pFoundNode->MA.m22 == 14500.138672f);
		CHECK(pFoundNode->MA.m23 == 19330.308594f);
		CHECK(pFoundNode->MA.m30 == 11667.819336f);
		CHECK(pFoundNode->MA.m31 == 15166.396484f);
		CHECK(pFoundNode->MA.m32 == 19997.603516f);
		CHECK(pFoundNode->MA.m33 == 5982.881348f);

		CHECK(pFoundNode->MB.m00 == 20984.812500f);
		CHECK(pFoundNode->MB.m01 == 13178.451172f);
		CHECK(pFoundNode->MB.m02 == 30863.783203f);
		CHECK(pFoundNode->MB.m03 == 4715.444336f);
		CHECK(pFoundNode->MB.m10 == 25778.341797f);
		CHECK(pFoundNode->MB.m11 == 16292.379883f);
		CHECK(pFoundNode->MB.m12 == 24716.837891f);
		CHECK(pFoundNode->MB.m13 == 21190.500000f);
		CHECK(pFoundNode->MB.m20 == 7638.266113f);
		CHECK(pFoundNode->MB.m21 == 20846.099609f);
		CHECK(pFoundNode->MB.m22 == 17995.501953f);
		CHECK(pFoundNode->MB.m23 == 25425.935547f);
		CHECK(pFoundNode->MB.m30 == 28764.193359f);
		CHECK(pFoundNode->MB.m31 == 3212.480225f);
		CHECK(pFoundNode->MB.m32 == 19492.333984f);
		CHECK(pFoundNode->MB.m33 == 25141.316406f);

		CHECK(pFoundNode->MC.m00 == 7326.042480f);
		CHECK(pFoundNode->MC.m01 == 27958.443359f);
		CHECK(pFoundNode->MC.m02 == 20758.595703f);
		CHECK(pFoundNode->MC.m03 == 12123.787109f);
		CHECK(pFoundNode->MC.m10 == 21213.230469f);
		CHECK(pFoundNode->MC.m11 == 32425.681641f);
		CHECK(pFoundNode->MC.m12 == 23361.755859f);
		CHECK(pFoundNode->MC.m13 == 10994.614258f);
		CHECK(pFoundNode->MC.m20 == 26044.498047f);
		CHECK(pFoundNode->MC.m21 == 8614.010742f);
		CHECK(pFoundNode->MC.m22 == 4716.622070f);
		CHECK(pFoundNode->MC.m23 == 1004.341858f);
		CHECK(pFoundNode->MC.m30 == 3267.344971f);
		CHECK(pFoundNode->MC.m31 == 25329.337891f);
		CHECK(pFoundNode->MC.m32 == 19072.089844f);
		CHECK(pFoundNode->MC.m33 == 5760.577637f);

		CHECK(pFoundNode->MD.m00 == 14046.095703f);
		CHECK(pFoundNode->MD.m01 == 25044.259766f);
		CHECK(pFoundNode->MD.m02 == 7691.525391f);
		CHECK(pFoundNode->MD.m03 == 23210.404297f);
		CHECK(pFoundNode->MD.m10 == 27867.595703f);
		CHECK(pFoundNode->MD.m11 == 18074.292969f);
		CHECK(pFoundNode->MD.m12 == 6334.767578f);
		CHECK(pFoundNode->MD.m13 == 25254.414063f);
		CHECK(pFoundNode->MD.m20 == 17392.523438f);
		CHECK(pFoundNode->MD.m21 == 18708.707031f);
		CHECK(pFoundNode->MD.m22 == 29167.757813f);
		CHECK(pFoundNode->MD.m23 == 27001.369141f);
		CHECK(pFoundNode->MD.m30 == 24626.333984f);
		CHECK(pFoundNode->MD.m31 == 18199.013672f);
		CHECK(pFoundNode->MD.m32 == 22296.794922f);
		CHECK(pFoundNode->MD.m33 == 29032.484375f);

		CHECK((unsigned char)pFoundNode->name[0x00] == (unsigned char)0x27);
		CHECK((unsigned char)pFoundNode->name[0x01] == (unsigned char)0xc6);
		CHECK((unsigned char)pFoundNode->name[0x02] == (unsigned char)0x67);
		CHECK((unsigned char)pFoundNode->name[0x03] == (unsigned char)0x8f);
		CHECK((unsigned char)pFoundNode->name[0x04] == (unsigned char)0x9d);
		CHECK((unsigned char)pFoundNode->name[0x05] == (unsigned char)0xb3);
		CHECK((unsigned char)pFoundNode->name[0x06] == (unsigned char)0xf2);
		CHECK((unsigned char)pFoundNode->name[0x07] == (unsigned char)0xae);
		CHECK((unsigned char)pFoundNode->name[0x08] == (unsigned char)0x58);
		CHECK((unsigned char)pFoundNode->name[0x09] == (unsigned char)0xa5);
		CHECK((unsigned char)pFoundNode->name[0x0a] == (unsigned char)0x81);
		CHECK((unsigned char)pFoundNode->name[0x0b] == (unsigned char)0x82);
		CHECK((unsigned char)pFoundNode->name[0x0c] == (unsigned char)0x65);
		CHECK((unsigned char)pFoundNode->name[0x0d] == (unsigned char)0x63);
		CHECK((unsigned char)pFoundNode->name[0x0e] == (unsigned char)0x26);
		CHECK((unsigned char)pFoundNode->name[0x0f] == (unsigned char)0xda);
		CHECK((unsigned char)pFoundNode->name[0x10] == (unsigned char)0xe9);
		CHECK((unsigned char)pFoundNode->name[0x11] == (unsigned char)0x79);
		CHECK((unsigned char)pFoundNode->name[0x12] == (unsigned char)0x83);
		CHECK((unsigned char)pFoundNode->name[0x13] == (unsigned char)0xb2);
		CHECK((unsigned char)pFoundNode->name[0x14] == (unsigned char)0x1b);
		CHECK((unsigned char)pFoundNode->name[0x15] == (unsigned char)0x1f);
		CHECK((unsigned char)pFoundNode->name[0x16] == (unsigned char)0x36);
		CHECK((unsigned char)pFoundNode->name[0x17] == (unsigned char)0xb2);
		CHECK((unsigned char)pFoundNode->name[0x18] == (unsigned char)0x3d);
		CHECK((unsigned char)pFoundNode->name[0x19] == (unsigned char)0x87);
		CHECK((unsigned char)pFoundNode->name[0x1a] == (unsigned char)0xe9);
		CHECK((unsigned char)pFoundNode->name[0x1b] == (unsigned char)0xc8);
		CHECK((unsigned char)pFoundNode->name[0x1c] == (unsigned char)0xf8);
		CHECK((unsigned char)pFoundNode->name[0x1d] == (unsigned char)0x2d);
		CHECK((unsigned char)pFoundNode->name[0x1e] == (unsigned char)0x8a);
		CHECK((unsigned char)pFoundNode->name[0x1f] == (unsigned char)0xe4);
		CHECK((unsigned char)pFoundNode->name[0x20] == (unsigned char)0x21);
		CHECK((unsigned char)pFoundNode->name[0x21] == (unsigned char)0xd7);
		CHECK((unsigned char)pFoundNode->name[0x22] == (unsigned char)0xbb);
		CHECK((unsigned char)pFoundNode->name[0x23] == (unsigned char)0xdb);
		CHECK((unsigned char)pFoundNode->name[0x24] == (unsigned char)0x35);
		CHECK((unsigned char)pFoundNode->name[0x25] == (unsigned char)0x65);
		CHECK((unsigned char)pFoundNode->name[0x26] == (unsigned char)0x1d);
		CHECK((unsigned char)pFoundNode->name[0x27] == (unsigned char)0x73);
		CHECK((unsigned char)pFoundNode->name[0x28] == (unsigned char)0x38);
		CHECK((unsigned char)pFoundNode->name[0x29] == (unsigned char)0x8c);
		CHECK((unsigned char)pFoundNode->name[0x2a] == (unsigned char)0xfd);
		CHECK((unsigned char)pFoundNode->name[0x2b] == (unsigned char)0x93);
		CHECK((unsigned char)pFoundNode->name[0x2c] == (unsigned char)0x31);
		CHECK((unsigned char)pFoundNode->name[0x2d] == (unsigned char)0x34);
		CHECK((unsigned char)pFoundNode->name[0x2e] == (unsigned char)0x7b);
		CHECK((unsigned char)pFoundNode->name[0x2f] == (unsigned char)0x39);
		CHECK((unsigned char)pFoundNode->name[0x30] == (unsigned char)0xe6);
		CHECK((unsigned char)pFoundNode->name[0x31] == (unsigned char)0x89);
		CHECK((unsigned char)pFoundNode->name[0x32] == (unsigned char)0x40);
		CHECK((unsigned char)pFoundNode->name[0x33] == (unsigned char)0x8c);
		CHECK((unsigned char)pFoundNode->name[0x34] == (unsigned char)0x30);
		CHECK((unsigned char)pFoundNode->name[0x35] == (unsigned char)0xed);
		CHECK((unsigned char)pFoundNode->name[0x36] == (unsigned char)0x54);
		CHECK((unsigned char)pFoundNode->name[0x37] == (unsigned char)0xbf);
		CHECK((unsigned char)pFoundNode->name[0x38] == (unsigned char)0xdb);
		CHECK((unsigned char)pFoundNode->name[0x39] == (unsigned char)0x6f);
		CHECK((unsigned char)pFoundNode->name[0x3a] == (unsigned char)0xb0);
		CHECK((unsigned char)pFoundNode->name[0x3b] == (unsigned char)0x9c);
		CHECK((unsigned char)pFoundNode->name[0x3c] == (unsigned char)0xa3);
		CHECK((unsigned char)pFoundNode->name[0x3d] == (unsigned char)0x67);
		CHECK((unsigned char)pFoundNode->name[0x3e] == (unsigned char)0x13);
		CHECK((unsigned char)pFoundNode->name[0x3f] == (unsigned char)0x62);
		CHECK((unsigned char)pFoundNode->name[0x40] == (unsigned char)0x9b);
		CHECK((unsigned char)pFoundNode->name[0x41] == (unsigned char)0xe1);
		CHECK((unsigned char)pFoundNode->name[0x42] == (unsigned char)0xbc);
		CHECK((unsigned char)pFoundNode->name[0x43] == (unsigned char)0x5b);
		CHECK((unsigned char)pFoundNode->name[0x44] == (unsigned char)0x09);
		CHECK((unsigned char)pFoundNode->name[0x45] == (unsigned char)0xf0);
		CHECK((unsigned char)pFoundNode->name[0x46] == (unsigned char)0x92);
		CHECK((unsigned char)pFoundNode->name[0x47] == (unsigned char)0x44);
		CHECK((unsigned char)pFoundNode->name[0x48] == (unsigned char)0x29);
		CHECK((unsigned char)pFoundNode->name[0x49] == (unsigned char)0x21);
		CHECK((unsigned char)pFoundNode->name[0x4a] == (unsigned char)0xd3);
		CHECK((unsigned char)pFoundNode->name[0x4b] == (unsigned char)0x7d);
		CHECK((unsigned char)pFoundNode->name[0x4c] == (unsigned char)0x4b);
		CHECK((unsigned char)pFoundNode->name[0x4d] == (unsigned char)0x0e);
		CHECK((unsigned char)pFoundNode->name[0x4e] == (unsigned char)0xdb);
		CHECK((unsigned char)pFoundNode->name[0x4f] == (unsigned char)0x90);
		CHECK((unsigned char)pFoundNode->name[0x50] == (unsigned char)0xb4);
		CHECK((unsigned char)pFoundNode->name[0x51] == (unsigned char)0x71);
		CHECK((unsigned char)pFoundNode->name[0x52] == (unsigned char)0xa2);
		CHECK((unsigned char)pFoundNode->name[0x53] == (unsigned char)0x85);
		CHECK((unsigned char)pFoundNode->name[0x54] == (unsigned char)0x48);
		CHECK((unsigned char)pFoundNode->name[0x55] == (unsigned char)0x0b);
		CHECK((unsigned char)pFoundNode->name[0x56] == (unsigned char)0x6e);
		CHECK((unsigned char)pFoundNode->name[0x57] == (unsigned char)0x96);
		CHECK((unsigned char)pFoundNode->name[0x58] == (unsigned char)0xe0);
		CHECK((unsigned char)pFoundNode->name[0x59] == (unsigned char)0x55);
		CHECK((unsigned char)pFoundNode->name[0x5a] == (unsigned char)0xed);
		CHECK((unsigned char)pFoundNode->name[0x5b] == (unsigned char)0x3d);
		CHECK((unsigned char)pFoundNode->name[0x5c] == (unsigned char)0xd2);
		CHECK((unsigned char)pFoundNode->name[0x5d] == (unsigned char)0xda);
		CHECK((unsigned char)pFoundNode->name[0x5e] == (unsigned char)0xa6);
		CHECK((unsigned char)pFoundNode->name[0x5f] == (unsigned char)0xa6);
		CHECK((unsigned char)pFoundNode->name[0x60] == (unsigned char)0x10);
		CHECK((unsigned char)pFoundNode->name[0x61] == (unsigned char)0x15);
		CHECK((unsigned char)pFoundNode->name[0x62] == (unsigned char)0x79);
		CHECK((unsigned char)pFoundNode->name[0x63] == (unsigned char)0x82);
		CHECK((unsigned char)pFoundNode->name[0x64] == (unsigned char)0x51);
		CHECK((unsigned char)pFoundNode->name[0x65] == (unsigned char)0xc7);
		CHECK((unsigned char)pFoundNode->name[0x66] == (unsigned char)0x26);
		CHECK((unsigned char)pFoundNode->name[0x67] == (unsigned char)0x4a);
		CHECK((unsigned char)pFoundNode->name[0x68] == (unsigned char)0x4f);
		CHECK((unsigned char)pFoundNode->name[0x69] == (unsigned char)0x97);
		CHECK((unsigned char)pFoundNode->name[0x6a] == (unsigned char)0x01);
		CHECK((unsigned char)pFoundNode->name[0x6b] == (unsigned char)0xe3);
		CHECK((unsigned char)pFoundNode->name[0x6c] == (unsigned char)0xe7);
		CHECK((unsigned char)pFoundNode->name[0x6d] == (unsigned char)0xf5);
		CHECK((unsigned char)pFoundNode->name[0x6e] == (unsigned char)0x58);
		CHECK((unsigned char)pFoundNode->name[0x6f] == (unsigned char)0x49);
		CHECK((unsigned char)pFoundNode->name[0x70] == (unsigned char)0x40);
		CHECK((unsigned char)pFoundNode->name[0x71] == (unsigned char)0x0a);
		CHECK((unsigned char)pFoundNode->name[0x72] == (unsigned char)0x37);
		CHECK((unsigned char)pFoundNode->name[0x73] == (unsigned char)0x0f);
		CHECK((unsigned char)pFoundNode->name[0x74] == (unsigned char)0x31);
		CHECK((unsigned char)pFoundNode->name[0x75] == (unsigned char)0xb2);
		CHECK((unsigned char)pFoundNode->name[0x76] == (unsigned char)0x78);
		CHECK((unsigned char)pFoundNode->name[0x77] == (unsigned char)0xfb);
		CHECK((unsigned char)pFoundNode->name[0x78] == (unsigned char)0xa1);
		CHECK((unsigned char)pFoundNode->name[0x79] == (unsigned char)0x58);
		CHECK((unsigned char)pFoundNode->name[0x7a] == (unsigned char)0x62);
		CHECK((unsigned char)pFoundNode->name[0x7b] == (unsigned char)0x88);
		CHECK((unsigned char)pFoundNode->name[0x7c] == (unsigned char)0x0b);
		CHECK((unsigned char)pFoundNode->name[0x7d] == (unsigned char)0x14);
		CHECK((unsigned char)pFoundNode->name[0x7e] == (unsigned char)0xb9);
		CHECK((unsigned char)pFoundNode->name[0x7f] == (unsigned char)0x00);
		CHECK(pFoundNode->key == 0x104C37BE);

		// Make sure its not used below
		pFoundNode = 0;

	//-----------------------------------------------------------------------------
	// Convert to HotCold
	//-----------------------------------------------------------------------------

	// Create a timer objects
	PerformanceTimer t3;

	// start timer
	t3.Tic();

		// -----------------------------------------------------------------------
		//  This is your new function
		// -----------------------------------------------------------------------
		//          Use this API signature to convert the bloated list to hot/cold
		//          You cannot reference the original data, you need to copy 
		//          and convert Original data into your new layout
		// -----------------------------------------------------------------------
		pHotCold = new HotCold(pBloated);

	// stop timer
	t3.Toc();

	CHECK(pHotCold != 0);

	//-----------------------------------------------------------------------------
	// Make sure you haven't reference the data
	//-----------------------------------------------------------------------------
	delete pBloated;
	pBloated = 0;

	//-----------------------------------------------------------------------------
	// Find a specific Key
	//-----------------------------------------------------------------------------

	HotNode  *pFoundHotNode;
	ColdNode *pFoundColdNode;

	// Create a timer objects
	PerformanceTimer t4;

	// start timer
	t4.Tic();

		// find a specific key
		foundFlag = pHotCold->FindKey(0x104C37BE, pFoundColdNode, pFoundHotNode);

	// stop timer
	t4.Toc();
	CHECK(foundFlag == true);

	//-----------------------------------------------------------------------------
	// Verify
	//-----------------------------------------------------------------------------

		CHECK(pFoundColdNode->x == 16949.7109f);
		CHECK(pFoundColdNode->y == 17853.2305f);
		CHECK(pFoundColdNode->z == 26587.0527f);

		CHECK(pFoundColdNode->A.x == 6247.274902f);
		CHECK(pFoundColdNode->A.y == 25425.746094f);
		CHECK(pFoundColdNode->A.z == 23551.759766f);

		CHECK(pFoundColdNode->B.x == 14479.426758f);
		CHECK(pFoundColdNode->B.y == 17492.029297f);
		CHECK(pFoundColdNode->B.z == 19202.816406f);
	
		CHECK(pFoundColdNode->C.x == 27231.945313f);
		CHECK(pFoundColdNode->C.y == 26241.130859f);
		CHECK(pFoundColdNode->C.z == 15572.863281f);

		CHECK(pFoundColdNode->MA.m00 == 21634.212891f);
		CHECK(pFoundColdNode->MA.m01 == 24311.041016f);
		CHECK(pFoundColdNode->MA.m02 == 20878.404297f);
		CHECK(pFoundColdNode->MA.m03 == 27057.738281f);
		CHECK(pFoundColdNode->MA.m10 == 30450.693359f);
		CHECK(pFoundColdNode->MA.m11 == 17123.791016f);
		CHECK(pFoundColdNode->MA.m12 == 27832.166016f);
		CHECK(pFoundColdNode->MA.m13 == 32506.955078f);
		CHECK(pFoundColdNode->MA.m20 == 30677.302734f);
		CHECK(pFoundColdNode->MA.m21 == 196.778442f);
		CHECK(pFoundColdNode->MA.m22 == 14500.138672f);
		CHECK(pFoundColdNode->MA.m23 == 19330.308594f);
		CHECK(pFoundColdNode->MA.m30 == 11667.819336f);
		CHECK(pFoundColdNode->MA.m31 == 15166.396484f);
		CHECK(pFoundColdNode->MA.m32 == 19997.603516f);
		CHECK(pFoundColdNode->MA.m33 == 5982.881348f);

		CHECK(pFoundColdNode->MB.m00 == 20984.812500f);
		CHECK(pFoundColdNode->MB.m01 == 13178.451172f);
		CHECK(pFoundColdNode->MB.m02 == 30863.783203f);
		CHECK(pFoundColdNode->MB.m03 == 4715.444336f);
		CHECK(pFoundColdNode->MB.m10 == 25778.341797f);
		CHECK(pFoundColdNode->MB.m11 == 16292.379883f);
		CHECK(pFoundColdNode->MB.m12 == 24716.837891f);
		CHECK(pFoundColdNode->MB.m13 == 21190.500000f);
		CHECK(pFoundColdNode->MB.m20 == 7638.266113f);
		CHECK(pFoundColdNode->MB.m21 == 20846.099609f);
		CHECK(pFoundColdNode->MB.m22 == 17995.501953f);
		CHECK(pFoundColdNode->MB.m23 == 25425.935547f);
		CHECK(pFoundColdNode->MB.m30 == 28764.193359f);
		CHECK(pFoundColdNode->MB.m31 == 3212.480225f);
		CHECK(pFoundColdNode->MB.m32 == 19492.333984f);
		CHECK(pFoundColdNode->MB.m33 == 25141.316406f);

		CHECK(pFoundColdNode->MC.m00 == 7326.042480f);
		CHECK(pFoundColdNode->MC.m01 == 27958.443359f);
		CHECK(pFoundColdNode->MC.m02 == 20758.595703f);
		CHECK(pFoundColdNode->MC.m03 == 12123.787109f);
		CHECK(pFoundColdNode->MC.m10 == 21213.230469f);
		CHECK(pFoundColdNode->MC.m11 == 32425.681641f);
		CHECK(pFoundColdNode->MC.m12 == 23361.755859f);
		CHECK(pFoundColdNode->MC.m13 == 10994.614258f);
		CHECK(pFoundColdNode->MC.m20 == 26044.498047f);
		CHECK(pFoundColdNode->MC.m21 == 8614.010742f);
		CHECK(pFoundColdNode->MC.m22 == 4716.622070f);
		CHECK(pFoundColdNode->MC.m23 == 1004.341858f);
		CHECK(pFoundColdNode->MC.m30 == 3267.344971f);
		CHECK(pFoundColdNode->MC.m31 == 25329.337891f);
		CHECK(pFoundColdNode->MC.m32 == 19072.089844f);
		CHECK(pFoundColdNode->MC.m33 == 5760.577637f);

		CHECK(pFoundColdNode->MD.m00 == 14046.095703f);
		CHECK(pFoundColdNode->MD.m01 == 25044.259766f);
		CHECK(pFoundColdNode->MD.m02 == 7691.525391f);
		CHECK(pFoundColdNode->MD.m03 == 23210.404297f);
		CHECK(pFoundColdNode->MD.m10 == 27867.595703f);
		CHECK(pFoundColdNode->MD.m11 == 18074.292969f);
		CHECK(pFoundColdNode->MD.m12 == 6334.767578f);
		CHECK(pFoundColdNode->MD.m13 == 25254.414063f);
		CHECK(pFoundColdNode->MD.m20 == 17392.523438f);
		CHECK(pFoundColdNode->MD.m21 == 18708.707031f);
		CHECK(pFoundColdNode->MD.m22 == 29167.757813f);
		CHECK(pFoundColdNode->MD.m23 == 27001.369141f);
		CHECK(pFoundColdNode->MD.m30 == 24626.333984f);
		CHECK(pFoundColdNode->MD.m31 == 18199.013672f);
		CHECK(pFoundColdNode->MD.m32 == 22296.794922f);
		CHECK(pFoundColdNode->MD.m33 == 29032.484375f);

		CHECK((unsigned char)pFoundColdNode->name[0x00] == (unsigned char)0x27);
		CHECK((unsigned char)pFoundColdNode->name[0x01] == (unsigned char)0xc6);
		CHECK((unsigned char)pFoundColdNode->name[0x02] == (unsigned char)0x67);
		CHECK((unsigned char)pFoundColdNode->name[0x03] == (unsigned char)0x8f);
		CHECK((unsigned char)pFoundColdNode->name[0x04] == (unsigned char)0x9d);
		CHECK((unsigned char)pFoundColdNode->name[0x05] == (unsigned char)0xb3);
		CHECK((unsigned char)pFoundColdNode->name[0x06] == (unsigned char)0xf2);
		CHECK((unsigned char)pFoundColdNode->name[0x07] == (unsigned char)0xae);
		CHECK((unsigned char)pFoundColdNode->name[0x08] == (unsigned char)0x58);
		CHECK((unsigned char)pFoundColdNode->name[0x09] == (unsigned char)0xa5);
		CHECK((unsigned char)pFoundColdNode->name[0x0a] == (unsigned char)0x81);
		CHECK((unsigned char)pFoundColdNode->name[0x0b] == (unsigned char)0x82);
		CHECK((unsigned char)pFoundColdNode->name[0x0c] == (unsigned char)0x65);
		CHECK((unsigned char)pFoundColdNode->name[0x0d] == (unsigned char)0x63);
		CHECK((unsigned char)pFoundColdNode->name[0x0e] == (unsigned char)0x26);
		CHECK((unsigned char)pFoundColdNode->name[0x0f] == (unsigned char)0xda);
		CHECK((unsigned char)pFoundColdNode->name[0x10] == (unsigned char)0xe9);
		CHECK((unsigned char)pFoundColdNode->name[0x11] == (unsigned char)0x79);
		CHECK((unsigned char)pFoundColdNode->name[0x12] == (unsigned char)0x83);
		CHECK((unsigned char)pFoundColdNode->name[0x13] == (unsigned char)0xb2);
		CHECK((unsigned char)pFoundColdNode->name[0x14] == (unsigned char)0x1b);
		CHECK((unsigned char)pFoundColdNode->name[0x15] == (unsigned char)0x1f);
		CHECK((unsigned char)pFoundColdNode->name[0x16] == (unsigned char)0x36);
		CHECK((unsigned char)pFoundColdNode->name[0x17] == (unsigned char)0xb2);
		CHECK((unsigned char)pFoundColdNode->name[0x18] == (unsigned char)0x3d);
		CHECK((unsigned char)pFoundColdNode->name[0x19] == (unsigned char)0x87);
		CHECK((unsigned char)pFoundColdNode->name[0x1a] == (unsigned char)0xe9);
		CHECK((unsigned char)pFoundColdNode->name[0x1b] == (unsigned char)0xc8);
		CHECK((unsigned char)pFoundColdNode->name[0x1c] == (unsigned char)0xf8);
		CHECK((unsigned char)pFoundColdNode->name[0x1d] == (unsigned char)0x2d);
		CHECK((unsigned char)pFoundColdNode->name[0x1e] == (unsigned char)0x8a);
		CHECK((unsigned char)pFoundColdNode->name[0x1f] == (unsigned char)0xe4);
		CHECK((unsigned char)pFoundColdNode->name[0x20] == (unsigned char)0x21);
		CHECK((unsigned char)pFoundColdNode->name[0x21] == (unsigned char)0xd7);
		CHECK((unsigned char)pFoundColdNode->name[0x22] == (unsigned char)0xbb);
		CHECK((unsigned char)pFoundColdNode->name[0x23] == (unsigned char)0xdb);
		CHECK((unsigned char)pFoundColdNode->name[0x24] == (unsigned char)0x35);
		CHECK((unsigned char)pFoundColdNode->name[0x25] == (unsigned char)0x65);
		CHECK((unsigned char)pFoundColdNode->name[0x26] == (unsigned char)0x1d);
		CHECK((unsigned char)pFoundColdNode->name[0x27] == (unsigned char)0x73);
		CHECK((unsigned char)pFoundColdNode->name[0x28] == (unsigned char)0x38);
		CHECK((unsigned char)pFoundColdNode->name[0x29] == (unsigned char)0x8c);
		CHECK((unsigned char)pFoundColdNode->name[0x2a] == (unsigned char)0xfd);
		CHECK((unsigned char)pFoundColdNode->name[0x2b] == (unsigned char)0x93);
		CHECK((unsigned char)pFoundColdNode->name[0x2c] == (unsigned char)0x31);
		CHECK((unsigned char)pFoundColdNode->name[0x2d] == (unsigned char)0x34);
		CHECK((unsigned char)pFoundColdNode->name[0x2e] == (unsigned char)0x7b);
		CHECK((unsigned char)pFoundColdNode->name[0x2f] == (unsigned char)0x39);
		CHECK((unsigned char)pFoundColdNode->name[0x30] == (unsigned char)0xe6);
		CHECK((unsigned char)pFoundColdNode->name[0x31] == (unsigned char)0x89);
		CHECK((unsigned char)pFoundColdNode->name[0x32] == (unsigned char)0x40);
		CHECK((unsigned char)pFoundColdNode->name[0x33] == (unsigned char)0x8c);
		CHECK((unsigned char)pFoundColdNode->name[0x34] == (unsigned char)0x30);
		CHECK((unsigned char)pFoundColdNode->name[0x35] == (unsigned char)0xed);
		CHECK((unsigned char)pFoundColdNode->name[0x36] == (unsigned char)0x54);
		CHECK((unsigned char)pFoundColdNode->name[0x37] == (unsigned char)0xbf);
		CHECK((unsigned char)pFoundColdNode->name[0x38] == (unsigned char)0xdb);
		CHECK((unsigned char)pFoundColdNode->name[0x39] == (unsigned char)0x6f);
		CHECK((unsigned char)pFoundColdNode->name[0x3a] == (unsigned char)0xb0);
		CHECK((unsigned char)pFoundColdNode->name[0x3b] == (unsigned char)0x9c);
		CHECK((unsigned char)pFoundColdNode->name[0x3c] == (unsigned char)0xa3);
		CHECK((unsigned char)pFoundColdNode->name[0x3d] == (unsigned char)0x67);
		CHECK((unsigned char)pFoundColdNode->name[0x3e] == (unsigned char)0x13);
		CHECK((unsigned char)pFoundColdNode->name[0x3f] == (unsigned char)0x62);
		CHECK((unsigned char)pFoundColdNode->name[0x40] == (unsigned char)0x9b);
		CHECK((unsigned char)pFoundColdNode->name[0x41] == (unsigned char)0xe1);
		CHECK((unsigned char)pFoundColdNode->name[0x42] == (unsigned char)0xbc);
		CHECK((unsigned char)pFoundColdNode->name[0x43] == (unsigned char)0x5b);
		CHECK((unsigned char)pFoundColdNode->name[0x44] == (unsigned char)0x09);
		CHECK((unsigned char)pFoundColdNode->name[0x45] == (unsigned char)0xf0);
		CHECK((unsigned char)pFoundColdNode->name[0x46] == (unsigned char)0x92);
		CHECK((unsigned char)pFoundColdNode->name[0x47] == (unsigned char)0x44);
		CHECK((unsigned char)pFoundColdNode->name[0x48] == (unsigned char)0x29);
		CHECK((unsigned char)pFoundColdNode->name[0x49] == (unsigned char)0x21);
		CHECK((unsigned char)pFoundColdNode->name[0x4a] == (unsigned char)0xd3);
		CHECK((unsigned char)pFoundColdNode->name[0x4b] == (unsigned char)0x7d);
		CHECK((unsigned char)pFoundColdNode->name[0x4c] == (unsigned char)0x4b);
		CHECK((unsigned char)pFoundColdNode->name[0x4d] == (unsigned char)0x0e);
		CHECK((unsigned char)pFoundColdNode->name[0x4e] == (unsigned char)0xdb);
		CHECK((unsigned char)pFoundColdNode->name[0x4f] == (unsigned char)0x90);
		CHECK((unsigned char)pFoundColdNode->name[0x50] == (unsigned char)0xb4);
		CHECK((unsigned char)pFoundColdNode->name[0x51] == (unsigned char)0x71);
		CHECK((unsigned char)pFoundColdNode->name[0x52] == (unsigned char)0xa2);
		CHECK((unsigned char)pFoundColdNode->name[0x53] == (unsigned char)0x85);
		CHECK((unsigned char)pFoundColdNode->name[0x54] == (unsigned char)0x48);
		CHECK((unsigned char)pFoundColdNode->name[0x55] == (unsigned char)0x0b);
		CHECK((unsigned char)pFoundColdNode->name[0x56] == (unsigned char)0x6e);
		CHECK((unsigned char)pFoundColdNode->name[0x57] == (unsigned char)0x96);
		CHECK((unsigned char)pFoundColdNode->name[0x58] == (unsigned char)0xe0);
		CHECK((unsigned char)pFoundColdNode->name[0x59] == (unsigned char)0x55);
		CHECK((unsigned char)pFoundColdNode->name[0x5a] == (unsigned char)0xed);
		CHECK((unsigned char)pFoundColdNode->name[0x5b] == (unsigned char)0x3d);
		CHECK((unsigned char)pFoundColdNode->name[0x5c] == (unsigned char)0xd2);
		CHECK((unsigned char)pFoundColdNode->name[0x5d] == (unsigned char)0xda);
		CHECK((unsigned char)pFoundColdNode->name[0x5e] == (unsigned char)0xa6);
		CHECK((unsigned char)pFoundColdNode->name[0x5f] == (unsigned char)0xa6);
		CHECK((unsigned char)pFoundColdNode->name[0x60] == (unsigned char)0x10);
		CHECK((unsigned char)pFoundColdNode->name[0x61] == (unsigned char)0x15);
		CHECK((unsigned char)pFoundColdNode->name[0x62] == (unsigned char)0x79);
		CHECK((unsigned char)pFoundColdNode->name[0x63] == (unsigned char)0x82);
		CHECK((unsigned char)pFoundColdNode->name[0x64] == (unsigned char)0x51);
		CHECK((unsigned char)pFoundColdNode->name[0x65] == (unsigned char)0xc7);
		CHECK((unsigned char)pFoundColdNode->name[0x66] == (unsigned char)0x26);
		CHECK((unsigned char)pFoundColdNode->name[0x67] == (unsigned char)0x4a);
		CHECK((unsigned char)pFoundColdNode->name[0x68] == (unsigned char)0x4f);
		CHECK((unsigned char)pFoundColdNode->name[0x69] == (unsigned char)0x97);
		CHECK((unsigned char)pFoundColdNode->name[0x6a] == (unsigned char)0x01);
		CHECK((unsigned char)pFoundColdNode->name[0x6b] == (unsigned char)0xe3);
		CHECK((unsigned char)pFoundColdNode->name[0x6c] == (unsigned char)0xe7);
		CHECK((unsigned char)pFoundColdNode->name[0x6d] == (unsigned char)0xf5);
		CHECK((unsigned char)pFoundColdNode->name[0x6e] == (unsigned char)0x58);
		CHECK((unsigned char)pFoundColdNode->name[0x6f] == (unsigned char)0x49);
		CHECK((unsigned char)pFoundColdNode->name[0x70] == (unsigned char)0x40);
		CHECK((unsigned char)pFoundColdNode->name[0x71] == (unsigned char)0x0a);
		CHECK((unsigned char)pFoundColdNode->name[0x72] == (unsigned char)0x37);
		CHECK((unsigned char)pFoundColdNode->name[0x73] == (unsigned char)0x0f);
		CHECK((unsigned char)pFoundColdNode->name[0x74] == (unsigned char)0x31);
		CHECK((unsigned char)pFoundColdNode->name[0x75] == (unsigned char)0xb2);
		CHECK((unsigned char)pFoundColdNode->name[0x76] == (unsigned char)0x78);
		CHECK((unsigned char)pFoundColdNode->name[0x77] == (unsigned char)0xfb);
		CHECK((unsigned char)pFoundColdNode->name[0x78] == (unsigned char)0xa1);
		CHECK((unsigned char)pFoundColdNode->name[0x79] == (unsigned char)0x58);
		CHECK((unsigned char)pFoundColdNode->name[0x7a] == (unsigned char)0x62);
		CHECK((unsigned char)pFoundColdNode->name[0x7b] == (unsigned char)0x88);
		CHECK((unsigned char)pFoundColdNode->name[0x7c] == (unsigned char)0x0b);
		CHECK((unsigned char)pFoundColdNode->name[0x7d] == (unsigned char)0x14);
		CHECK((unsigned char)pFoundColdNode->name[0x7e] == (unsigned char)0xb9);
		CHECK((unsigned char)pFoundColdNode->name[0x7f] == (unsigned char)0x00);
		CHECK(pFoundHotNode->key == 0x104C37BE);


	//-----------------------------------------------------------------------------
	// Print Results
	//-----------------------------------------------------------------------------

	Trace::out("\n");
	Trace::out("  Bloated List create: %f s\n", t1.TimeInSeconds());
	Trace::out("      HotCold convert: %f ms\n", t3.TimeInSeconds() * 1000.0f);
	Trace::out("\n");
	Trace::out("         Bloated find: %f ms\n", t2.TimeInSeconds() * 1000.0f);
	Trace::out("         HotCold find: %f ms\n", t4.TimeInSeconds() * 1000.0f);
	Trace::out("\n");
	Trace::out("                Ratio: %f \n", t2.TimeInSeconds() / t4.TimeInSeconds());


} TEST_END


TEST_TEARDOWN(Timing, HotCold)
{
	delete pBloated;
	delete pHotCold;
}

#endif

// End of File
