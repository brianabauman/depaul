//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include <Math.h>
#include <assert.h>
#include <xmmintrin.h>
#include <smmintrin.h>  

#include "Trace.h"
#include "Vect4D.h"
#include "Matrix.h"

Matrix::Matrix()
{	// constructor for the matrix
	v0._m = _mm_set_ps1(0.0f);
	v1._m = _mm_set_ps1(0.0f);
	v2._m = _mm_set_ps1(0.0f);
	v3._m = _mm_set_ps1(0.0f);
}

Matrix::Matrix(Matrix& t)
{ // copy constructor
	this->v0._m = t.v0._m;
	this->v1._m = t.v1._m;
	this->v2._m = t.v2._m;
	this->v3._m = t.v3._m;
}

Matrix::~Matrix()
{
	// nothign to delete
}

Matrix::Matrix(__m128 m0, __m128 m1, __m128 m2, __m128 m3)
	: v0(m0), v1(m1), v2(m2), v3(m3)
{
}

Matrix::Matrix(Vect4D m0, Vect4D m1, Vect4D m2, Vect4D m3)
	: v0(m0), v1(m1), v2(m2), v3(m3)
{
}

void Matrix::setIdentMatrix()
{ // initialize to the identity matrix
	this->m0 = 1.0;
	this->m1 = 0.0;
	this->m2 = 0.0;
	this->m3 = 0.0;

	this->m4 = 0.0;
	this->m5 = 1.0;
	this->m6 = 0.0;
	this->m7 = 0.0;

	this->m8 = 0.0;
	this->m9 = 0.0;
	this->m10 = 1.0;
	this->m11 = 0.0;

	this->m12 = 0.0;
	this->m13 = 0.0;
	this->m14 = 0.0;
	this->m15 = 1.0;
}

void Matrix::setTransMatrix(Vect4D *t)
{ // set the translation matrix (note: we are row major)
	//assumes the matrix is already an identity matrix!
	this->m12 = t->x;
	this->m13 = t->y;
	this->m14 = t->z;
}

void Matrix::setScaleMatrix(Vect4D *scale)
{
	//	{	sx		0		0		0 } 
	//	{	0		sy		0		0 } 
	//	{	0		0		sz		0 } 
	//	{	0		0		0		1 } 
	// assumes the matrix is already an identity matrix!
	this->m0 = scale->x;
	this->m5 = scale->y;
	this->m10 = scale->z;
}

void Matrix::setRotZMatrix(float az)
{
	//	{	cos		-sin		0		0 } 
	//	{	sin		cos		0		0 } 
	//	{	0		0		1		0 } 
	//	{	0		0		0		1 } 
	// assumes the matrix is already an identity matrix!
	this->m0 = cos(az);
	this->m1 = -sin(az);
	this->m4 = sin(az);
	this->m5 = cos(az);
}

void Matrix::set(MATRIX_ENUM row, Vect4D *t)
{
	// initialize the rows of the matrix
	switch (row)
	{
	case MATRIX_ROW_0:
		this->v0._m = t->_m;
		break;
	case MATRIX_ROW_1:
		this->v1._m = t->_m;
		break;
	case MATRIX_ROW_2:
		this->v2._m = t->_m;
		break;
	case MATRIX_ROW_3:
		this->v3._m = t->_m;
		break;
	default:
		// should never get here, if we are here something bad has happened
		assert(0);
	}
}

void Matrix::get(MATRIX_ENUM row, Vect4D *t)
{
	// initialize the rows of the matrix
	switch (row)
	{
	case MATRIX_ROW_0:
		t->_m = this->v0._m;
		break;
	case MATRIX_ROW_1:
		t->_m = this->v1._m;
		break;
	case MATRIX_ROW_2:
		t->_m = this->v2._m;
		break;
	case MATRIX_ROW_3:
		t->_m = this->v3._m;
		break;
	default:
		// should never get here, if we are here something bad has happened
		assert(0);
	}
}

