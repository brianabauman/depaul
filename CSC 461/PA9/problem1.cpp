//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
//
// NO HEADERS... do the problem in this CPP file
//
// Do Problem 1 here:
//
// ---------------------------------------------------------------------------
float calculate(const float x)
{
	float a0 = 1.0;
	float a1 = 2.0;
	float a2 = 3.0;
	float a3 = 4.0;
	float a4 = 5.0;
	float a5 = 6.0;

	return a0 + x * (a1 + x * (a2 + x * (a3 + x * (a4 + x * a5))));
};


// End of File
