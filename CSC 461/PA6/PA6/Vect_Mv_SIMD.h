//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------- 

#ifndef Vect_Mv_SIMD_H
#define Vect_Mv_SIMD_H

#include <xmmintrin.h>
#include <smmintrin.h>  

class Matrix_Mv_SIMD;

// -----------------------------------------------------------------------
// Rules: 
//    ---> No implementation in Header <---
//    No inline keyword
// -----------------------------------------------------------------------

class Vect_Mv_SIMD
{
public:
	Vect_Mv_SIMD() = default;
	Vect_Mv_SIMD(const Vect_Mv_SIMD &tmp) = default;
	Vect_Mv_SIMD &operator = (const Vect_Mv_SIMD &tmp) = default;
	~Vect_Mv_SIMD() = default;

	Vect_Mv_SIMD(const float tx, const float ty, const float tz, const float tw);
	Vect_Mv_SIMD(const __m128 m);

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
