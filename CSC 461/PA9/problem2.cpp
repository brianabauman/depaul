//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
//
// NO HEADERS... do the problem in this CPP file
//
// Do Problem 2 here:
//
// ---------------------------------------------------------------------------

struct Vect
{
	float x;
	float y;
	float z;
};

enum ResultCode
{
	SUCCESS,
	LENGTH_ZERO,
	NULLPTR,
	GENERIC_FAILURE
};

//from the internet, mentioned by Keenan
float InvSqrt(float x)
{
	if (x == 0) return 0;

	float xhalf = 0.5f*x;
	int i = *(int*)&x;
	i = 0x5f3759df - (i >> 1);
	x = *(float*)&i;
	x = x * (1.5f - xhalf * x*x);
	return x;
}

ResultCode normalize(Vect * const v)
{
	ResultCode rtnCd = GENERIC_FAILURE;

	if (v == nullptr) rtnCd = NULLPTR;
	else if (v->x == 0 && v->y == 0 && v->z == 0) rtnCd = LENGTH_ZERO;
	else
	{
		float x2y2z2 = (v->x * v->x) + (v->y * v->y) + (v->z * v->z);
		float n = InvSqrt(x2y2z2);

		v->x = v->x*n;
		v->y = v->y*n;
		v->z = v->z*n;

		rtnCd = SUCCESS;
	}

	return rtnCd;
}

// End of File
