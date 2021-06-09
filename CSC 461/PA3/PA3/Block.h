//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
// Optimized C++
//----------------------------------------------------------------------------- 

#ifndef BLOCK_H
#define BLOCK_H

#include "Types.h"

enum class Block : uint8_t
{
	Free = 0xC3, // Do not Change values 
	Used = 0xA5  // Do not change values 
};

#endif

// ---  End of File ---------------
