//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------- 

#ifndef STAND_H
#define STAND_H

// Add files include as needed
#include "Names.h"
#include "Order.h"

class Stand
{
public:
	//big four
	Stand();
	~Stand();
	Stand(const Stand &tmp);
	void operator=(const Stand &tmp);

	// Public Methods (Required)
	void Remove(Name name);
	void Add(Order *pOrder);
	int GetCurrOrders();
	int GetPeakOrders();
	
	// Methods used for Testing and Internals (Required)
	Order *GetHead();

private:
	Order *head;
	int orderCount;
	int peakOrderCount;
};

#endif

// ---  End of File ---------------
