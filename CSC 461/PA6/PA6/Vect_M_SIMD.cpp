//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------- 

#include "Vect_M_SIMD.h"
#include "Matrix_M_SIMD.h"

Vect_M_SIMD::Vect_M_SIMD(const float tx, const float ty, const float tz, const float tw)
	: x(tx), y(ty), z(tz), w(tw)
{
}

Vect_M_SIMD::Vect_M_SIMD(const __m128 m)
	: _m(m)
{
}

// ---  End of File ---------------


