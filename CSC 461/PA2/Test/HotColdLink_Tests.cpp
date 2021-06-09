//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------- 

#include "Framework.h"
#include "_UnitTestConfiguration.h"

#include "Node.h"
#include "Bloated.h"
#include "HotCold.h"

static HotCold *pHotCold = 0;

#if Link_HotCold_Test_Enable
TEST_WITH_TEARDOWN(Link, HotCold, Link_HotCold_Test_Enable)
{
	//-----------------------------------------------------------------------------
	// It initializes the data if a very bloated way do not modify it!
	//-----------------------------------------------------------------------------

	Bloated *pBloated = new Bloated(1000);
	CHECK(pBloated != 0);

	// -----------------------------------------------------------------------
	//  This is your new function
	// -----------------------------------------------------------------------
	//          Use this API signature to convert the bloated list to hot/cold
	//          You cannot reference the original data, you need to copy 
	//          and convert Original data into your new layout
	// -----------------------------------------------------------------------
	pHotCold = new HotCold( pBloated );
	CHECK(pHotCold != 0);

	//-----------------------------------------------------------------------------
	// Make sure you haven't reference the data
	//-----------------------------------------------------------------------------
	delete pBloated;
	pBloated = 0;

	//-----------------------------------------------------------------------------
	// Find a specific Keys
	//-----------------------------------------------------------------------------

	HotNode  *pFoundHotNode;
	ColdNode *pFoundColdNode;
	bool foundFlag;

	//-------------------------------------------------------------------
	// Find Key A
	//-------------------------------------------------------------------
	foundFlag = pHotCold->FindKey(0x17281445, pFoundColdNode, pFoundHotNode);
	CHECK(foundFlag == true);

	CHECK(pFoundColdNode->x == 6628.170410f);
	CHECK(pFoundColdNode->y == 26336.000000f);
	CHECK(pFoundColdNode->z == 15986.185547f);
	CHECK(pFoundColdNode->A.x == 30603.710938f);
	CHECK(pFoundColdNode->A.y == 5783.308594f);
	CHECK(pFoundColdNode->A.z == 2290.570068f);
	CHECK(pFoundColdNode->B.x == 14609.004883f);
	CHECK(pFoundColdNode->B.y == 10465.243164f);
	CHECK(pFoundColdNode->B.z == 27687.509766f);
	CHECK(pFoundColdNode->C.x == 27372.203125f);
	CHECK(pFoundColdNode->C.y == 21561.359375f);
	CHECK(pFoundColdNode->C.z == 11176.781250f);
	CHECK(pFoundColdNode->MA.m00 == 28827.089844f);
	CHECK(pFoundColdNode->MA.m01 == 5147.714844f);
	CHECK(pFoundColdNode->MA.m02 == 23204.388672f);
	CHECK(pFoundColdNode->MA.m03 == 29040.712891f);
	CHECK(pFoundColdNode->MA.m10 == 31489.464844f);
	CHECK(pFoundColdNode->MA.m11 == 13551.084961f);
	CHECK(pFoundColdNode->MA.m12 == 10575.935547f);
	CHECK(pFoundColdNode->MA.m13 == 12333.951172f);
	CHECK(pFoundColdNode->MA.m20 == 27114.000000f);
	CHECK(pFoundColdNode->MA.m21 == 24960.080078f);
	CHECK(pFoundColdNode->MA.m22 == 15871.195313f);
	CHECK(pFoundColdNode->MA.m23 == 25782.871094f);
	CHECK(pFoundColdNode->MA.m30 == 14825.485352f);
	CHECK(pFoundColdNode->MA.m31 == 23559.513672f);
	CHECK(pFoundColdNode->MA.m32 == 21946.007813f);
	CHECK(pFoundColdNode->MA.m33 == 25927.875000f);
	CHECK(pFoundColdNode->MB.m00 == 11287.224609f);
	CHECK(pFoundColdNode->MB.m01 == 28513.115234f);
	CHECK(pFoundColdNode->MB.m02 == 6986.765625f);
	CHECK(pFoundColdNode->MB.m03 == 1024.590088f);
	CHECK(pFoundColdNode->MB.m10 == 31890.765625f);
	CHECK(pFoundColdNode->MB.m11 == 22927.048828f);
	CHECK(pFoundColdNode->MB.m12 == 26045.947266f);
	CHECK(pFoundColdNode->MB.m13 == 16740.679688f);
	CHECK(pFoundColdNode->MB.m20 == 10489.248047f);
	CHECK(pFoundColdNode->MB.m21 == 17976.027344f);
	CHECK(pFoundColdNode->MB.m22 == 1768.278076f);
	CHECK(pFoundColdNode->MB.m23 == 3803.289063f);
	CHECK(pFoundColdNode->MB.m30 == 18162.369141f);
	CHECK(pFoundColdNode->MB.m31 == 22821.076172f);
	CHECK(pFoundColdNode->MB.m32 == 10719.519531f);
	CHECK(pFoundColdNode->MB.m33 == 8496.104492f);
	CHECK(pFoundColdNode->MC.m00 == 27301.992188f);
	CHECK(pFoundColdNode->MC.m01 == 18628.906250f);
	CHECK(pFoundColdNode->MC.m02 == 16766.873047f);
	CHECK(pFoundColdNode->MC.m03 == 21267.050781f);
	CHECK(pFoundColdNode->MC.m10 == 7486.355469f);
	CHECK(pFoundColdNode->MC.m11 == 2215.924805f);
	CHECK(pFoundColdNode->MC.m12 == 1764.021484f);
	CHECK(pFoundColdNode->MC.m13 == 6040.607422f);
	CHECK(pFoundColdNode->MC.m20 == 25455.933594f);
	CHECK(pFoundColdNode->MC.m21 == 1026.856079f);
	CHECK(pFoundColdNode->MC.m22 == 2035.781738f);
	CHECK(pFoundColdNode->MC.m23 == 31926.748047f);
	CHECK(pFoundColdNode->MC.m30 == 21483.898438f);
	CHECK(pFoundColdNode->MC.m31 == 26672.000000f);
	CHECK(pFoundColdNode->MC.m32 == 17873.396484f);
	CHECK(pFoundColdNode->MC.m33 == 15818.506836f);
	CHECK(pFoundColdNode->MD.m00 == 15852.228516f);
	CHECK(pFoundColdNode->MD.m01 == 32559.113281f);
	CHECK(pFoundColdNode->MD.m02 == 25450.443359f);
	CHECK(pFoundColdNode->MD.m03 == 26129.171875f);
	CHECK(pFoundColdNode->MD.m10 == 24494.421875f);
	CHECK(pFoundColdNode->MD.m11 == 6687.903809f);
	CHECK(pFoundColdNode->MD.m12 == 25579.367188f);
	CHECK(pFoundColdNode->MD.m13 == 817.097046f);
	CHECK(pFoundColdNode->MD.m20 == 11506.844727f);
	CHECK(pFoundColdNode->MD.m21 == 3014.172119f);
	CHECK(pFoundColdNode->MD.m22 == 31048.640625f);
	CHECK(pFoundColdNode->MD.m23 == 26545.150391f);
	CHECK(pFoundColdNode->MD.m30 == 9596.712891f);
	CHECK(pFoundColdNode->MD.m31 == 13071.556641f);
	CHECK(pFoundColdNode->MD.m32 == 25271.550781f);
	CHECK(pFoundColdNode->MD.m33 == 32124.777344f);
	CHECK((unsigned char)pFoundColdNode->name[0x00] == (unsigned char)0xd1);
	CHECK((unsigned char)pFoundColdNode->name[0x01] == (unsigned char)0x1b);
	CHECK((unsigned char)pFoundColdNode->name[0x02] == (unsigned char)0x9d);
	CHECK((unsigned char)pFoundColdNode->name[0x03] == (unsigned char)0xb7);
	CHECK((unsigned char)pFoundColdNode->name[0x04] == (unsigned char)0x8f);
	CHECK((unsigned char)pFoundColdNode->name[0x05] == (unsigned char)0xb5);
	CHECK((unsigned char)pFoundColdNode->name[0x06] == (unsigned char)0x8c);
	CHECK((unsigned char)pFoundColdNode->name[0x07] == (unsigned char)0xf7);
	CHECK((unsigned char)pFoundColdNode->name[0x08] == (unsigned char)0xd5);
	CHECK((unsigned char)pFoundColdNode->name[0x09] == (unsigned char)0x63);
	CHECK((unsigned char)pFoundColdNode->name[0x0a] == (unsigned char)0xe9);
	CHECK((unsigned char)pFoundColdNode->name[0x0b] == (unsigned char)0x87);
	CHECK((unsigned char)pFoundColdNode->name[0x0c] == (unsigned char)0x14);
	CHECK((unsigned char)pFoundColdNode->name[0x0d] == (unsigned char)0x95);
	CHECK((unsigned char)pFoundColdNode->name[0x0e] == (unsigned char)0xd0);
	CHECK((unsigned char)pFoundColdNode->name[0x0f] == (unsigned char)0x0b);
	CHECK((unsigned char)pFoundColdNode->name[0x10] == (unsigned char)0x48);
	CHECK((unsigned char)pFoundColdNode->name[0x11] == (unsigned char)0x6a);
	CHECK((unsigned char)pFoundColdNode->name[0x12] == (unsigned char)0xdf);
	CHECK((unsigned char)pFoundColdNode->name[0x13] == (unsigned char)0x78);
	CHECK((unsigned char)pFoundColdNode->name[0x14] == (unsigned char)0x68);
	CHECK((unsigned char)pFoundColdNode->name[0x15] == (unsigned char)0xbc);
	CHECK((unsigned char)pFoundColdNode->name[0x16] == (unsigned char)0xa1);
	CHECK((unsigned char)pFoundColdNode->name[0x17] == (unsigned char)0xa3);
	CHECK((unsigned char)pFoundColdNode->name[0x18] == (unsigned char)0x51);
	CHECK((unsigned char)pFoundColdNode->name[0x19] == (unsigned char)0x1a);
	CHECK((unsigned char)pFoundColdNode->name[0x1a] == (unsigned char)0xb2);
	CHECK((unsigned char)pFoundColdNode->name[0x1b] == (unsigned char)0xa1);
	CHECK((unsigned char)pFoundColdNode->name[0x1c] == (unsigned char)0x39);
	CHECK((unsigned char)pFoundColdNode->name[0x1d] == (unsigned char)0x4b);
	CHECK((unsigned char)pFoundColdNode->name[0x1e] == (unsigned char)0xb7);
	CHECK((unsigned char)pFoundColdNode->name[0x1f] == (unsigned char)0xc2);
	CHECK((unsigned char)pFoundColdNode->name[0x20] == (unsigned char)0xc5);
	CHECK((unsigned char)pFoundColdNode->name[0x21] == (unsigned char)0xda);
	CHECK((unsigned char)pFoundColdNode->name[0x22] == (unsigned char)0xe8);
	CHECK((unsigned char)pFoundColdNode->name[0x23] == (unsigned char)0x2e);
	CHECK((unsigned char)pFoundColdNode->name[0x24] == (unsigned char)0x4c);
	CHECK((unsigned char)pFoundColdNode->name[0x25] == (unsigned char)0xa3);
	CHECK((unsigned char)pFoundColdNode->name[0x26] == (unsigned char)0xd9);
	CHECK((unsigned char)pFoundColdNode->name[0x27] == (unsigned char)0xe2);
	CHECK((unsigned char)pFoundColdNode->name[0x28] == (unsigned char)0xe2);
	CHECK((unsigned char)pFoundColdNode->name[0x29] == (unsigned char)0xef);
	CHECK((unsigned char)pFoundColdNode->name[0x2a] == (unsigned char)0x47);
	CHECK((unsigned char)pFoundColdNode->name[0x2b] == (unsigned char)0x1b);
	CHECK((unsigned char)pFoundColdNode->name[0x2c] == (unsigned char)0x3e);
	CHECK((unsigned char)pFoundColdNode->name[0x2d] == (unsigned char)0xac);
	CHECK((unsigned char)pFoundColdNode->name[0x2e] == (unsigned char)0x84);
	CHECK((unsigned char)pFoundColdNode->name[0x2f] == (unsigned char)0x5f);
	CHECK((unsigned char)pFoundColdNode->name[0x30] == (unsigned char)0x12);
	CHECK((unsigned char)pFoundColdNode->name[0x31] == (unsigned char)0x24);
	CHECK((unsigned char)pFoundColdNode->name[0x32] == (unsigned char)0x4f);
	CHECK((unsigned char)pFoundColdNode->name[0x33] == (unsigned char)0x47);
	CHECK((unsigned char)pFoundColdNode->name[0x34] == (unsigned char)0xd5);
	CHECK((unsigned char)pFoundColdNode->name[0x35] == (unsigned char)0xea);
	CHECK((unsigned char)pFoundColdNode->name[0x36] == (unsigned char)0xb2);
	CHECK((unsigned char)pFoundColdNode->name[0x37] == (unsigned char)0xac);
	CHECK((unsigned char)pFoundColdNode->name[0x38] == (unsigned char)0x42);
	CHECK((unsigned char)pFoundColdNode->name[0x39] == (unsigned char)0x48);
	CHECK((unsigned char)pFoundColdNode->name[0x3a] == (unsigned char)0x42);
	CHECK((unsigned char)pFoundColdNode->name[0x3b] == (unsigned char)0x57);
	CHECK((unsigned char)pFoundColdNode->name[0x3c] == (unsigned char)0x5b);
	CHECK((unsigned char)pFoundColdNode->name[0x3d] == (unsigned char)0x63);
	CHECK((unsigned char)pFoundColdNode->name[0x3e] == (unsigned char)0x32);
	CHECK((unsigned char)pFoundColdNode->name[0x3f] == (unsigned char)0xe1);
	CHECK((unsigned char)pFoundColdNode->name[0x40] == (unsigned char)0xcc);
	CHECK((unsigned char)pFoundColdNode->name[0x41] == (unsigned char)0x7a);
	CHECK((unsigned char)pFoundColdNode->name[0x42] == (unsigned char)0xc3);
	CHECK((unsigned char)pFoundColdNode->name[0x43] == (unsigned char)0xe1);
	CHECK((unsigned char)pFoundColdNode->name[0x44] == (unsigned char)0x0d);
	CHECK((unsigned char)pFoundColdNode->name[0x45] == (unsigned char)0xd0);
	CHECK((unsigned char)pFoundColdNode->name[0x46] == (unsigned char)0xfb);
	CHECK((unsigned char)pFoundColdNode->name[0x47] == (unsigned char)0x0f);
	CHECK((unsigned char)pFoundColdNode->name[0x48] == (unsigned char)0x6c);
	CHECK((unsigned char)pFoundColdNode->name[0x49] == (unsigned char)0xc5);
	CHECK((unsigned char)pFoundColdNode->name[0x4a] == (unsigned char)0xfe);
	CHECK((unsigned char)pFoundColdNode->name[0x4b] == (unsigned char)0x74);
	CHECK((unsigned char)pFoundColdNode->name[0x4c] == (unsigned char)0x1b);
	CHECK((unsigned char)pFoundColdNode->name[0x4d] == (unsigned char)0xa3);
	CHECK((unsigned char)pFoundColdNode->name[0x4e] == (unsigned char)0xb2);
	CHECK((unsigned char)pFoundColdNode->name[0x4f] == (unsigned char)0xe8);
	CHECK((unsigned char)pFoundColdNode->name[0x50] == (unsigned char)0xc1);
	CHECK((unsigned char)pFoundColdNode->name[0x51] == (unsigned char)0x92);
	CHECK((unsigned char)pFoundColdNode->name[0x52] == (unsigned char)0x64);
	CHECK((unsigned char)pFoundColdNode->name[0x53] == (unsigned char)0x5e);
	CHECK((unsigned char)pFoundColdNode->name[0x54] == (unsigned char)0xb5);
	CHECK((unsigned char)pFoundColdNode->name[0x55] == (unsigned char)0x5d);
	CHECK((unsigned char)pFoundColdNode->name[0x56] == (unsigned char)0x9d);
	CHECK((unsigned char)pFoundColdNode->name[0x57] == (unsigned char)0xbc);
	CHECK((unsigned char)pFoundColdNode->name[0x58] == (unsigned char)0x6c);
	CHECK((unsigned char)pFoundColdNode->name[0x59] == (unsigned char)0x5a);
	CHECK((unsigned char)pFoundColdNode->name[0x5a] == (unsigned char)0xee);
	CHECK((unsigned char)pFoundColdNode->name[0x5b] == (unsigned char)0x57);
	CHECK((unsigned char)pFoundColdNode->name[0x5c] == (unsigned char)0x2e);
	CHECK((unsigned char)pFoundColdNode->name[0x5d] == (unsigned char)0xaf);
	CHECK((unsigned char)pFoundColdNode->name[0x5e] == (unsigned char)0x3f);
	CHECK((unsigned char)pFoundColdNode->name[0x5f] == (unsigned char)0xbe);
	CHECK((unsigned char)pFoundColdNode->name[0x60] == (unsigned char)0xb1);
	CHECK((unsigned char)pFoundColdNode->name[0x61] == (unsigned char)0x3d);
	CHECK((unsigned char)pFoundColdNode->name[0x62] == (unsigned char)0x85);
	CHECK((unsigned char)pFoundColdNode->name[0x63] == (unsigned char)0x6d);
	CHECK((unsigned char)pFoundColdNode->name[0x64] == (unsigned char)0xa0);
	CHECK((unsigned char)pFoundColdNode->name[0x65] == (unsigned char)0x73);
	CHECK((unsigned char)pFoundColdNode->name[0x66] == (unsigned char)0x72);
	CHECK((unsigned char)pFoundColdNode->name[0x67] == (unsigned char)0x9d);
	CHECK((unsigned char)pFoundColdNode->name[0x68] == (unsigned char)0xae);
	CHECK((unsigned char)pFoundColdNode->name[0x69] == (unsigned char)0x57);
	CHECK((unsigned char)pFoundColdNode->name[0x6a] == (unsigned char)0xe0);
	CHECK((unsigned char)pFoundColdNode->name[0x6b] == (unsigned char)0xc2);
	CHECK((unsigned char)pFoundColdNode->name[0x6c] == (unsigned char)0x38);
	CHECK((unsigned char)pFoundColdNode->name[0x6d] == (unsigned char)0xed);
	CHECK((unsigned char)pFoundColdNode->name[0x6e] == (unsigned char)0x25);
	CHECK((unsigned char)pFoundColdNode->name[0x6f] == (unsigned char)0xed);
	CHECK((unsigned char)pFoundColdNode->name[0x70] == (unsigned char)0x26);
	CHECK((unsigned char)pFoundColdNode->name[0x71] == (unsigned char)0xef);
	CHECK((unsigned char)pFoundColdNode->name[0x72] == (unsigned char)0x09);
	CHECK((unsigned char)pFoundColdNode->name[0x73] == (unsigned char)0x23);
	CHECK((unsigned char)pFoundColdNode->name[0x74] == (unsigned char)0xf9);
	CHECK((unsigned char)pFoundColdNode->name[0x75] == (unsigned char)0xe2);
	CHECK((unsigned char)pFoundColdNode->name[0x76] == (unsigned char)0x12);
	CHECK((unsigned char)pFoundColdNode->name[0x77] == (unsigned char)0x5f);
	CHECK((unsigned char)pFoundColdNode->name[0x78] == (unsigned char)0xcd);
	CHECK((unsigned char)pFoundColdNode->name[0x79] == (unsigned char)0x7a);
	CHECK((unsigned char)pFoundColdNode->name[0x7a] == (unsigned char)0x5b);
	CHECK((unsigned char)pFoundColdNode->name[0x7b] == (unsigned char)0xde);
	CHECK((unsigned char)pFoundColdNode->name[0x7c] == (unsigned char)0x23);
	CHECK((unsigned char)pFoundColdNode->name[0x7d] == (unsigned char)0xf9);
	CHECK((unsigned char)pFoundColdNode->name[0x7e] == (unsigned char)0x99);
	CHECK((unsigned char)pFoundColdNode->name[0x7f] == (unsigned char)0x00);

	CHECK(pFoundHotNode->key == 0x17281445);
	CHECK(pFoundHotNode->pCold == pFoundColdNode);
	CHECK(pFoundColdNode->pHot == pFoundHotNode);

	HotNode *pA = pFoundHotNode;

	CHECK(pA != 0);

	CHECK(pA->key == 0x17281445);
	CHECK(pA->pPrev == 0);
	CHECK(pA->pNext != 0);
	CHECK(pA->pCold == pFoundColdNode);

	HotNode *pB = pA->pNext;
	CHECK(pB != 0);

	CHECK(pB->key == 0x3019389B);
	CHECK(pB->pPrev == pA);
	CHECK(pB->pNext != 0);
	CHECK(pB->pCold != 0);

	HotNode *pC = pB->pNext;
	CHECK(pC != 0);

	CHECK(pC->key == 0x54922db7);
	CHECK(pC->pPrev == pB);
	CHECK(pC->pNext != 0);
	CHECK(pC->pCold != 0);

	CHECK(pB->pNext == pC);

	pA = 0;
	pB = 0;
	pC = 0;

	//-------------------------------------------------------------------
	// Find Key N
	//-------------------------------------------------------------------
	foundFlag = pHotCold->FindKey(0x34294032, pFoundColdNode, pFoundHotNode);
	CHECK(foundFlag == true);

	CHECK(pFoundColdNode->x == 19586.810547f);
	CHECK(pFoundColdNode->y == 4292.119141f);
	CHECK(pFoundColdNode->z == 10789.589844f);
	CHECK(pFoundColdNode->A.x == 12918.946289f);
	CHECK(pFoundColdNode->A.y == 23779.582031f);
	CHECK(pFoundColdNode->A.z == 14188.118164f);
	CHECK(pFoundColdNode->B.x == 11559.238281f);
	CHECK(pFoundColdNode->B.y == 30613.933594f);
	CHECK(pFoundColdNode->B.z == 24460.173828f);
	CHECK(pFoundColdNode->C.x == 29317.390625f);
	CHECK(pFoundColdNode->C.y == 14160.729492f);
	CHECK(pFoundColdNode->C.z == 1408.552246f);
	CHECK(pFoundColdNode->MA.m00 == 32006.439453f);
	CHECK(pFoundColdNode->MA.m01 == 18388.005859f);
	CHECK(pFoundColdNode->MA.m02 == 23946.435547f);
	CHECK(pFoundColdNode->MA.m03 == 364.701904f);
	CHECK(pFoundColdNode->MA.m10 == 13626.305664f);
	CHECK(pFoundColdNode->MA.m11 == 28579.976563f);
	CHECK(pFoundColdNode->MA.m12 == 7011.450195f);
	CHECK(pFoundColdNode->MA.m13 == 19542.003906f);
	CHECK(pFoundColdNode->MA.m20 == 16890.466797f);
	CHECK(pFoundColdNode->MA.m21 == 19261.482422f);
	CHECK(pFoundColdNode->MA.m22 == 32141.587891f);
	CHECK(pFoundColdNode->MA.m23 == 379.837646f);
	CHECK(pFoundColdNode->MA.m30 == 2424.705078f);
	CHECK(pFoundColdNode->MA.m31 == 27507.708984f);
	CHECK(pFoundColdNode->MA.m32 == 23644.017578f);
	CHECK(pFoundColdNode->MA.m33 == 1246.005249f);
	CHECK(pFoundColdNode->MB.m00 == 8397.826172f);
	CHECK(pFoundColdNode->MB.m01 == 10010.328125f);
	CHECK(pFoundColdNode->MB.m02 == 9803.512695f);
	CHECK(pFoundColdNode->MB.m03 == 8645.011719f);
	CHECK(pFoundColdNode->MB.m10 == 24180.228516f);
	CHECK(pFoundColdNode->MB.m11 == 16779.593750f);
	CHECK(pFoundColdNode->MB.m12 == 14967.332031f);
	CHECK(pFoundColdNode->MB.m13 == 14652.976563f);
	CHECK(pFoundColdNode->MB.m20 == 31948.095703f);
	CHECK(pFoundColdNode->MB.m21 == 8482.064453f);
	CHECK(pFoundColdNode->MB.m22 == 21283.724609f);
	CHECK(pFoundColdNode->MB.m23 == 145.169769f);
	CHECK(pFoundColdNode->MB.m30 == 19610.208984f);
	CHECK(pFoundColdNode->MB.m31 == 5567.949707f);
	CHECK(pFoundColdNode->MB.m32 == 50.054504f);
	CHECK(pFoundColdNode->MB.m33 == 20438.171875f);
	CHECK(pFoundColdNode->MC.m00 == 30596.396484f);
	CHECK(pFoundColdNode->MC.m01 == 12104.083984f);
	CHECK(pFoundColdNode->MC.m02 == 12720.560547f);
	CHECK(pFoundColdNode->MC.m03 == 99.660210f);
	CHECK(pFoundColdNode->MC.m10 == 21143.585938f);
	CHECK(pFoundColdNode->MC.m11 == 9253.524414f);
	CHECK(pFoundColdNode->MC.m12 == 21066.730469f);
	CHECK(pFoundColdNode->MC.m13 == 23377.814453f);
	CHECK(pFoundColdNode->MC.m20 == 16577.511719f);
	CHECK(pFoundColdNode->MC.m21 == 18370.771484f);
	CHECK(pFoundColdNode->MC.m22 == 29137.304688f);
	CHECK(pFoundColdNode->MC.m23 == 6144.354980f);
	CHECK(pFoundColdNode->MC.m30 == 9560.022461f);
	CHECK(pFoundColdNode->MC.m31 == 4369.622559f);
	CHECK(pFoundColdNode->MC.m32 == 32699.914063f);
	CHECK(pFoundColdNode->MC.m33 == 27282.207031f);
	CHECK(pFoundColdNode->MD.m00 == 26258.021484f);
	CHECK(pFoundColdNode->MD.m01 == 12550.633789f);
	CHECK(pFoundColdNode->MD.m02 == 5537.316406f);
	CHECK(pFoundColdNode->MD.m03 == 8813.777344f);
	CHECK(pFoundColdNode->MD.m10 == 11.038728f);
	CHECK(pFoundColdNode->MD.m11 == 14617.230469f);
	CHECK(pFoundColdNode->MD.m12 == 20930.294922f);
	CHECK(pFoundColdNode->MD.m13 == 22717.871094f);
	CHECK(pFoundColdNode->MD.m20 == 9538.417969f);
	CHECK(pFoundColdNode->MD.m21 == 20935.417969f);
	CHECK(pFoundColdNode->MD.m22 == 16767.146484f);
	CHECK(pFoundColdNode->MD.m23 == 12015.225586f);
	CHECK(pFoundColdNode->MD.m30 == 29723.132813f);
	CHECK(pFoundColdNode->MD.m31 == 272.140503f);
	CHECK(pFoundColdNode->MD.m32 == 23517.822266f);
	CHECK(pFoundColdNode->MD.m33 == 7479.666992f);
	CHECK((unsigned char)pFoundColdNode->name[0x00] == (unsigned char)0x97);
	CHECK((unsigned char)pFoundColdNode->name[0x01] == (unsigned char)0x06);
	CHECK((unsigned char)pFoundColdNode->name[0x02] == (unsigned char)0xfb);
	CHECK((unsigned char)pFoundColdNode->name[0x03] == (unsigned char)0x4b);
	CHECK((unsigned char)pFoundColdNode->name[0x04] == (unsigned char)0x13);
	CHECK((unsigned char)pFoundColdNode->name[0x05] == (unsigned char)0x75);
	CHECK((unsigned char)pFoundColdNode->name[0x06] == (unsigned char)0x5e);
	CHECK((unsigned char)pFoundColdNode->name[0x07] == (unsigned char)0x88);
	CHECK((unsigned char)pFoundColdNode->name[0x08] == (unsigned char)0x71);
	CHECK((unsigned char)pFoundColdNode->name[0x09] == (unsigned char)0x7e);
	CHECK((unsigned char)pFoundColdNode->name[0x0a] == (unsigned char)0x35);
	CHECK((unsigned char)pFoundColdNode->name[0x0b] == (unsigned char)0x0e);
	CHECK((unsigned char)pFoundColdNode->name[0x0c] == (unsigned char)0x15);
	CHECK((unsigned char)pFoundColdNode->name[0x0d] == (unsigned char)0xe1);
	CHECK((unsigned char)pFoundColdNode->name[0x0e] == (unsigned char)0xc3);
	CHECK((unsigned char)pFoundColdNode->name[0x0f] == (unsigned char)0x4c);
	CHECK((unsigned char)pFoundColdNode->name[0x10] == (unsigned char)0xdb);
	CHECK((unsigned char)pFoundColdNode->name[0x11] == (unsigned char)0xd6);
	CHECK((unsigned char)pFoundColdNode->name[0x12] == (unsigned char)0x2d);
	CHECK((unsigned char)pFoundColdNode->name[0x13] == (unsigned char)0xbc);
	CHECK((unsigned char)pFoundColdNode->name[0x14] == (unsigned char)0x64);
	CHECK((unsigned char)pFoundColdNode->name[0x15] == (unsigned char)0x10);
	CHECK((unsigned char)pFoundColdNode->name[0x16] == (unsigned char)0xf8);
	CHECK((unsigned char)pFoundColdNode->name[0x17] == (unsigned char)0xaf);
	CHECK((unsigned char)pFoundColdNode->name[0x18] == (unsigned char)0xca);
	CHECK((unsigned char)pFoundColdNode->name[0x19] == (unsigned char)0x4a);
	CHECK((unsigned char)pFoundColdNode->name[0x1a] == (unsigned char)0x73);
	CHECK((unsigned char)pFoundColdNode->name[0x1b] == (unsigned char)0xf6);
	CHECK((unsigned char)pFoundColdNode->name[0x1c] == (unsigned char)0xbb);
	CHECK((unsigned char)pFoundColdNode->name[0x1d] == (unsigned char)0x6b);
	CHECK((unsigned char)pFoundColdNode->name[0x1e] == (unsigned char)0x65);
	CHECK((unsigned char)pFoundColdNode->name[0x1f] == (unsigned char)0x91);
	CHECK((unsigned char)pFoundColdNode->name[0x20] == (unsigned char)0x6b);
	CHECK((unsigned char)pFoundColdNode->name[0x21] == (unsigned char)0xf1);
	CHECK((unsigned char)pFoundColdNode->name[0x22] == (unsigned char)0x48);
	CHECK((unsigned char)pFoundColdNode->name[0x23] == (unsigned char)0xd7);
	CHECK((unsigned char)pFoundColdNode->name[0x24] == (unsigned char)0x3b);
	CHECK((unsigned char)pFoundColdNode->name[0x25] == (unsigned char)0x45);
	CHECK((unsigned char)pFoundColdNode->name[0x26] == (unsigned char)0x81);
	CHECK((unsigned char)pFoundColdNode->name[0x27] == (unsigned char)0x26);
	CHECK((unsigned char)pFoundColdNode->name[0x28] == (unsigned char)0xba);
	CHECK((unsigned char)pFoundColdNode->name[0x29] == (unsigned char)0x10);
	CHECK((unsigned char)pFoundColdNode->name[0x2a] == (unsigned char)0xc1);
	CHECK((unsigned char)pFoundColdNode->name[0x2b] == (unsigned char)0x03);
	CHECK((unsigned char)pFoundColdNode->name[0x2c] == (unsigned char)0xbd);
	CHECK((unsigned char)pFoundColdNode->name[0x2d] == (unsigned char)0x4c);
	CHECK((unsigned char)pFoundColdNode->name[0x2e] == (unsigned char)0x8a);
	CHECK((unsigned char)pFoundColdNode->name[0x2f] == (unsigned char)0x69);
	CHECK((unsigned char)pFoundColdNode->name[0x30] == (unsigned char)0xa6);
	CHECK((unsigned char)pFoundColdNode->name[0x31] == (unsigned char)0xa4);
	CHECK((unsigned char)pFoundColdNode->name[0x32] == (unsigned char)0x0a);
	CHECK((unsigned char)pFoundColdNode->name[0x33] == (unsigned char)0x7c);
	CHECK((unsigned char)pFoundColdNode->name[0x34] == (unsigned char)0xc3);
	CHECK((unsigned char)pFoundColdNode->name[0x35] == (unsigned char)0x47);
	CHECK((unsigned char)pFoundColdNode->name[0x36] == (unsigned char)0x3d);
	CHECK((unsigned char)pFoundColdNode->name[0x37] == (unsigned char)0x6b);
	CHECK((unsigned char)pFoundColdNode->name[0x38] == (unsigned char)0xbb);
	CHECK((unsigned char)pFoundColdNode->name[0x39] == (unsigned char)0x5b);
	CHECK((unsigned char)pFoundColdNode->name[0x3a] == (unsigned char)0x1b);
	CHECK((unsigned char)pFoundColdNode->name[0x3b] == (unsigned char)0xd7);
	CHECK((unsigned char)pFoundColdNode->name[0x3c] == (unsigned char)0xf2);
	CHECK((unsigned char)pFoundColdNode->name[0x3d] == (unsigned char)0xab);
	CHECK((unsigned char)pFoundColdNode->name[0x3e] == (unsigned char)0x23);
	CHECK((unsigned char)pFoundColdNode->name[0x3f] == (unsigned char)0xdd);
	CHECK((unsigned char)pFoundColdNode->name[0x40] == (unsigned char)0xee);
	CHECK((unsigned char)pFoundColdNode->name[0x41] == (unsigned char)0xc0);
	CHECK((unsigned char)pFoundColdNode->name[0x42] == (unsigned char)0x9e);
	CHECK((unsigned char)pFoundColdNode->name[0x43] == (unsigned char)0x36);
	CHECK((unsigned char)pFoundColdNode->name[0x44] == (unsigned char)0x1a);
	CHECK((unsigned char)pFoundColdNode->name[0x45] == (unsigned char)0x76);
	CHECK((unsigned char)pFoundColdNode->name[0x46] == (unsigned char)0xf4);
	CHECK((unsigned char)pFoundColdNode->name[0x47] == (unsigned char)0xfa);
	CHECK((unsigned char)pFoundColdNode->name[0x48] == (unsigned char)0x69);
	CHECK((unsigned char)pFoundColdNode->name[0x49] == (unsigned char)0xc8);
	CHECK((unsigned char)pFoundColdNode->name[0x4a] == (unsigned char)0xcf);
	CHECK((unsigned char)pFoundColdNode->name[0x4b] == (unsigned char)0x0f);
	CHECK((unsigned char)pFoundColdNode->name[0x4c] == (unsigned char)0x4f);
	CHECK((unsigned char)pFoundColdNode->name[0x4d] == (unsigned char)0x63);
	CHECK((unsigned char)pFoundColdNode->name[0x4e] == (unsigned char)0x07);
	CHECK((unsigned char)pFoundColdNode->name[0x4f] == (unsigned char)0xb7);
	CHECK((unsigned char)pFoundColdNode->name[0x50] == (unsigned char)0x72);
	CHECK((unsigned char)pFoundColdNode->name[0x51] == (unsigned char)0x2d);
	CHECK((unsigned char)pFoundColdNode->name[0x52] == (unsigned char)0xf3);
	CHECK((unsigned char)pFoundColdNode->name[0x53] == (unsigned char)0xd1);
	CHECK((unsigned char)pFoundColdNode->name[0x54] == (unsigned char)0x9b);
	CHECK((unsigned char)pFoundColdNode->name[0x55] == (unsigned char)0x68);
	CHECK((unsigned char)pFoundColdNode->name[0x56] == (unsigned char)0xc6);
	CHECK((unsigned char)pFoundColdNode->name[0x57] == (unsigned char)0x4d);
	CHECK((unsigned char)pFoundColdNode->name[0x58] == (unsigned char)0xd9);
	CHECK((unsigned char)pFoundColdNode->name[0x59] == (unsigned char)0x8f);
	CHECK((unsigned char)pFoundColdNode->name[0x5a] == (unsigned char)0xde);
	CHECK((unsigned char)pFoundColdNode->name[0x5b] == (unsigned char)0xcb);
	CHECK((unsigned char)pFoundColdNode->name[0x5c] == (unsigned char)0x32);
	CHECK((unsigned char)pFoundColdNode->name[0x5d] == (unsigned char)0x0c);
	CHECK((unsigned char)pFoundColdNode->name[0x5e] == (unsigned char)0x4b);
	CHECK((unsigned char)pFoundColdNode->name[0x5f] == (unsigned char)0x87);
	CHECK((unsigned char)pFoundColdNode->name[0x60] == (unsigned char)0x7f);
	CHECK((unsigned char)pFoundColdNode->name[0x61] == (unsigned char)0x77);
	CHECK((unsigned char)pFoundColdNode->name[0x62] == (unsigned char)0x09);
	CHECK((unsigned char)pFoundColdNode->name[0x63] == (unsigned char)0x6a);
	CHECK((unsigned char)pFoundColdNode->name[0x64] == (unsigned char)0x3c);
	CHECK((unsigned char)pFoundColdNode->name[0x65] == (unsigned char)0x7f);
	CHECK((unsigned char)pFoundColdNode->name[0x66] == (unsigned char)0x74);
	CHECK((unsigned char)pFoundColdNode->name[0x67] == (unsigned char)0x70);
	CHECK((unsigned char)pFoundColdNode->name[0x68] == (unsigned char)0x64);
	CHECK((unsigned char)pFoundColdNode->name[0x69] == (unsigned char)0x95);
	CHECK((unsigned char)pFoundColdNode->name[0x6a] == (unsigned char)0xb8);
	CHECK((unsigned char)pFoundColdNode->name[0x6b] == (unsigned char)0xc5);
	CHECK((unsigned char)pFoundColdNode->name[0x6c] == (unsigned char)0xb3);
	CHECK((unsigned char)pFoundColdNode->name[0x6d] == (unsigned char)0x92);
	CHECK((unsigned char)pFoundColdNode->name[0x6e] == (unsigned char)0x14);
	CHECK((unsigned char)pFoundColdNode->name[0x6f] == (unsigned char)0xbc);
	CHECK((unsigned char)pFoundColdNode->name[0x70] == (unsigned char)0x50);
	CHECK((unsigned char)pFoundColdNode->name[0x71] == (unsigned char)0x62);
	CHECK((unsigned char)pFoundColdNode->name[0x72] == (unsigned char)0x39);
	CHECK((unsigned char)pFoundColdNode->name[0x73] == (unsigned char)0xfb);
	CHECK((unsigned char)pFoundColdNode->name[0x74] == (unsigned char)0xcc);
	CHECK((unsigned char)pFoundColdNode->name[0x75] == (unsigned char)0xf3);
	CHECK((unsigned char)pFoundColdNode->name[0x76] == (unsigned char)0x34);
	CHECK((unsigned char)pFoundColdNode->name[0x77] == (unsigned char)0x16);
	CHECK((unsigned char)pFoundColdNode->name[0x78] == (unsigned char)0xfb);
	CHECK((unsigned char)pFoundColdNode->name[0x79] == (unsigned char)0x7e);
	CHECK((unsigned char)pFoundColdNode->name[0x7a] == (unsigned char)0x1b);
	CHECK((unsigned char)pFoundColdNode->name[0x7b] == (unsigned char)0x5f);
	CHECK((unsigned char)pFoundColdNode->name[0x7c] == (unsigned char)0xf4);
	CHECK((unsigned char)pFoundColdNode->name[0x7d] == (unsigned char)0xc1);
	CHECK((unsigned char)pFoundColdNode->name[0x7e] == (unsigned char)0x5f);
	CHECK((unsigned char)pFoundColdNode->name[0x7f] == (unsigned char)0x00);

	CHECK(pFoundHotNode->key == 0x34294032);
	CHECK(pFoundHotNode->pCold == pFoundColdNode);
	CHECK(pFoundColdNode->pHot == pFoundHotNode);


	HotNode *pR = pFoundHotNode;

	CHECK(pR != 0);

	CHECK(pR->key == 0x34294032);
	CHECK(pR->pPrev != 0);
	CHECK(pR->pNext == 0);
	CHECK(pR->pCold == pFoundColdNode);

	HotNode *pS = pR->pPrev;
	CHECK(pS != 0);

	CHECK(pS->key == 0x5E300126);
	CHECK(pS->pPrev != 0);
	CHECK(pS->pNext == pR);
	CHECK(pS->pCold != 0);

	HotNode *pT = pS->pPrev;
	CHECK(pT != 0);

	CHECK(pT->key == 0x120f49fe);
	CHECK(pT->pPrev != 0);
	CHECK(pT->pNext == pS);
	CHECK(pT->pCold != 0);

	CHECK(pS->pPrev == pT);

	pR = 0;
	pS = 0;
	pT = 0;
	
} TEST_END

TEST_TEARDOWN(Link, HotCold)
{
	delete pHotCold;
}
#endif

// End of File
