//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------- 

#ifndef NODE_H
#define NODE_H

#include "Vect.h"
#include "Matrix.h"

class Node
{
public:
	static const unsigned int NAME_SIZE = 128;

public:
	// big four
	Node();
	Node(const Node &) = default;
	Node & operator = (const Node &) = default;
	~Node() = default;

private:
	void privSetRandFloat(float & var) const;
	void privSetRandInt(int & var) const;
	void privSetRandVect(Vect & var) const;
	void privSetRandMatrix(Matrix & var) const ;
	void privSetRandName(char * p, const int size) const;
	char privSetRandChar() const;

public:  // Treating as SIMPLE DATA, so public is OK
	Node	*pNext;
	Node	*pPrev;
	float	x;
	float	y;
	float	z;
	Vect	A;
	Vect	B;
	Vect	C;
	Matrix	MA;
	Matrix	MB;
	Matrix	MC;
	Matrix	MD;
	char	name[NAME_SIZE];
	int		key;
};

#endif 

// ---  End of File ---------------
