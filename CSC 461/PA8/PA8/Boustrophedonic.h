//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef BOUSTROPHEDIC_H
#define BOUSTROPHEDIC_H

#include "Node.h"

void Remove(Node *&head, int row, int col);

// Add extra methods here (if desired):
enum Direction
{
	NORTH,
	EAST,
	WEST,
	SOUTH
};

Node *getNextNode(Node *pCurrentNode);
Node *getSouthernNode(Node *pCurrentNode);
void updateLocation(int &currCol, int &currRow, Node *pCurrentNode, Node *pNextNode);

#endif


// ---  End of File ---------------
