//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Framework.h"
#include "_UnitTestConfiguration.h"

#include "Boustrophedonic.h"
#include "Tree.h"

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

static Tree *pTree = nullptr;

#if Delete00_Test_Enable

TEST_WITH_TEARDOWN(Delete00, Basic, Delete00_Test_Enable)
{
	pTree = new Tree();

	DataNode *pN00, *pN01;
	DataNode *pN10, *pN11;


	pTree->GetPointers(pTree->pHead,
					   pN00, pN01, 
					   pN10, pN11 );

	pTree->SkipThisOne = Tree::SkipDelete::N00;

	// Make sure we have a good initial tree

	//-----------------------------------
	CHECK_EQUAL(pN00->pNorth, nullptr);
	CHECK_EQUAL(pN00->pSouth, nullptr);
	CHECK_EQUAL(pN00->pEast, pN01);
	CHECK_EQUAL(pN00->pWest, nullptr);

	CHECK_EQUAL(pN01->pNorth, nullptr);
	CHECK_EQUAL(pN01->pSouth, pN11);
	CHECK_EQUAL(pN01->pEast, nullptr);
	CHECK_EQUAL(pN01->pWest, nullptr);

	//---------------------------------

	CHECK_EQUAL(pN11->pNorth, nullptr);
	CHECK_EQUAL(pN11->pSouth, nullptr);
	CHECK_EQUAL(pN11->pEast, nullptr);
	CHECK_EQUAL(pN11->pWest, pN10);

	CHECK_EQUAL(pN10->pNorth, pN00);
	CHECK_EQUAL(pN10->pSouth, nullptr);
	CHECK_EQUAL(pN10->pEast, nullptr);
	CHECK_EQUAL(pN10->pWest, nullptr);


	//---- TEST below here --------------------

	Trace::out("remove:---> (0,0) \n");
	Node *p = pTree->pHead;
	Remove(p, 0, 0);

	// ------- CHECK HEAD ---------------------

	DataNode *pData = (DataNode *)p;
	CHECK_EQUAL(pData, pN01);

	//-----------------------------------

	CHECK_EQUAL(pN01->pNorth, nullptr);
	CHECK_EQUAL(pN01->pSouth, pN11);
	CHECK_EQUAL(pN01->pEast, nullptr);
	CHECK_EQUAL(pN01->pWest, nullptr);

	//---------------------------------

	CHECK_EQUAL(pN11->pNorth, nullptr);
	CHECK_EQUAL(pN11->pSouth, nullptr);
	CHECK_EQUAL(pN11->pEast, nullptr);
	CHECK_EQUAL(pN11->pWest, pN10);

	CHECK_EQUAL(pN10->pNorth, nullptr);
	CHECK_EQUAL(pN10->pSouth, nullptr);
	CHECK_EQUAL(pN10->pEast, nullptr);
	CHECK_EQUAL(pN10->pWest, nullptr);


} TEST_END


TEST_TEARDOWN(Delete00, Basic)
{
	delete pTree;
}

#endif

// ---  End of File ---------------