Matrix Matrix::operator*(Matrix& rhs)
{
	__m128 x0 = _mm_mul_ps(rhs.v0._m, _mm_set1_ps(m0));
	__m128 y0 = _mm_mul_ps(rhs.v1._m, _mm_set1_ps(m1));
	__m128 z0 = _mm_mul_ps(rhs.v2._m, _mm_set1_ps(m2));
	__m128 w0 = _mm_mul_ps(rhs.v3._m, _mm_set1_ps(m3));
	__m128 r0 = _mm_add_ps(_mm_add_ps(_mm_add_ps(x0, y0), z0), w0);

	__m128 x1 = _mm_mul_ps(rhs.v0._m, _mm_set1_ps(m4));
	__m128 y1 = _mm_mul_ps(rhs.v1._m, _mm_set1_ps(m5));
	__m128 z1 = _mm_mul_ps(rhs.v2._m, _mm_set1_ps(m6));
	__m128 w1 = _mm_mul_ps(rhs.v3._m, _mm_set1_ps(m7));
	__m128 r1 = _mm_add_ps(_mm_add_ps(_mm_add_ps(x1, y1), z1), w1);

	__m128 x2 = _mm_mul_ps(rhs.v0._m, _mm_set1_ps(m8));
	__m128 y2 = _mm_mul_ps(rhs.v1._m, _mm_set1_ps(m9));
	__m128 z2 = _mm_mul_ps(rhs.v2._m, _mm_set1_ps(m10));
	__m128 w2 = _mm_mul_ps(rhs.v3._m, _mm_set1_ps(m11));
	__m128 r2 = _mm_add_ps(_mm_add_ps(_mm_add_ps(x2, y2), z2), w2);

	__m128 x3 = _mm_mul_ps(rhs.v0._m, _mm_set1_ps(m12));
	__m128 y3 = _mm_mul_ps(rhs.v1._m, _mm_set1_ps(m13));
	__m128 z3 = _mm_mul_ps(rhs.v2._m, _mm_set1_ps(m14));
	__m128 w3 = _mm_mul_ps(rhs.v3._m, _mm_set1_ps(m15));
	__m128 r3 = _mm_add_ps(_mm_add_ps(_mm_add_ps(x3, y3), z3), w3);

	return Matrix(r0, r1, r2, r3);
}

Matrix& Matrix::operator/=(float rhs)
{
	// divide each element by a value
	// using inverse multiply trick, faster that individual divides
	__m128 inv_rhs = _mm_set_ps1(1.0f / rhs);

	v0._m = _mm_mul_ps(inv_rhs, v0._m);
	v1._m = _mm_mul_ps(inv_rhs, v1._m);
	v2._m = _mm_mul_ps(inv_rhs, v2._m);
	v2._m = _mm_mul_ps(inv_rhs, v3._m);

	return *this;
}

float Matrix::Determinant()
{
	// A = { a,b,c,d / e,f,g,h / j,k,l,m / n,o,p,q }
	// A = { 0,1,2,3 / 4,5,6,7 / 8,9,10,11 / 12,13,14,15 }

	// det(A) = a*det( { f,g,h / k,l,m / o,p,q } )
	//			- b*det( { e,g,h / j,l,m / n,p,q } )
	//			+ c*det( { e,f,h / j,k,m / n,o,q } )
	//			- d*det( { e,f,g / j,k,l / n,o,p } )

	// det(A) = (a (f (lq - mp) - g (kq - mo) + h (kp - lo) ) )
	//			- (b (e (lq - mp) - g (jq - mn) + h (jp - ln) ) )
	//			+ (c (e (kq - mo) - f (jq - mn) + h (jo - kn) ) )
	//			- (d (e (kp - lo) - f (jp - ln) + g (jo - kn) ) )

	// ta = (lq - mp)
	float ta = (m10 * m15) - (m11 * m14);
	// tb = (kq - mo)
	float tb = (m9 * m15) - (m11 * m13);
	// tc = (kp - lo)
	float tc = (m9 * m14) - (m10 * m13);
	// td = (jq - mn)
	float td = (m8 * m15) - (m11 * m12);
	// te = (jo - kn)
	float te = (m8 * m13) - (m9 *  m12);
	// tf = (jp - ln)
	float tf = (m8 * m14) - (m10 * m12);

	// det(A) = (a (f*ta  - g*tb + h*tc) )
	//			- (b (e*ta - g*td + h*tf) )      
	//			+ (c (e*tb - f*td + h*te) )      
	//			- (d (e*tc - f*tf + g*te) )       
	return ((m0 * ((m5 * ta) - (m6 * tb) + (m7 * tc)))
			- (m1 * ((m4 * ta) - (m6 * td) + (m7 * tf)))
			+ (m2 * ((m4 * tb) - (m5 * td) + (m7 * te)))
			- (m3 * ((m4 * tc) - (m5 * tf) + (m6 * te))));

}

