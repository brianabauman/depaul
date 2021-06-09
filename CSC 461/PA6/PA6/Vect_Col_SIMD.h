//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------- 

#ifndef Vect_Col_SIMD_H
#define Vect_Col_SIMD_H

#include <xmmintrin.h>
#include <smmintrin.h>  

class Matrix_Col_SIMD;

// -----------------------------------------------------------------------
// Rules: 
//    ---> No implementation in Header <---
//    No inline keyword
// -----------------------------------------------------------------------

class Vect_Col_SIMD
{
public:
	Vect_Col_SIMD() = default;
	Vect_Col_SIMD(const Vect_Col_SIMD &tmp) = default;
	Vect_Col_SIMD &operator = (const Vect_Col_SIMD &tmp) = default;
	~Vect_Col_SIMD() = default;

	Vect_Col_SIMD(const float tx, const float ty, const float tz, const float tw);
	Vect_Col_SIMD(const __m128 m);

public:

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

// ---  End of File ---------------
