//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------- 
#include "Framework.h"
#include "_UnitTestConfiguration.h"

#include "HotDog.h"
#include "Order.h"
#include "Stand.h"

Order *pJamieOrder = nullptr;

// --- DO NOT MODIFY ---
TEST_WITH_TEARDOWN(BigFour_Orders, OrderGroup, BigFour_Orders_Test_Enable)
{
	// -----------------------------------------------
	// Default constructor
	// -----------------------------------------------
	Order R;
	CHECK(R.GetName() == Name::Unknown)
	CHECK(R.GetHead() == 0);

	// -----------------------------------------------
	// Specialize constructor
	// -----------------------------------------------
	Order S(Name::Arya);
	CHECK(S.GetName() == Name::Arya);
	CHECK(S.GetHead() == 0);

	// -----------------------------------------------
	// Create a complicated order
	// -----------------------------------------------
	pJamieOrder = new Order(Name::Jaime);

		CHECK(pJamieOrder != 0);
		CHECK(pJamieOrder->GetName() == Name::Jaime);
		CHECK(pJamieOrder->GetNext() == 0);
		CHECK(pJamieOrder->GetPrev() == 0);

		HotDog *A = new HotDog();
		CHECK(A != 0);

		A->Add(Condiments::Yellow_Mustard);
		A->Add(Condiments::Chopped_Onions);
		A->Add(Condiments::Pickle_Spear);
		A->Add(Condiments::Celery_Salt);
		CHECK(A->GetCondiments() == 0xAA);

		pJamieOrder->Add(A);

		HotDog *B = new HotDog();
		CHECK(B != 0);

		B->Add(Condiments::Yellow_Mustard);
		B->Add(Condiments::Chopped_Onions);
		B->Add(Condiments::Pickle_Spear);
		B->Add(Condiments::Celery_Salt);
		B->Add(Condiments::Ketchup);
		B->Add(Condiments::Tomato_Wedge);
		CHECK(B->GetCondiments() == 0xBB);

		pJamieOrder->Add(B);

		HotDog *C = new HotDog();
		CHECK(C != 0);

		C->Add(Condiments::Green_Relish);
		C->Add(Condiments::Chopped_Onions);
		C->Add(Condiments::Sport_Peppers);
		C->Add(Condiments::Celery_Salt);
		CHECK(C->GetCondiments() == 0xCC);

		pJamieOrder->Add(C);

		HotDog *D = new HotDog();
		CHECK(D != 0);

		D->Add(Condiments::Green_Relish);
		D->Add(Condiments::Chopped_Onions);
		D->Add(Condiments::Sport_Peppers);
		D->Add(Condiments::Celery_Salt);
		D->Add(Condiments::Ketchup);
		D->Add(Condiments::Tomato_Wedge);
		CHECK(D->GetCondiments() == 0xDD);

		pJamieOrder->Add(D);

		HotDog *pDog = pJamieOrder->GetHead();
		CHECK(pDog != 0);

		CHECK(pDog->GetCondiments() == 0xAA);
		CHECK(pDog->GetPrev() == 0);
		CHECK(pDog->GetNext()->GetCondiments() == 0xBB);

		pDog = pDog->GetNext();
		CHECK(pDog->GetCondiments() == 0xBB);
		CHECK(pDog->GetPrev()->GetCondiments() == 0xAA);
		CHECK(pDog->GetNext()->GetCondiments() == 0xCC);

		pDog = pDog->GetNext();
		CHECK(pDog->GetCondiments() == 0xCC);
		CHECK(pDog->GetPrev()->GetCondiments() == 0xBB);
		CHECK(pDog->GetNext()->GetCondiments() == 0xDD);

		pDog = pDog->GetNext();
		CHECK(pDog->GetCondiments() == 0xDD);
		CHECK(pDog->GetPrev()->GetCondiments() == 0xCC);
		CHECK(pDog->GetNext() == 0);

	// -----------------------------------------------
	// Copy constructor - with deep copy
	// -----------------------------------------------
	Order T(*pJamieOrder);

		// Make verify deep copy
		CHECK(T.GetName() == pJamieOrder->GetName());
		CHECK(T.GetNext() == 0);
		CHECK(T.GetPrev() == 0);

		pDog = T.GetHead();
		CHECK(pDog != 0);

		CHECK(pDog->GetCondiments() == 0xAA);
		CHECK(pDog->GetPrev() == 0);
		CHECK(pDog->GetNext()->GetCondiments() == 0xBB);

		HotDog *T0 = pDog;

		pDog = pDog->GetNext();
		CHECK(pDog->GetCondiments() == 0xBB);
		CHECK(pDog->GetPrev()->GetCondiments() == 0xAA);
		CHECK(pDog->GetNext()->GetCondiments() == 0xCC);

		HotDog *T1 = pDog;

		pDog = pDog->GetNext();
		CHECK(pDog->GetCondiments() == 0xCC);
		CHECK(pDog->GetPrev()->GetCondiments() == 0xBB);
		CHECK(pDog->GetNext()->GetCondiments() == 0xDD);

		HotDog *T2 = pDog;

		pDog = pDog->GetNext();
		CHECK(pDog->GetCondiments() == 0xDD);
		CHECK(pDog->GetPrev()->GetCondiments() == 0xCC);
		CHECK(pDog->GetNext() == 0);

		HotDog *T3 = pDog;

		// Make sure Jamie isn't corrupted
		pDog = pJamieOrder->GetHead();
		CHECK(pDog != 0);

		CHECK(pDog->GetCondiments() == 0xAA);
		CHECK(pDog->GetPrev() == 0);
		CHECK(pDog->GetNext()->GetCondiments() == 0xBB);

		HotDog *S0 = pDog;

		pDog = pDog->GetNext();
		CHECK(pDog->GetCondiments() == 0xBB);
		CHECK(pDog->GetPrev()->GetCondiments() == 0xAA);
		CHECK(pDog->GetNext()->GetCondiments() == 0xCC);

		HotDog *S1 = pDog;

		pDog = pDog->GetNext();
		CHECK(pDog->GetCondiments() == 0xCC);
		CHECK(pDog->GetPrev()->GetCondiments() == 0xBB);
		CHECK(pDog->GetNext()->GetCondiments() == 0xDD);

		HotDog *S2 = pDog;

		pDog = pDog->GetNext();
		CHECK(pDog->GetCondiments() == 0xDD);
		CHECK(pDog->GetPrev()->GetCondiments() == 0xCC);
		CHECK(pDog->GetNext() == 0);

		HotDog *S3 = pDog;

		// Make sure they are not equal
		CHECK(T0 != S0);
		CHECK(T1 != S1);
		CHECK(T2 != S2);
		CHECK(T3 != S3);

	// -----------------------------------------------
	// Assignment operator
	// -----------------------------------------------
	Order M;
	CHECK(M.GetName() == Name::Unknown);
	CHECK(M.GetHead() == 0);

	M = *pJamieOrder;

		// Make verify deep copy
		CHECK(M.GetName() == pJamieOrder->GetName());
		CHECK(M.GetNext() == 0);
		CHECK(M.GetPrev() == 0);

		pDog = M.GetHead();
		CHECK(pDog != 0);

		CHECK(pDog->GetCondiments() == 0xAA);
		CHECK(pDog->GetPrev() == 0);
		CHECK(pDog->GetNext()->GetCondiments() == 0xBB);

		HotDog *M0 = pDog;

		pDog = pDog->GetNext();
		CHECK(pDog->GetCondiments() == 0xBB);
		CHECK(pDog->GetPrev()->GetCondiments() == 0xAA);
		CHECK(pDog->GetNext()->GetCondiments() == 0xCC);

		HotDog *M1 = pDog;

		pDog = pDog->GetNext();
		CHECK(pDog->GetCondiments() == 0xCC);
		CHECK(pDog->GetPrev()->GetCondiments() == 0xBB);
		CHECK(pDog->GetNext()->GetCondiments() == 0xDD);

		HotDog *M2 = pDog;

		pDog = pDog->GetNext();
		CHECK(pDog->GetCondiments() == 0xDD);
		CHECK(pDog->GetPrev()->GetCondiments() == 0xCC);
		CHECK(pDog->GetNext() == 0);

		HotDog *M3 = pDog;

		// Make sure Jamie isn't corrupted
		pDog = pJamieOrder->GetHead();
		CHECK(pDog != 0);

		CHECK(pDog->GetCondiments() == 0xAA);
		CHECK(pDog->GetPrev() == 0);
		CHECK(pDog->GetNext()->GetCondiments() == 0xBB);

		S0 = pDog;

		pDog = pDog->GetNext();
		CHECK(pDog->GetCondiments() == 0xBB);
		CHECK(pDog->GetPrev()->GetCondiments() == 0xAA);
		CHECK(pDog->GetNext()->GetCondiments() == 0xCC);

		S1 = pDog;

		pDog = pDog->GetNext();
		CHECK(pDog->GetCondiments() == 0xCC);
		CHECK(pDog->GetPrev()->GetCondiments() == 0xBB);
		CHECK(pDog->GetNext()->GetCondiments() == 0xDD);

		S2 = pDog;

		pDog = pDog->GetNext();
		CHECK(pDog->GetCondiments() == 0xDD);
		CHECK(pDog->GetPrev()->GetCondiments() == 0xCC);
		CHECK(pDog->GetNext() == 0);

		S3 = pDog;

		// Make sure they are not equal
		CHECK(M0 != S0);
		CHECK(M1 != S1);
		CHECK(M2 != S2);
		CHECK(M3 != S3);
		
	// -----------------------------------------------
	// destructor - is called freeing up all HotDogs
	// -----------------------------------------------
	delete pJamieOrder;
	pJamieOrder = nullptr;

} TEST_END

TEST_TEARDOWN(BigFour_Orders, OrderGroup)
{
	delete pJamieOrder;
}

// ---  End of File ---------------

