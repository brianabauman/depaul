//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------- 

#include "Framework.h"
#include "Order.h"

// place holder for compiling purposes
// In each method replace with your code
// Just delete the Stub and code code code
#define STUB_PLEASE_REPLACE(x) (x)

// Methods

Order::Order()
{
	this->name = Name::Unknown;
	this->head = 0;
	this->next = 0;
	this->prev = 0;
}

Order::~Order()
{
	while (this->head != 0)
	{
		HotDog *nextHotDog = this->head->GetNext();
		delete this->head;
		this->head = nextHotDog;
	}
}

Order::Order(const Order &tmp)
{
	this->name = tmp.name;
	this->next = tmp.next;
	this->prev = tmp.prev;

	this->head = new HotDog(*tmp.head);
	HotDog *tmpCurrent = tmp.head;
	HotDog *current = this->head;
	while (tmpCurrent->GetNext() != 0)
	{
		tmpCurrent = tmpCurrent->GetNext();
		current->SetNext(new HotDog(*tmpCurrent));
		current->GetNext()->SetPrev(current);
		current = current->GetNext();
	}
}

void Order::operator=(const Order &tmp)
{
	this->name = tmp.name;
	this->next = tmp.next;
	this->prev = tmp.prev;

	this->head = new HotDog(*tmp.head);
	HotDog *tmpCurrent = tmp.head;
	HotDog *current = this->head;
	while (tmpCurrent->GetNext() != 0)
	{
		tmpCurrent = tmpCurrent->GetNext();
		current->SetNext(new HotDog(*tmpCurrent));
		current->GetNext()->SetPrev(current);
		current = current->GetNext();
	}
}

Order::Order(Name name)
{
	this->name = name;
	this->head = 0;
	this->next = 0;
	this->prev = 0;
}

void Order::Add(HotDog *p)
{
	if (this->head == 0)
	{
		this->head = p;
	}
	else
	{
		HotDog *current = this->head;
		while (current->GetNext() != 0)
		{
			current = current->GetNext();
		}

		current->SetNext(p);
	}
}

void Order::Remove(HotDog *p)
{
	HotDog *current = this->head;
	while (current != 0)
	{
		if (p == current)
		{
			if (current->GetPrev() != 0) { current->GetPrev()->SetNext(current->GetNext()); }
			if (current->GetNext() != 0) { current->GetNext()->SetPrev(current->GetPrev()); }
			if (current->GetPrev() == 0) { this->head = current->GetNext(); }
			delete p;
			break;
		}
		current = current->GetNext();
	}
}

Order *Order::GetNext()
{
	return next;
}

Order *Order::GetPrev()
{
	return prev;
}

HotDog *Order::GetHead()
{
	return head;
}

void Order::SetNext(Order *p)
{
	this->next = p;
	if (p != 0) { p->SetPrev(this); }
}

void Order::SetPrev(Order *p)
{
	this->prev = p;
}

Name Order::GetName()
{
	return this->name;
}

void Order::SetName(Name n)
{
	this->name = n;
}


// ---  End of File ---------------
