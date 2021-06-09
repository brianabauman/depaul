//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------- 

#ifndef Matrix_Col_SIMD_H
#define Matrix_Col_SIMD_H

#include "Vect_Col_SIMD.h"
   
// -----------------------------------------------------------------------
// Rules: 
//    Implement for Col Major
//    ---> No implementation in Header <---
//
//    Proxy (optional)
//    
//        Proxies are the only thing that can have the keyword "inline"
//            inline only for subsitution resolving.. that's it
//                No constructors or other operators... only proxy for substituion purpose
//            example:  (this is allowed)
//                inline MM operator * (const Matrix_Col_SIMD &m, const Matrix_Col_SIMD &n)
//        No proxy implementation in header
//            conversion operator needs to be implemented in CPP file
//            proxy constructors are allowed in header (only exception)
// -----------------------------------------------------------------------

class Matrix_Col_SIMD
{
public:
	Matrix_Col_SIMD() = default;
	Matrix_Col_SIMD(const Matrix_Col_SIMD &tmp) = default;
	Matrix_Col_SIMD &operator=(const Matrix_Col_SIMD &tmp) = default;
	~Matrix_Col_SIMD() = default;

	Matrix_Col_SIMD(const Vect_Col_SIMD &tV0,
					const Vect_Col_SIMD &tV1,
					const Vect_Col_SIMD &tV2,
					const Vect_Col_SIMD &tV3);
 
	//Matrix_Col_SIMD operator * (const Matrix_Col_SIMD &n);
	//Vect_Col_SIMD operator * (const Vect_Col_SIMD &n);

	union
	{
		struct
		{
			Vect_Col_SIMD v0;
			Vect_Col_SIMD v1;
			Vect_Col_SIMD v2;
			Vect_Col_SIMD v3;
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

private:

	friend struct MM;
};

struct MM
{

public:
	MM() = delete;
	~MM() = default;
	MM(const MM &) = default;
	MM operator = (const MM &) = delete;

	MM(const Matrix_Col_SIMD &M1, const Matrix_Col_SIMD &M2)
		: M1(M1), M2(M2)
	{
	};

private:
	const Matrix_Col_SIMD M1;
	const Matrix_Col_SIMD M2;

	friend struct MMM;
};

inline MM operator * (const Matrix_Col_SIMD &M1, const Matrix_Col_SIMD &M2)
{
	return MM(M1, M2);
}

struct MMM
{
public:
	MMM() = delete;
	~MMM() = default;
	MMM(const MMM &) = default;
	MMM operator = (const MMM &) = delete;

	MMM(const MM &MM, const Matrix_Col_SIMD &M)
		: M1(MM.M1), M2(MM.M2), M3(M)
	{
	};

private:
	const Matrix_Col_SIMD M1;
	const Matrix_Col_SIMD M2;
	const Matrix_Col_SIMD M3;

	friend struct MMMM;
};

inline MMM operator * (const MM &MM, const Matrix_Col_SIMD &M)
{
	return MMM(MM, M);
}

struct MMMM
{
public:
	MMMM() = delete;
	~MMMM() = default;
	MMMM(const MMMM &) = default;
	MMMM operator = (const MMMM &) = delete;

	MMMM(const MMM &MMM, const Matrix_Col_SIMD &M)
		: M1(MMM.M1), M2(MMM.M2), M3(MMM.M3), M4(M)
	{
	};

private:
	const Matrix_Col_SIMD M1;
	const Matrix_Col_SIMD M2;
	const Matrix_Col_SIMD M3;
	const Matrix_Col_SIMD M4;

	friend struct MMMMM;
};

inline MMMM operator * (const MMM &MMM, const Matrix_Col_SIMD &M)
{
	return MMMM(MMM, M);
}

struct MMMMM
{
public:
	MMMMM() = delete;
	~MMMMM() = default;
	MMMMM(const MMMMM &) = default;
	MMMMM operator = (const MMMMM &) = delete;

	Vect_Col_SIMD operator * (const Vect_Col_SIMD &v);

	MMMMM(const MMMM &MMMM, const Matrix_Col_SIMD &M)
		: M1(MMMM.M1), M2(MMMM.M2), M3(MMMM.M3), M4(MMMM.M4), M5(M)
	{
	};

private:
	const Matrix_Col_SIMD M1;
	const Matrix_Col_SIMD M2;
	const Matrix_Col_SIMD M3;
	const Matrix_Col_SIMD M4;
	const Matrix_Col_SIMD M5;
};

inline MMMMM operator * (const MMMM &MMMM, const Matrix_Col_SIMD &M)
{
	return MMMMM(MMMM, M);
}

#endif

// ---  End of File ---------------
