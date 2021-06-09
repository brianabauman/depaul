//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
//
// NO HEADERS... do the problem in this CPP file
//
// Do Problem 3 here:
//
// ---------------------------------------------------------------------------

typedef struct LinkList 
{ 
	struct LinkList *next; 
	struct LinkList *prev; 
	struct ImportantData *data; 
} LinkList_t;

LinkList_t *headList;

enum ResultCode
{
	SUCCESS,
	GENERIC_FAILURE,
	NODE_NOT_FOUND,
	EMPTY_LIST
};

struct ImportantData
{
	int x;
};

ResultCode removeNode(LinkList_t *&pList, ImportantData *pData)
{
	ResultCode rtnCd = GENERIC_FAILURE;
	if (pList == nullptr) return EMPTY_LIST;

	LinkList *pCurrentNode = pList;
	while (pCurrentNode != nullptr)
	{
		if (pCurrentNode->data == pData)
		{
			if (pCurrentNode->prev != nullptr) pCurrentNode->prev->next = pCurrentNode->next;
			else pList = pCurrentNode->next;

			if (pCurrentNode->next != nullptr) pCurrentNode->next->prev = pCurrentNode->prev;

			rtnCd = SUCCESS;
			break;
		}
		else pCurrentNode = pCurrentNode->next;
	}

	if (pCurrentNode == nullptr) rtnCd = NODE_NOT_FOUND;
	else delete pCurrentNode;

	return rtnCd;
}


// End of File
