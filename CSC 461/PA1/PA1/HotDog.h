//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------- 

#ifndef HOTDOG_H
#define HOTDOG_H

// Add files include as needed
#include "Condiments.h"

class HotDog
{
public:
	//big four
	HotDog();
	~HotDog() = default;
	HotDog(const HotDog &tmp);
	void operator=(const HotDog &tmp);
	 
	// Public Methods (Required)
	void Minus(Condiments condiment);
	void Add(Condiments condiment);

	// Methods for Testing and Internals (Required)
	int GetCondiments();
	HotDog *GetNext();
	HotDog *GetPrev();
	void SetNext(HotDog *pDog);
	void SetPrev(HotDog *pDog);


private:
	int condiments;
	HotDog *next;
	HotDog *prev;
};

#endif

// ---  End of File ---------------
