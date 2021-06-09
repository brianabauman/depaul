//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------- 

#ifndef ALIGN_H
#define ALIGN_H

class Align
{
public:
	struct Info
	{
		int NumTotalBytes;
		int NumBytesOfPadding;
	};

	static Info PrintME(void *p, int StructSize, char *s);
};

#endif

// ---  End of File ---------------
