//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------- 

#include "Framework.h"
#include "Stand.h"

// place holder for compiling purposes
// In each method replace with your code
#define STUB_PLEASE_REPLACE(x) (x)

// Methods
Stand::Stand()
{
	this->orderCount = 0;
	this->peakOrderCount = 0;
	this->head = 0;
}

Stand::~Stand()
{
	while (this->head != 0)
	{
		Order *nextOrder = this->head->GetNext();
		delete this->head;
		this->head = nextOrder;
	}
}

Stand::Stand(const Stand &tmp)
{
	this->orderCount = tmp.orderCount;
	this->peakOrderCount = tmp.orderCount;
	this->head = tmp.head;
}

void Stand::operator=(const Stand &tmp)
{
	this->orderCount = tmp.orderCount;
	this->peakOrderCount = tmp.orderCount;
	this->head = tmp.head;
}

int Stand::GetCurrOrders()
{
	return orderCount;
}

int Stand::GetPeakOrders()
{
	return peakOrderCount;
}

Order *Stand::GetHead()
{
	return this->head;
}

void Stand::Remove(Name name)
{
	Order *current = this->head;
	while (current != 0)
	{
		if (current->GetName() == name)
		{
			if (current->GetPrev() != 0) { current->GetPrev()->SetNext(current->GetNext()); }
			if (current->GetNext() != 0) { current->GetNext()->SetPrev(current->GetPrev()); }
			if (current->GetPrev() == 0) { this->head = current->GetNext(); }
			Order *prevOrder = current;
			current = current->GetNext();
			delete prevOrder;
			this->orderCount--;
		}
		else
		{
			current = current->GetNext();
		}
	}
}

void Stand::Add(Order *pOrder)
{
	if (this->head == 0)
	{
		this->head = pOrder;
	}
	else
	{
		Order *current = this->head;
		while (current->GetNext() != 0)
		{
			current = current->GetNext();
		}

		current->SetNext(pOrder);
	}

	this->orderCount++;
	if (this->orderCount > this->peakOrderCount) { this->peakOrderCount = this->orderCount; }
}

// ---  End of File ---------------

