//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------- 

#ifndef VECT4D_H
#define VECT4D_H

//-------------------------------------------
//       ---> DO NOT MODIFY <---
//-------------------------------------------

#include "Framework.h"

#define STUB_PLEASE_REPLACE(x) (x)

class Matrix;

class Vect4D
{
public:
	Vect4D() = default;
	Vect4D(const Vect4D &t) = default;
	Vect4D &operator = (const Vect4D &tmp) = default;
	~Vect4D() = default;

	Vect4D(const float tx, const float ty, const float tz, const float tw);

	Vect4D operator + (const Vect4D &t) const;
	Vect4D operator - (const Vect4D &t) const;
	Vect4D operator * (const float s) const;
	Vect4D operator * (const Matrix &m)const;

	static Vect4D Lerp(const Vect4D &a, const Vect4D &b, const float t);

public:
	float x;
	float y;
	float z;
	float w;
};

#endif

// ---  End of File ---------------
