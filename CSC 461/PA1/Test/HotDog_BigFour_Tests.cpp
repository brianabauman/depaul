//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------- 
#include "Framework.h"
#include "_UnitTestConfiguration.h"

#include "HotDog.h"
#include "Order.h"

HotDog *pE = nullptr;

// --- DO NOT MODIFY ---
TEST_WITH_TEARDOWN(Big_Four, HotDogGroup, Big_Four_Test_Enable)
{
	// -----------------------------------------------
	// Default constructor
	// -----------------------------------------------
	HotDog  A;
		CHECK(A.GetNext() == 0);
		CHECK(A.GetPrev() == 0);
		CHECK(A.GetCondiments() == 0);

	HotDog  AA;
		CHECK(A.GetNext() == 0);
		CHECK(A.GetPrev() == 0);
		CHECK(A.GetCondiments() == 0);

	// -----------------------------------------------
	// B - complicated node used in copy constructor
	// -----------------------------------------------
	HotDog B;

		B.Add(Condiments::Everything);
		B.Minus(Condiments::Chopped_Onions);
		B.Minus(Condiments::Green_Relish);
		B.Add(Condiments::Ketchup);
		B.SetNext(&AA);
		B.SetPrev(&A);
		CHECK(B.GetNext() == &AA);
		CHECK(B.GetPrev() == &A);
		CHECK(B.GetCondiments() == 0xF3);

	// -----------------------------------------------
	// Copy constructor
	// -----------------------------------------------
	HotDog C(B);

		// Copy B into C
		CHECK(C.GetNext() == 0);
		CHECK(C.GetPrev() == 0);
		CHECK(C.GetCondiments() == 0xF3);

		// Make sure B isn't corrupted
		CHECK(B.GetNext() == &AA);
		CHECK(B.GetPrev() == &A);
		CHECK(B.GetCondiments() == 0xF3);

	// -----------------------------------------------
	// Assignment operator
	// -----------------------------------------------
	HotDog D;
		CHECK(D.GetNext() == 0);
		CHECK(D.GetPrev() == 0);
		CHECK(D.GetCondiments() == 0);

	D = B;

		// Copy B into C
		CHECK(D.GetNext() == 0);
		CHECK(D.GetPrev() == 0);
		CHECK(D.GetCondiments() == 0xF3);

		// Make sure B isn't corrupted
		CHECK(B.GetNext() == &AA);
		CHECK(B.GetPrev() == &A);
		CHECK(B.GetCondiments() == 0xF3);

	// -----------------------------------------------
	// Destructor
	// -----------------------------------------------
	pE = new HotDog();
		CHECK(pE != 0);

		pE->Add(Condiments::Yellow_Mustard);
		CHECK(pE->GetCondiments() == 0x2);
		CHECK(pE->GetNext() == 0);
		CHECK(pE->GetPrev() == 0);

	delete pE;
	pE = nullptr;

} TEST_END

TEST_TEARDOWN(Big_Four, HotDogGroup)
{
	delete pE;
}

// ---  End of File ---------------
