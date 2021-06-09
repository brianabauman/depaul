//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------- 

#ifndef ALIGN_DATA_H
#define ALIGN_DATA_H

// Add default constructor to each structure
// Initialize all variable to 0

struct A
{
	A();

	int  a0;
	char a1;
};

struct B
{
	B();

	float b0;
	float b1;
	bool  b2;
	float b3;
};

struct C
{
	C();

	char   c0;
	double c1;
	char   c2;
};

struct D
{
	D();

	A      d0;
	double d1;
	B      d2;
	char   d3;
	C      d4;
};

#endif

// ---  End of File ---------------
