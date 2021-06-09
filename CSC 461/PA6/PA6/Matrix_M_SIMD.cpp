//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------- 

#include "Vect_M_SIMD.h"
#include "Matrix_M_SIMD.h"

#define UNUSED_VAR(X) ((void )X)

Matrix_M_SIMD::Matrix_M_SIMD(const Vect_M_SIMD &tV0,
							 const Vect_M_SIMD &tV1,
							 const Vect_M_SIMD &tV2,
							 const Vect_M_SIMD &tV3)
	: v0(tV0), v1(tV1), v2(tV2), v3(tV3)
{
}

Matrix_M_SIMD Matrix_M_SIMD::operator * (const Matrix_M_SIMD &mb) const
{
	__m128 x0 = _mm_mul_ps(mb.v0._m, _mm_set1_ps(m0));
	__m128 y0 = _mm_mul_ps(mb.v1._m, _mm_set1_ps(m1));
	__m128 z0 = _mm_mul_ps(mb.v2._m, _mm_set1_ps(m2));
	__m128 w0 = _mm_mul_ps(mb.v3._m, _mm_set1_ps(m3));
	__m128 r0 = _mm_add_ps(_mm_add_ps(_mm_add_ps(x0, y0), z0), w0);

	__m128 x1 = _mm_mul_ps(mb.v0._m, _mm_set1_ps(m4));
	__m128 y1 = _mm_mul_ps(mb.v1._m, _mm_set1_ps(m5));
	__m128 z1 = _mm_mul_ps(mb.v2._m, _mm_set1_ps(m6));
	__m128 w1 = _mm_mul_ps(mb.v3._m, _mm_set1_ps(m7));
	__m128 r1 = _mm_add_ps(_mm_add_ps(_mm_add_ps(x1, y1), z1), w1);

	__m128 x2 = _mm_mul_ps(mb.v0._m, _mm_set1_ps(m8));
	__m128 y2 = _mm_mul_ps(mb.v1._m, _mm_set1_ps(m9));
	__m128 z2 = _mm_mul_ps(mb.v2._m, _mm_set1_ps(m10));
	__m128 w2 = _mm_mul_ps(mb.v3._m, _mm_set1_ps(m11));
	__m128 r2 = _mm_add_ps(_mm_add_ps(_mm_add_ps(x2, y2), z2), w2);

	__m128 x3 = _mm_mul_ps(mb.v0._m, _mm_set1_ps(m12));
	__m128 y3 = _mm_mul_ps(mb.v1._m, _mm_set1_ps(m13));
	__m128 z3 = _mm_mul_ps(mb.v2._m, _mm_set1_ps(m14));
	__m128 w3 = _mm_mul_ps(mb.v3._m, _mm_set1_ps(m15));
	__m128 r3 = _mm_add_ps(_mm_add_ps(_mm_add_ps(x3, y3), z3), w3);

	return Matrix_M_SIMD(r0, r1, r2, r3);
}


// ---  End of File ---------------
