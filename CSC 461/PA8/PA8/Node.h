//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef NODE_H
#define NODE_H

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

struct Node
{	
public:
	Node();
	Node(const Node &) = delete;
	Node &operator = (const Node &) = delete;
	~Node();
	
// data:
	Node *pNorth;
	Node *pSouth;
	Node *pEast;
	Node *pWest;
};

#endif

// ---  End of File ---------------