Matrix Matrix::GetAdjugate()
{
	// matrix = { a,b,c,d / e,f,g,h / j,k,l,m / n,o,p,q }

	// ta = lq - mp
	// tb = kq - mo
	// tc = kp - lo
	// td = gq - hp
	// te = fq - ho
	// tf = fp - go
	// tg = gm - hl
	// th = fm - hk
	// ti = fl - gk
	// tj = jq - mn
	// tk = jp - ln
	// tl = eq - hn
	// tm = ep - gn
	// tn = em - hj
	// to = el - gj
	// tp = jo - kn
	// tq = ek - fj
	// tr = eo - fn

	// a = det( { f,g,h / k,l,m / o,p,q } )
	// a = f(lq - mp) - g(kq - mo) + h(kp - lo)
	// a = f(ta) - g(tb) + h(tc)   

	// b = -det( { b,c,d / k,l,m / o,p,q } )
	// b = -( b(lq - mp) - c(kq - mo) + d(kp - lo))
	// b = -( b(ta) - c(tb) + d(tc))

	// c = det( { b,c,d / f,g,h / o,p,q } )
	// c = b(gq - hp) - c(fq - ho) + d(fp - go)
	// c = b(td) - c(te) + d(tf)

	// d = -det( { b,c,d / f,g,h / k,l,m } )
	// d = -( b(gm - hl) - c(fm - hk) + d(fl - gk) )
	// d = -( b(tg) - c(th) + d(ti) )

	// e = -det( { e,g,h / j,l,m / n,p,q } )
	// e = - ( e(lq - mp) - g(jq - mn) + h(jp - ln))
	// e = - ( e(ta) - g(tj) + h(tk))     

	// f = det( { a,c,d / j,l,m / n,p,q } )
	// f = a(lq - mp) - c(jq - mn) + d(jp - ln)
	// f = a(ta) - c(tj) + d(tk)

	// g = -det( { a,c,d / e,g,h / n,p,q } )
	// g = - ( a(gq - hp) - c(eq - hn) + d(ep - gn))
	// g = - ( a(td) - c(tl) + d(tm))

	// h = det( { a,c,d / e,g,h / j,l,m } )
	// h = a(gm - hl) - c(em - hj) + d(el - gj)
	// h = a(tg) - c(tn) + d(to)   

	// j = det( { e,f,h / j,k,m / n,o,q } )
	// j = e(kq - mo) - f(jq - mn) + h(jo - kn)
	// j = e(tb) - f(tj) + h(tp)

	// k = -det( { a,b,d / j,k,m / n,o,q } )
	// k = - ( a(kq - mo) - b(jq - mn) + d(jo - kn))
	// k = - ( a(tb) - b(tj) + d(tp))

	// l = det( { a,b,d / e,f,h / n,o,q } )
	// l = a(fq - ho) - b(eq - hn) + d(eo - fn)
	// l = a(te) - b(tl) + d(tr)

	// m = -det( { a,b,d / e,f,h / j,k,m } )
	// m = -( a(fm - hk) - b(em - hj) + d(ek - fj))
	// m = -( a(th) - b(tn) + d(tq))

	// n = -det( { e,f,g / j,k,l / n,o,p } )
	// n = -( e(kp - lo) - f(jp - ln) + g(jo - kn))
	// n = -( e(tc) - f(tk) + g(tp))

	// o = det( { a,b,c / j,k,l / n,o,p } )
	// o = a(kp - lo) - b(jp - ln) + c(jo - kn)
	// o = a(tc) - b(tk) + c(tp)

	// p = -det( { a,b,c / e,f,g / n,o,p } )
	// p = - ( a(fp - go) - b(ep - gn) + c(eo - fn))
	// p = - ( a(tf) - b(tm) + c(tr))       

	// q = det( { a,b,c / e,f,g / j,k,l } )
	// q = a(fl - gk) - b(el - gj) + c(ek - fj)
	// q = a(ti) - b(to) + c(tq)

	Matrix tmp;

	// load		ABC		(3)		ABC--
	float t1 = (m10*m15) - (m11*m14);
	float t2 = (m9*m15) - (m11*m13);
	float t3 = (m9*m14) - (m10*m13);

	// a = f(ta) - g(tb) + h(tc)
	tmp.m0 = (m5*t1) - (m6*t2) + (m7*t3);
	// b = -( b(ta) - c(tb) + d(tc)) 
	tmp.m1 = -((m1*t1) - (m2*t2) + (m3*t3));

	// load		JK		(5)		ABCJK
	float t4 = (m8*m15) - (m11*m12);
	float t5 = (m8*m14) - (m10*m12);
	// e = - ( e(ta) - g(tj) + h(tk))
	tmp.m4 = -((m4*t1) - (m6*t4) + (m7*t5));
	// f = a(ta) - c(tj) + d(tk)
	tmp.m5 = (m0*t1) - (m2*t4) + (m3*t5);

	// unload	AJ		(3)		-BC-K
	// load		P		(4)		PBC-K
	t1 = (m8*m13) - (m9*m12);
	// n = -( e(tc) - f(tk) + g(tp))
	tmp.m12 = -((m4*t3) - (m5*t5) + (m6*t1));
	// o = a(tc) - b(tk) + c(tp)  
	tmp.m13 = (m0*t3) - (m1*t5) + (m2*t1);

	// unload	KC		(2)		PB---
	// load		J		(3)		PBJ--
	t3 = (m8*m15) - (m11*m12);

	// j = e(tb) - f(tj) + h(tp)
	tmp.m8 = (m4*t2) - (m5*t3) + (m7*t1);
	// k = - ( a(tb) - b(tj) + d(tp))
	tmp.m9 = -((m0*t2) - (m1*t3) + (m3*t1));

	// unload	BPJ		(0)		-----
	// load		DLM		(3)		DLM--
	t1 = (m6*m15) - (m7*m14);
	t2 = (m4*m15) - (m7*m12);
	t3 = (m4*m14) - (m6*m12);

	// g = - ( a(td) - c(tl) + d(tm))
	tmp.m6 = -((m0*t1) - (m2*t2) + (m3*t3));

	// load		FR		(5)		DLMFR
	t4 = (m5*m14) - (m6*m13);
	t5 = (m4*m13) - (m5*m12);

	// p = - ( a(tf) - b(tm) + c(tr))
	tmp.m14 = -((m0*t4) - (m1*t3) + (m3*t5));

	// unload	M		(4)		DL-FR 
	// load		E		(5)		DLEFR 
	t3 = (m5*m15) - (m7*m13);

	// l = a(te) - b(tl) + d(tr)
	tmp.m10 = (m0*t3) - (m1*t2) + (m3*t5);

	// unload	LR		(3)		D-EF-
	// c = b(td) - c(te) + d(tf)
	tmp.m2 = (m1*t1) - (m2*t3) + (m3*t4);

	// unload	DEF		(0)		-----
	// load		GHI		(3)		GHI--
	t1 = (m6*m11) - (m7*m10);
	t2 = (m5*m11) - (m7*m9);
	t3 = (m5*m10) - (m6*m9);

	// d = -( b(tg) - c(th) + d(ti) )      
	tmp.m3 = -((m1*t1) - (m2*t2) + (m3*t3));

	// load		NO		(5)		GHINO
	t4 = (m4*m11) - (m7*m8);
	t5 = (m4*m10) - (m6*m8);

	// h = a(tg) - c(tn) + d(to)
	tmp.m7 = (m0*t1) - (m2*t4) + (m3*t5);

	// unload	G		(4)		-HINO
	// load		Q		(5)		QHINO
	t1 = (m4*m9) - (m5*m8);

	// m = -( a(th) - b(tn) + d(tq))
	tmp.m11 = -((m0*t2) - (m1*t4) + (m3*t1));

	// unload	HN		(3)		Q-I-O
	// q = a(ti) - b(to) + c(tq)
	tmp.m15 = (m0*t3) - (m1*t5) + (m2*t1);

	return tmp;
}

void Matrix::Inverse(Matrix &out)
{
	Matrix tmp;
	float det = Determinant();
	if (fabs(det) < 0.0001)
	{
		// do nothing, Matrix is not invertable
	}
	else
	{
		tmp = GetAdjugate();
		tmp /= det;
	}

	out = tmp;
}
// End of file