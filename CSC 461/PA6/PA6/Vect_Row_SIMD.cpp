//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------- 

#include "Vect_Row_SIMD.h"
#include "Matrix_Row_SIMD.h"

#define UNUSED_VAR(X) ((void )X)

Vect_Row_SIMD::Vect_Row_SIMD(const float tx, const float ty, const float tz, const float tw)
	: x(tx), y(ty), z(tz), w(tw)
{
}

Vect_Row_SIMD::Vect_Row_SIMD(const __m128 m)
	: _m(m)
{
}

Vect_Row_SIMD Vect_Row_SIMD::operator * ( const Matrix_Row_SIMD &ma)
{
	__m128 x0 = _mm_mul_ps(ma.v0._m, _mm_set1_ps(x));
	__m128 y0 = _mm_mul_ps(ma.v1._m, _mm_set1_ps(y));
	__m128 z0 = _mm_mul_ps(ma.v2._m, _mm_set1_ps(z));
	__m128 w0 = _mm_mul_ps(ma.v3._m, _mm_set1_ps(w));
	return Vect_Row_SIMD(_mm_add_ps(_mm_add_ps(_mm_add_ps(x0, y0), z0), w0));
};


// ---  End of File ---------------


