//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef MATRIX_H
#define MATRIX_H

// includes
#include "Enum.h"
#include "Vect4D.h"
#include "Align16.h"

// forward declare
class Vect4D;

// class
class Matrix : Align16
{
public:

	//big four
	Matrix();
	Matrix(Matrix& t);
	~Matrix();
	Matrix &operator=(const Matrix &tmp) = default;

	Matrix(__m128 m0, __m128 m1, __m128 m2, __m128 m3);
	Matrix(Vect4D m0, Vect4D m1, Vect4D m2, Vect4D m3);

	Matrix operator*(Matrix &t);
	Matrix& Matrix::operator/=(float t);

	void set(MATRIX_ENUM row, Vect4D *t);
	void get(MATRIX_ENUM row, Vect4D *vOut);

	void setIdentMatrix();
	void setTransMatrix(Vect4D *t);
	void setScaleMatrix(Vect4D *s);
	void setRotZMatrix(float Z_Radians);
	float Determinant();
	Matrix GetAdjugate();
	void Inverse(Matrix &out);

	union
	{
		struct
		{
			Vect4D v0;
			Vect4D v1;
			Vect4D v2;
			Vect4D v3;
		};

		struct
		{
			float m0;
			float m1;
			float m2;
			float m3;
			float m4;
			float m5;
			float m6;
			float m7;
			float m8;
			float m9;
			float m10;
			float m11;
			float m12;
			float m13;
			float m14;
			float m15;
		};
	};
};

#endif 

// End of File

