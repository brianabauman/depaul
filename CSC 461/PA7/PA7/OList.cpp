//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "OList.h"
#include "Node.h"
#include "Trace.h"

#define UNUSED_VAR(x) (void *)x

// ----------------------------------
// -----> MODIFY This FILE <---------
// ----------------------------------

void OList::SetCutoffLength()
{
	// Yes HARD code your cutoff
	// CHANGE this number, by running experiments to find best value
	this->mCutoffLength = 40;
}

OList::OList(const char * const pFileName, const int numNodes)
{
	// Leave the next 5 lines...
	this->SetCutoffLength();
	this->pHead = nullptr;
	this->mCutoffLength = this->GetCutoffLength();
	this->NumNodes = numNodes;
	this->privFunctor = nullptr;

	// Do your magic here:

	// Create the Linked List... You cannot use the original code
	// The input file, and numNodes is all you need to recreate the OList

	// Hint: Open the file, read and create new nodes, 
	//       fill them with the data from the file

	// Grads - You need to do the Load-In-Place technique
	//         You cannot have more than 2 new functions in this method

	// Ungrads - You need to store the data and reconstruct the linked list
	//           You can use as many new/deletes as needed

	// Everyone - Fill in your CustomDestructCommand::Command() that will be used 
	//            in the destructor.

	// Quick sample code... remove this code and replace with your own

	FILE *pFileHandle;

	assert(pFileName);
	pFileHandle = fopen(pFileName, "rb");

	Node *buffer = new Node[(unsigned int)numNodes];
	size_t numBytesRead = fread(buffer, 1, (size_t)numNodes * sizeof(Node), pFileHandle);

	fclose(pFileHandle);

	int nodesParsed = 0;
	Node *pCurrentNode = nullptr;
	while (nodesParsed < numNodes)
	{
		pCurrentNode = (Node *)(buffer + nodesParsed);
		pCurrentNode->pNext = pCurrentNode + 1;
		pCurrentNode->pPrev = pCurrentNode - 1;
		nodesParsed++;
	}
	pCurrentNode->pNext = nullptr;

	this->pHead = buffer;
	this->pHead->pPrev = nullptr;
}

void OList::WriteToFile(const char * const pFileName)
{
	FILE *pFileHandle = nullptr;

	assert(pFileName);
	pFileHandle = fopen(pFileName, "wb");

	Node *buffer = new Node[(unsigned int)this->NumNodes];

	int count = 0;
	Node *pCurrentNode = this->pHead;
	while (pCurrentNode != nullptr)
	{
		memcpy(buffer + count, pCurrentNode, sizeof(Node));
		pCurrentNode = pCurrentNode->pNext;
		count++;
	}

	size_t numBytesWritten = fwrite(buffer, 1, (size_t)this->NumNodes * sizeof(Node), pFileHandle);
	assert(numBytesWritten == sizeof(Node) * this->NumNodes);

	fclose(pFileHandle);
	delete buffer;
}

void OList::InsertionSort()
{
	insertionSortHelper(&(this->pHead));
}

void OList::MergeSort()
{
	mergeSortHelper(&(this->pHead));
}

void OList::MergeComboSort(int CutoffLength)
{
	mergeComboSortHelper(&this->pHead, CutoffLength);
}

void OList::insertionSortHelper(Node **pList)
{
	//from: https://www.geeksforgeeks.org/insertion-sort-for-singly-linked-list/

	// Initialize sorted linked list 
	Node *pSortedHead = nullptr;

	// Traverse the given linked list and insert every node to sorted 
	Node *current = *pList;
	while (current != nullptr)
	{
		// Store next for next iteration 
		Node *next = current->pNext;

		// insert current in sorted linked list 
		this->sortedInsert(&pSortedHead, current);

		// Update current 
		current = next;
	}

	// Update head_ref to point to sorted linked list 
	this->pHead = pSortedHead;
}

void OList::sortedInsert(Node **pSortedHead, Node *pNewNode)
{
	//from: https://www.geeksforgeeks.org/insertion-sort-for-singly-linked-list/

	Node *current;
	/* Special case for the head end */
	if (*pSortedHead == nullptr)
	{
		pNewNode->pNext = *pSortedHead;
		pNewNode->pPrev = nullptr;
		*pSortedHead = pNewNode;
	}
	else if ((*pSortedHead)->key >= pNewNode->key)
	{
		pNewNode->pNext = *pSortedHead;
		pNewNode->pPrev = nullptr;
		(*pSortedHead)->pPrev = pNewNode;
		*pSortedHead = pNewNode;
	}
	else
	{
		/* Locate the node before the point of insertion */
		current = *pSortedHead;
		while (current->pNext != nullptr &&
			   current->pNext->key < pNewNode->key)
		{
			current = current->pNext;
		}

		if (current->pNext != nullptr) current->pNext->pPrev = pNewNode;
		pNewNode->pNext = current->pNext;
		current->pNext = pNewNode;
		pNewNode->pPrev = current;
	}
}

void OList::mergeSortHelper(Node **pList)
{
	Node* a;
	Node* b;

	/* Base case -- length 0 or 1 */
	if ((*pList == nullptr) || ((*pList)->pNext == nullptr)) return;

	/* Split head into 'a' and 'b' sublists */
	frontBackSplit(*pList, &a, &b);

	/* Recursively sort the sublists */
	mergeSortHelper(&a);
	mergeSortHelper(&b);

	/* answer = merge the two sorted lists together */
	*pList = sortedMerge(a, b);
}

void OList::frontBackSplit(Node* source, Node** frontRef, Node** backRef)
{
	Node* fast;
	Node* slow;
	slow = source;
	fast = source->pNext;

	/* Advance 'fast' two nodes, and advance 'slow' one node */
	while (fast != nullptr)
	{
		fast = fast->pNext;
		if (fast != nullptr)
		{
			slow = slow->pNext;
			fast = fast->pNext;
		}
	}

	/* 'slow' is before the midpoint in the list, so split it in two
	at that point. */
	*frontRef = source;
	*backRef = slow->pNext;
	slow->pNext = nullptr;
}

Node* OList::sortedMerge(Node* a, Node* b)
{
	Node* result = nullptr;

	/* Base cases */
	if (a == nullptr)
	{
		b->pPrev = nullptr;
		return b;
	}
	else if (b == nullptr)
	{
		a->pPrev = nullptr;
		return a;
	}

	/* Pick either a or b, and recurse */
	if (a->key <= b->key)
	{
		result = a;
		result->pNext = sortedMerge(a->pNext, b);
		if (result->pNext != nullptr) result->pNext->pPrev = a;
	}
	else
	{
		result = b;
		result->pNext = sortedMerge(a, b->pNext);
		if (result->pNext != nullptr) result->pNext->pPrev = b;
	}

	result->pPrev = nullptr;
	return result;
}

void OList::mergeComboSortHelper(Node **pList, int CutoffLength)
{
	//cout total nodes and decide how to sort
	int count = 0;
	Node *pCurrentNode = *pList;
	while (pCurrentNode != nullptr && count <= CutoffLength)
	{
		count++;
		pCurrentNode = pCurrentNode->pNext;
	}

	if (count <= CutoffLength)
	{ //insertion sort!
		insertionSortHelper(pList);
	}
	else
	{ //merge sort!
		mergeSortHelper(pList);
	}
}

// ---  End of File ---------------
