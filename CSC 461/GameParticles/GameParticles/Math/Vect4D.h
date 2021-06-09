//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

// This is a 4 dimensional Vect4D class
#ifndef Vect4D_H
#define Vect4D_H

// includes
#include "Enum.h"
#include "Align16.h"

#include <xmmintrin.h>
#include <smmintrin.h>  

// Foward Declarations
class Matrix;

// class
class Vect4D : Align16
{
public:
	friend class Matrix;

	//big four
	Vect4D();
	~Vect4D() = default;
	Vect4D(const Vect4D & tmp) = default;
	Vect4D & operator=(const Vect4D & tmp) = default;

	Vect4D(float tx, float ty, float tz, float tw = 1.0f);
	Vect4D(const __m128 m);

	Vect4D operator + (Vect4D t);
	Vect4D operator - (Vect4D t);
	Vect4D operator * (float scale);
	float &operator[](VECT_ENUM e);

	void Cross(Vect4D &vin, Vect4D &vout);
	void norm(Vect4D &out);
	void set(float tx, float ty, float tz, float tw = 1.0f);

	union
	{
		__m128	_m;

		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
	};
};

#endif  

// End of file

