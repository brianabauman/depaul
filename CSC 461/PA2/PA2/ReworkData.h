//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------- 

#ifndef REWORK_DATA_H
#define REWORK_DATA_H

struct DataA
{
	char a;
	char b;
	double r;
};

struct DataB
{
	DataA da;
	int i;
	char a;
	char b;
};

struct DataC
{
	double r;
	int i;
	bool f;
	char a;
};

struct DataD
{
	double r;
	int i;
	char a;
	char b;
};

struct DataE
{
	double r;
	char name[12];
	int x;
	int *p;
	char a;
	char c;
};

struct Vect
{
	float vx;
	float vy;
	float vz;
	float vw;
	char a;
	char b;
};

struct DataF
{
	Vect v;
	int i;
	int j;
	char c;
	char b;
};


#endif

// ---  End of File ---------------
