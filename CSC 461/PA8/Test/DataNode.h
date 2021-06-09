//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

#ifndef DATANODE_H
#define DATANODE_H

#include "Node.h"

struct DataNode : public Node
{
public:

	enum class Direction
	{
		East,
		West
	};

	int row;
	int col;

	DataNode(int _row, int _col);
	DataNode(const DataNode &) = delete;
	DataNode &operator = (const DataNode &) = delete;
	~DataNode();

	void Print();

	void Set(DataNode *pN, DataNode *pS, DataNode *pE, DataNode *pW);
	void Walk();

private:
	void privPrintNorth();
	void privPrintSouth();
	void privPrintEast();
	void privPrintWest();

};

#endif

// ---  End of File ---------------
