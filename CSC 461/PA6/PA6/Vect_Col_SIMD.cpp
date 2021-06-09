//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------- 

#include "Vect_Col_SIMD.h"


Vect_Col_SIMD::Vect_Col_SIMD(const float tx, const float ty, const float tz, const float tw)
	: x(tx), y(ty), z(tz), w(tw)
{
}

Vect_Col_SIMD::Vect_Col_SIMD(const __m128 m)
	: _m(m)
{
}

// ---  End of File ---------------


