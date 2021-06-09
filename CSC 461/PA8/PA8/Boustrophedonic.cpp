//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include <assert.h>
#include <stdio.h>

#include "Trace.h"
#include "Boustrophedonic.h"

#define UNUSED_VAR(v) ((void *)v)

void Remove(Node *&pHead, int row, int col)
{
	Node *pCurrentNode = pHead;
	Node *pFoundNode = nullptr;
	Node *pNextNode = nullptr;
	Node *pNorthernNode = nullptr;
	Node *pEasternNode = nullptr;
	Node *pSouthernNode = nullptr;
	Node *pWesternNode = nullptr;

	int currCol = 0;
	int currRow = 0;

	while (pCurrentNode != nullptr &&
		   ((currCol != col) || (currRow != row)))
	{		
		//attempt to remember interesting nodes
		if (currCol == col && currRow == row - 1) pNorthernNode = pCurrentNode;
		else if (currRow == row && currCol == col - 1) pWesternNode = pCurrentNode;
		else if (currRow == row && currCol == col + 1) pEasternNode = pCurrentNode;

		//get the next node
		pNextNode = getNextNode(pCurrentNode);

		//update distances to destination node
		if (pNextNode != nullptr) updateLocation(currCol, currRow, pCurrentNode, pNextNode);
		pCurrentNode = pNextNode;
	}

	if (pCurrentNode != nullptr)
	{
		//we found 'er
		pFoundNode = pCurrentNode;
		pNextNode = getNextNode(pFoundNode);
		if (pWesternNode == nullptr) pWesternNode = pFoundNode->pWest;
		if (pEasternNode == nullptr) pEasternNode = pFoundNode->pEast;
		pSouthernNode = getSouthernNode(pFoundNode);
		
		//clean up links
		if (pWesternNode != nullptr) pWesternNode->pEast = pFoundNode->pEast;
		if (pEasternNode != nullptr) pEasternNode->pWest = pFoundNode->pWest;
		if (pNorthernNode != nullptr && pNorthernNode->pSouth != nullptr) pNorthernNode->pSouth = pSouthernNode;
		if (pSouthernNode != nullptr && pSouthernNode->pNorth != nullptr) pSouthernNode->pNorth = pNorthernNode;

		delete pFoundNode;
	}

	if (pFoundNode == pHead) pHead = pNextNode;
};

Node *getNextNode(Node *pCurrentNode)
{
	Node *pNextNode = nullptr;

	if (pCurrentNode->pEast != nullptr) pNextNode = pCurrentNode->pEast;
	else if (pCurrentNode->pWest != nullptr) pNextNode = pCurrentNode->pWest;
	else pNextNode = pCurrentNode->pSouth;

	return pNextNode;
}

//make for other directions?
Node *getSouthernNode(Node *pCurrentNode)
{
	Node *pSouthernNode = nullptr;

	if (pCurrentNode->pSouth != nullptr) pSouthernNode = pCurrentNode->pSouth;
	else
	{
		Node *pNextNode = getNextNode(pCurrentNode);
		if (pNextNode != nullptr && pNextNode->pSouth != nullptr) pSouthernNode = getNextNode(pNextNode->pSouth);
	}

	return pSouthernNode;
}

void updateLocation(int &currentCol, int &currentRow, Node *pCurrentNode, Node *pNextNode)
{
	if (pNextNode == pCurrentNode->pNorth) currentRow--;
	else if (pNextNode == pCurrentNode->pWest) currentCol--;
	else if (pNextNode == pCurrentNode->pSouth) currentRow++;
	else if (pNextNode == pCurrentNode->pEast) currentCol++;
};
// ---  End of File ---------------
