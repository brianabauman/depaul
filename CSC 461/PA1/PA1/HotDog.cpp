//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------- 

#include "Framework.h"

#include "HotDog.h"

// place holder for compiling purposes
// In each method replace with your code
#define STUB_PLEASE_REPLACE(x) (x)

// Methods

HotDog::HotDog()
{
	this->condiments = 0;
	this->prev = 0;
	this->next = 0;
}

HotDog::HotDog(const HotDog &tmp)
{
	this->condiments = tmp.condiments;
	this->next = 0;
	this->prev = 0;
}

void HotDog::operator=(const HotDog &tmp)
{
	this->condiments = tmp.condiments;
	this->next = 0;
	this->prev = 0;
}

void HotDog::Minus(Condiments condiment)
{
	// Only use bit-wise operations
	this->condiments &= ~(int)condiment;
}

void HotDog::Add(Condiments condiment)
{
	// Only use bit-wise operations
	this->condiments |= (int)condiment;
}

int HotDog::GetCondiments()
{
	return this->condiments;
}

HotDog *HotDog::GetNext()
{
	return this->next;
}

HotDog *HotDog::GetPrev()
{
	return this->prev;;
}

void HotDog::SetNext(HotDog *pDog)
{
	this->next = pDog;
	if (pDog != 0) { pDog->SetPrev(this); }
}

void HotDog::SetPrev(HotDog *pDog)
{
	this->prev = pDog;
}


// ---  End of File ---------------

