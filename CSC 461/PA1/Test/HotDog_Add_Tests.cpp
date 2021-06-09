//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------- 
#include "Framework.h"
#include "_UnitTestConfiguration.h"

#include "HotDog.h"
#include "Order.h"

// --- DO NOT MODIFY ---
TEST(Add_HotDog, HotDogGroup, Add_HotDog_Test_Enable)
{
	// -----------------------------------------------
	// Create an order
	// -----------------------------------------------
	Order JamieOrder(Name::Jaime);

		CHECK(JamieOrder.GetHead() == 0);
		CHECK(JamieOrder.GetName() == Name::Jaime);
		CHECK(JamieOrder.GetNext() == 0);
		CHECK(JamieOrder.GetPrev() == 0);

	// -----------------------------------------------
	// Add a HotDog to an Order
	// -----------------------------------------------
	HotDog  *A = new HotDog();
		CHECK(A != 0);

		A->Add(Condiments::Yellow_Mustard);
		A->Add(Condiments::Chopped_Onions);
		A->Add(Condiments::Pickle_Spear);
		A->Add(Condiments::Celery_Salt);
		CHECK(A->GetCondiments() == 0xAA);

		JamieOrder.Add(A);

		HotDog *pDog = JamieOrder.GetHead();
		CHECK(pDog != 0);

		CHECK(pDog->GetCondiments() == 0xAA);
		CHECK(pDog->GetPrev() == 0);
		CHECK(pDog->GetNext() == 0);

	// -----------------------------------------------
	// Add a HotDog to an Order
	// -----------------------------------------------
	HotDog  *B = new HotDog();
		CHECK(B != 0);

		B->Add(Condiments::Yellow_Mustard);
		B->Add(Condiments::Chopped_Onions);
		B->Add(Condiments::Pickle_Spear);
		B->Add(Condiments::Celery_Salt);
		B->Add(Condiments::Ketchup);
		B->Add(Condiments::Tomato_Wedge);
		CHECK(B->GetCondiments() == 0xBB);

	JamieOrder.Add(B);

		pDog = JamieOrder.GetHead();
		CHECK(pDog != 0);

		CHECK(pDog->GetCondiments() == 0xAA);
		CHECK(pDog->GetPrev() == 0);
		CHECK(pDog->GetNext()->GetCondiments() == 0xBB);

		pDog = pDog->GetNext();
		CHECK(pDog->GetCondiments() == 0xBB);
		CHECK(pDog->GetPrev()->GetCondiments() == 0xAA);
		CHECK(pDog->GetNext() == 0);

	// -----------------------------------------------
	// Add a HotDog to an Order
	// -----------------------------------------------
	HotDog  *C = new HotDog();
		CHECK(C != 0);

		C->Add(Condiments::Green_Relish);
		C->Add(Condiments::Chopped_Onions);
		C->Add(Condiments::Sport_Peppers);
		C->Add(Condiments::Celery_Salt);
		CHECK(C->GetCondiments() == 0xCC);

	JamieOrder.Add(C);

		pDog = JamieOrder.GetHead();
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
		CHECK(pDog->GetNext() == 0);

	// -----------------------------------------------
	// Add a HotDog to an Order
	// -----------------------------------------------
	HotDog  *D = new HotDog();
		CHECK(D != 0);

		D->Add(Condiments::Green_Relish);
		D->Add(Condiments::Chopped_Onions);
		D->Add(Condiments::Sport_Peppers);
		D->Add(Condiments::Celery_Salt);
		D->Add(Condiments::Ketchup);
		D->Add(Condiments::Tomato_Wedge);
		CHECK(D->GetCondiments() == 0xDD);

	JamieOrder.Add(D);

		pDog = JamieOrder.GetHead();
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

} TEST_END


// ---  End of File ---------------
