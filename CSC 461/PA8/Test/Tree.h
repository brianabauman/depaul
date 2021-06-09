//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

#ifndef TREE_H
#define TREE_H

#include "Node.h"
#include "DataNode.h"

struct Tree
{
public:
		
	enum SkipDelete
	{
		N00,
		N01,
		N10,
		N11
	};


	Tree();
	Tree(const Tree &) = delete;
	Tree &operator = (const Tree &) = delete;
	~Tree();

	DataNode *pN00;
	DataNode *pN01;
	DataNode *pN10;
	DataNode *pN11;


	SkipDelete SkipThisOne;

	void GetPointers(DataNode *pHead,
					 DataNode *&pN00,
					 DataNode *&pN01,
					 DataNode *&pN10,
					 DataNode *&pN11);


private:
	DataNode *privCreateTree();

public:
	DataNode *pHead;
};

#endif

// ---  End of File ---------------
