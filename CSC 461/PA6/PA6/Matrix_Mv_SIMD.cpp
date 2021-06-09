//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------- 

#include "Vect_Mv_SIMD.h"
#include "Matrix_Mv_SIMD.h"

#define UNUSED_VAR(X) ((void )X)

Matrix_Mv_SIMD::Matrix_Mv_SIMD(const Vect_Mv_SIMD &tV0,
							   const Vect_Mv_SIMD &tV1,
							   const Vect_Mv_SIMD &tV2,
							   const Vect_Mv_SIMD &tV3)
	: v0(tV0), v1(tV1), v2(tV2), v3(tV3)
{
}

Vect_Mv_SIMD Matrix_Mv_SIMD::operator * (const Vect_Mv_SIMD &v) const
{
	__m128 tmp0 = _mm_mul_ps(v0._m, v._m);
	__m128 tmp1 = _mm_mul_ps(v1._m, v._m);
	__m128 tmp2 = _mm_mul_ps(v2._m, v._m);
	__m128 tmp3 = _mm_mul_ps(v3._m, v._m);
	return Vect_Mv_SIMD(_mm_hadd_ps(_mm_hadd_ps(tmp0, tmp1), _mm_hadd_ps(tmp2, tmp3)));
}

// ---  End of File ---------------
