//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
//
// NO HEADERS... do the problem in this CPP file
//
// Do Problem 4 here:
//
// ---------------------------------------------------------------------------

#include <math.h>

typedef struct Vect  // Vector struct for positions
{
	float x;
	float y;
	float z;
} Vect_t; 
 
/***********************************************************************
*
*  Function: findMaxDistance()
*
*  Input:
*          int       nPlayers - number of players
*          Vect_t   *playerArray - the array of players
*  Output:
*          float     maxDist - the maxDistance between any two players 
*
***********************************************************************/

//from the internet, mentioned by Keenan
float InvSqrt(float x)
{
	if (x == 0) return 0.0f;

	float xhalf = 0.5f*x;
	int i = *(int*)&x;
	i = 0x5f3759df - (i >> 1);
	x = *(float*)&i;
	x = x * (1.5f - xhalf * x*x);
	return x;
}

enum ResultCode
{
	SUCCESS,
	GENERIC_FAILURE,
	NO_PLAYERS
};

ResultCode findMaxMinDistances(const int nPlayers, const Vect_t *playerArray, float &outputMax, float &outputMin)
{
	ResultCode rtnCd = GENERIC_FAILURE;
	if (playerArray == nullptr || nPlayers < 1) return NO_PLAYERS;

	Vect_t tmpVect;   // temporary vector
	float tmpDist;    // temporary distance
	float tmpDistSq;  // temporary square of the distance

	// initialize the distance to zero
	outputMax = 0.0f;
	outputMin = -1.0f;

	for (int i = 0; i < nPlayers; i++)
		for (int j = i + 1; j < nPlayers; j++)
		{
			// Find a vector between point i and j
			tmpVect.x = playerArray[i].x - playerArray[j].x;
			tmpVect.y = playerArray[i].y - playerArray[j].y;
			tmpVect.z = playerArray[i].z - playerArray[j].z;

			// Get its length
			tmpDistSq = (tmpVect.x * tmpVect.x
				+ tmpVect.y * tmpVect.y
				+ tmpVect.z * tmpVect.z);
			tmpDist = InvSqrt(tmpDistSq) * tmpDistSq; //Using 1/sqrt(x) speed from internet and Keenan

			// determine if it’s a new maximum length or minimum length
			if (tmpDist > outputMax) outputMax = tmpDist;
			else if (tmpDist < outputMin || outputMin < 0) outputMin = tmpDist;
		}

	rtnCd = SUCCESS;

	return rtnCd;

} // End of findMaxDistance()

// End of File
