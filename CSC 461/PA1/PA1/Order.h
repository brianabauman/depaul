//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------- 

#ifndef ORDER_H
#define ORDER_H

// Add files include as needed
#include "HotDog.h"
#include "Names.h"

class Order 
{
public:
	//big four
	Order();
	~Order();
	Order(const Order &tmp);
	void operator=(const Order &tmp);

	// Public Methods (Required)
	Order(Name name);
	Name GetName();
	void SetName(Name name);
	void Add(HotDog *pDog);
	void Remove(HotDog *pDog);

	// Methods used for Testing and Internals (Required)
	HotDog *GetHead();
	Order *GetNext();
	Order *GetPrev();
	void SetNext(Order *pOrder);
	void SetPrev(Order *pOrder);


private:
	Name name;
	HotDog *head;
	Order *next;
	Order *prev;
};

#endif

// ---  End of File ---------------
