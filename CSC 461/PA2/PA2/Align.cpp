//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------- 

#include "Framework.h"

#include "Align.h"

#define STUB_PLEASE_REPLACE(x) (x)

//-------------------------------------------------------------
// PrintME()
//
// Write your alignment printing function here
//-------------------------------------------------------------

Align::Info Align::PrintME(void *pData, int StructSize, char *pString)
{
	// Use Trace::out(...) to display the data layout and padding
	// Mimic the KeenanSampleOutput_Debug.txt

        // EXACTLY or the grading system will give a 0
	
	int paddingBytes = 0;

	Trace::out("%s:", pString);
	for (int i = 0; i < StructSize; i++)
	{
		if (i % 4 == 0) { Trace::out("\n  0x%02x: ", i); }
		unsigned char *charToPrint = (((unsigned char *)pData) + i);
		if (*charToPrint == 170) { paddingBytes++; }
		Trace::out("%02x ", *charToPrint);
	}
	Trace::out("\n------------------------\n");
	Trace::out("size: %d  padding : %d\n", StructSize, paddingBytes);

	Info info;
	info.NumBytesOfPadding = paddingBytes;
	info.NumTotalBytes = StructSize;

	return info;
}

// ---  End of File ---------------
