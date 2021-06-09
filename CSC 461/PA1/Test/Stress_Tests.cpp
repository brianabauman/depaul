//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------- 
#include "Framework.h"
#include "_UnitTestConfiguration.h"

#include "HotDog.h"
#include "Order.h"
#include "Stand.h"

// --- DO NOT MODIFY ---
TEST( ManyOperationsTogether, StressGroup, ManyOperationsTogether_Test_Enable)
{

	// ----------------------------------------------------
	// Jamie order
	// ----------------------------------------------------

	HotDog  *pHotdog_A = new HotDog();
	CHECK(pHotdog_A != 0);
	pHotdog_A->Add(Condiments::Everything);

	HotDog  *pHotdog_B = new HotDog();
	CHECK(pHotdog_B != 0);
	pHotdog_B->Add(Condiments::Yellow_Mustard);
	pHotdog_B->Add(Condiments::Sport_Peppers);

	HotDog  *pHotdog_C = new HotDog();
	CHECK(pHotdog_C != 0);
	pHotdog_C->Add(Condiments::Celery_Salt);
	pHotdog_C->Add(Condiments::Tomato_Wedge);
	pHotdog_C->Add(Condiments::Green_Relish);

	Order *pOrder_Jamie = new Order(Name::Jaime);
	CHECK(pOrder_Jamie != 0);
	pOrder_Jamie->Add(pHotdog_A);
	pOrder_Jamie->Add(pHotdog_B);
	pOrder_Jamie->Add(pHotdog_C);

		// ----------------------------------------------------
		// Check Jamie order
		// ----------------------------------------------------

		HotDog *pDog = pOrder_Jamie->GetHead();
		CHECK(pDog != 0);

		CHECK(pDog->GetCondiments() == 0xFE);
		CHECK(pDog->GetPrev() == 0);
		CHECK(pDog->GetNext()->GetCondiments() == 0x42);

		pDog = pDog->GetNext();
		CHECK(pDog->GetCondiments() == 0x42);
		CHECK(pDog->GetPrev()->GetCondiments() == 0xFE);
		CHECK(pDog->GetNext()->GetCondiments() == 0x94);

		pDog = pDog->GetNext();
		CHECK(pDog->GetCondiments() == 0x94);
		CHECK(pDog->GetPrev()->GetCondiments() == 0x42);
		CHECK(pDog->GetNext() == 0);

	// ----------------------------------------------------
	// Cersei order
	// ----------------------------------------------------

	HotDog *pHotdog_D = new HotDog();
	CHECK(pHotdog_D != 0);
	pHotdog_D->Add(Condiments::Plain);
	pHotdog_D->Add(Condiments::Celery_Salt);
	pHotdog_D->Add(Condiments::Tomato_Wedge);

	HotDog *pHotdog_D1 = new HotDog(*pHotdog_D);
	CHECK(pHotdog_D1 != 0);

	HotDog *pHotdog_D2 = new HotDog();
	CHECK(pHotdog_D2 != 0);
	*pHotdog_D2 = *pHotdog_D;

	Order *pOrder_Cersei = new Order(Name::Cersei);
	CHECK(pOrder_Cersei != 0);
	pOrder_Cersei->Add(pHotdog_D);
	pOrder_Cersei->Add(pHotdog_D1);
	pOrder_Cersei->Add(pHotdog_D2);

		// ----------------------------------------------------
		// Check Cersei order
		// ----------------------------------------------------

		pDog = pOrder_Cersei->GetHead();
		CHECK(pDog != 0);

		CHECK(pDog->GetCondiments() == 0x90);
		CHECK(pDog->GetPrev() == 0);
		CHECK(pDog->GetNext()->GetCondiments() == 0x90);

		pDog = pDog->GetNext();
		CHECK(pDog->GetCondiments() == 0x90);
		CHECK(pDog->GetPrev()->GetCondiments() == 0x90);
		CHECK(pDog->GetNext()->GetCondiments() == 0x90);

		pDog = pDog->GetNext();
		CHECK(pDog->GetCondiments() == 0x90);
		CHECK(pDog->GetPrev()->GetCondiments() == 0x90);
		CHECK(pDog->GetNext() == 0);

	// ----------------------------------------------------
	// Arya order
	// ----------------------------------------------------

	HotDog *pHotdog_E = new HotDog();
	CHECK(pHotdog_E != 0);
	pHotdog_E->Add(Condiments::Everything);
	pHotdog_E->Minus(Condiments::Sport_Peppers);

	Order *pOrder_Arya = new Order(Name::Arya);
	CHECK(pOrder_Arya != 0);
	pOrder_Arya->Add(pHotdog_E);
	
		// ----------------------------------------------------
		// Check Arya order
		// ----------------------------------------------------

		pDog = pOrder_Arya->GetHead();
		CHECK(pDog != 0);

		CHECK(pDog->GetCondiments() == 0xBE);
		CHECK(pDog->GetPrev() == 0);
		CHECK(pDog->GetNext() == 0);

	// ----------------------------------------------------
	// Sansa order
	// ----------------------------------------------------

	HotDog *pHotdog_F = new HotDog();
	CHECK(pHotdog_F != 0);
	pHotdog_F->Add(Condiments::Chopped_Onions);
	pHotdog_F->Add(Condiments::Yellow_Mustard);
	pHotdog_F->Add(Condiments::Green_Relish);

	HotDog *pHotdog_G = new HotDog();
	CHECK(pHotdog_G != 0);
	pHotdog_G->Add(Condiments::Everything);
	pHotdog_G->Add(Condiments::Ketchup);
	pHotdog_G->Minus(Condiments::Yellow_Mustard);

	Order *pOrder_Sansa = new Order(Name::Sansa);
	CHECK(pOrder_Sansa != 0);
	pOrder_Sansa->Add(pHotdog_F);
	pOrder_Sansa->Add(pHotdog_G);

		// ----------------------------------------------------
		// Check Sansa order
		// ----------------------------------------------------

		pDog = pOrder_Sansa->GetHead();
		CHECK(pDog != 0);

		CHECK(pDog->GetCondiments() == 0x0E);
		CHECK(pDog->GetPrev() == 0);
		CHECK(pDog->GetNext()->GetCondiments() == 0xFD);

		pDog = pDog->GetNext();
		CHECK(pDog->GetCondiments() == 0xFD);
		CHECK(pDog->GetPrev()->GetCondiments() == 0x0E);
		CHECK(pDog->GetNext() == 0);

	// ----------------------------------------------------
	// Samwell order: assignment operator
	// ----------------------------------------------------

	Order *pOrder_Samwell = new Order();
	CHECK(pOrder_Samwell != 0);
	*pOrder_Samwell = *pOrder_Arya;
	pOrder_Samwell->SetName(Name::Samwell);

		// ----------------------------------------------------
		// Check Samwell order
		// ----------------------------------------------------

		pDog = pOrder_Samwell->GetHead();
		CHECK(pDog != 0);

		CHECK(pDog->GetCondiments() == 0xBE);
		CHECK(pDog->GetPrev() == 0);
		CHECK(pDog->GetNext() == 0);


	// ----------------------------------------------------
	// Jon Order: copy constructor
	// ----------------------------------------------------

	Order *pOrder_Jon = new Order(*pOrder_Sansa);
	assert(pOrder_Jon);
	pOrder_Jon->SetName(Name::Jon);

		// ----------------------------------------------------
		// Check Jon order
		// ----------------------------------------------------

		pDog = pOrder_Jon->GetHead();
		CHECK(pDog != 0);

		CHECK(pDog->GetCondiments() == 0x0E);
		CHECK(pDog->GetPrev() == 0);
		CHECK(pDog->GetNext()->GetCondiments() == 0xFD);

		pDog = pDog->GetNext();
		CHECK(pDog->GetCondiments() == 0xFD);
		CHECK(pDog->GetPrev()->GetCondiments() == 0x0E);
		CHECK(pDog->GetNext() == 0);

	// ----------------------------------------------------
	// Delete Arya order
	// ----------------------------------------------------

	delete pOrder_Arya;

	// ----------------------------------------------------
	// Delete HotDog B from Jamie's order
	// ----------------------------------------------------

	pOrder_Jamie->Remove(pHotdog_B);

			// ----------------------------------------------------
			// Check Jamie order
			// ----------------------------------------------------

			pDog = pOrder_Jamie->GetHead();
			CHECK(pDog != 0);

			CHECK(pDog->GetCondiments() == 0xFE);
			CHECK(pDog->GetPrev() == 0);
			CHECK(pDog->GetNext()->GetCondiments() == 0x94);

			pDog = pDog->GetNext();
			CHECK(pDog->GetCondiments() == 0x94);
			CHECK(pDog->GetPrev()->GetCondiments() == 0xFE);
			CHECK(pDog->GetNext() == 0);

	// -----------------------------------------------
	// Stand - add 5 orders
	// -----------------------------------------------

	Stand *pStand = new Stand();
	CHECK(pStand != 0);

	CHECK(pStand->GetCurrOrders() == 0);
	CHECK(pStand->GetPeakOrders() == 0);
	CHECK(pStand->GetHead() == 0);

	pStand->Add(pOrder_Jamie);

		// -------------------------------------------------------
		// Check stand
		// -------------------------------------------------------

		CHECK(pStand->GetCurrOrders() == 1);
		CHECK(pStand->GetPeakOrders() == 1);
	
		Order *pOrder = pStand->GetHead();
		CHECK(pOrder != 0);

		CHECK(pOrder->GetName() == Name::Jaime);
		CHECK(pOrder->GetPrev() == 0);
		CHECK(pOrder->GetNext() == 0);

	pStand->Add(pOrder_Cersei);

		// -------------------------------------------------------
		// Check stand
		// -------------------------------------------------------

		CHECK(pStand->GetCurrOrders() == 2);
		CHECK(pStand->GetPeakOrders() == 2);

		pOrder = pStand->GetHead();
		CHECK(pOrder != 0);

		CHECK(pOrder->GetName() == Name::Jaime);
		CHECK(pOrder->GetPrev() == 0);
		CHECK(pOrder->GetNext()->GetName() == Name::Cersei);

		pOrder = pOrder->GetNext();
		CHECK(pOrder != 0);

		CHECK(pOrder->GetName() == Name::Cersei);
		CHECK(pOrder->GetPrev()->GetName() == Name::Jaime);
		CHECK(pOrder->GetNext() == 0);


	pStand->Add(pOrder_Samwell);

		// -------------------------------------------------------
		// Check stand
		// -------------------------------------------------------

		CHECK(pStand->GetCurrOrders() == 3);
		CHECK(pStand->GetPeakOrders() == 3);

		pOrder = pStand->GetHead();
		CHECK(pOrder != 0);

		CHECK(pOrder->GetName() == Name::Jaime);
		CHECK(pOrder->GetPrev() == 0);
		CHECK(pOrder->GetNext()->GetName() == Name::Cersei);

		pOrder = pOrder->GetNext();
		CHECK(pOrder != 0);

		CHECK(pOrder->GetName() == Name::Cersei);
		CHECK(pOrder->GetPrev()->GetName() == Name::Jaime);
		CHECK(pOrder->GetNext()->GetName() == Name::Samwell);

		pOrder = pOrder->GetNext();
		CHECK(pOrder != 0);

		CHECK(pOrder->GetName() == Name::Samwell);
		CHECK(pOrder->GetPrev()->GetName() == Name::Cersei);
		CHECK(pOrder->GetNext() == 0);


	pStand->Add(pOrder_Sansa);

		// -------------------------------------------------------
		// Check stand
		// -------------------------------------------------------

		CHECK(pStand->GetCurrOrders() == 4);
		CHECK(pStand->GetPeakOrders() == 4);

		pOrder = pStand->GetHead();
		CHECK(pOrder != 0);

		CHECK(pOrder->GetName() == Name::Jaime);
		CHECK(pOrder->GetPrev() == 0);
		CHECK(pOrder->GetNext()->GetName() == Name::Cersei);

		pOrder = pOrder->GetNext();
		CHECK(pOrder != 0);

		CHECK(pOrder->GetName() == Name::Cersei);
		CHECK(pOrder->GetPrev()->GetName() == Name::Jaime);
		CHECK(pOrder->GetNext()->GetName() == Name::Samwell);

		pOrder = pOrder->GetNext();
		CHECK(pOrder != 0);

		CHECK(pOrder->GetName() == Name::Samwell);
		CHECK(pOrder->GetPrev()->GetName() == Name::Cersei);
		CHECK(pOrder->GetNext()->GetName() == Name::Sansa);

		pOrder = pOrder->GetNext();
		CHECK(pOrder != 0);

		CHECK(pOrder->GetName() == Name::Sansa);
		CHECK(pOrder->GetPrev()->GetName() == Name::Samwell);
		CHECK(pOrder->GetNext() == 0);

	pStand->Add(pOrder_Jon);

		// -------------------------------------------------------
		// Check stand
		// -------------------------------------------------------

		CHECK(pStand->GetCurrOrders() == 5);
		CHECK(pStand->GetPeakOrders() == 5);

		pOrder = pStand->GetHead();
		CHECK(pOrder != 0);

		CHECK(pOrder->GetName() == Name::Jaime);
		CHECK(pOrder->GetPrev() == 0);
		CHECK(pOrder->GetNext()->GetName() == Name::Cersei);

			// ----------------------------------------------------
			// Check Jamie order
			// ----------------------------------------------------

			pDog = pOrder->GetHead();
			CHECK(pDog != 0);

			CHECK(pDog->GetCondiments() == 0xFE);
			CHECK(pDog->GetPrev() == 0);
			CHECK(pDog->GetNext()->GetCondiments() == 0x94);

			pDog = pDog->GetNext();
			CHECK(pDog->GetCondiments() == 0x94);
			CHECK(pDog->GetPrev()->GetCondiments() == 0xFE);
			CHECK(pDog->GetNext() == 0);

		pOrder = pOrder->GetNext();
		CHECK(pOrder != 0);

		CHECK(pOrder->GetName() == Name::Cersei);
		CHECK(pOrder->GetPrev()->GetName() == Name::Jaime);
		CHECK(pOrder->GetNext()->GetName() == Name::Samwell);

			// ----------------------------------------------------
			// Check Cersei order
			// ----------------------------------------------------

			pDog = pOrder->GetHead();
			CHECK(pDog != 0);

			CHECK(pDog->GetCondiments() == 0x90);
			CHECK(pDog->GetPrev() == 0);
			CHECK(pDog->GetNext()->GetCondiments() == 0x90);

			pDog = pDog->GetNext();
			CHECK(pDog->GetCondiments() == 0x90);
			CHECK(pDog->GetPrev()->GetCondiments() == 0x90);
			CHECK(pDog->GetNext()->GetCondiments() == 0x90);

			pDog = pDog->GetNext();
			CHECK(pDog->GetCondiments() == 0x90);
			CHECK(pDog->GetPrev()->GetCondiments() == 0x90);
			CHECK(pDog->GetNext() == 0);

		pOrder = pOrder->GetNext();
		CHECK(pOrder != 0);

		CHECK(pOrder->GetName() == Name::Samwell);
		CHECK(pOrder->GetPrev()->GetName() == Name::Cersei);
		CHECK(pOrder->GetNext()->GetName() == Name::Sansa);

			// ----------------------------------------------------
			// Check Samwell order
			// ----------------------------------------------------

			pDog = pOrder->GetHead();
			CHECK(pDog != 0);

			CHECK(pDog->GetCondiments() == 0xBE);
			CHECK(pDog->GetPrev() == 0);
			CHECK(pDog->GetNext() == 0);

		pOrder = pOrder->GetNext();
		CHECK(pOrder != 0);

		CHECK(pOrder->GetName() == Name::Sansa);
		CHECK(pOrder->GetPrev()->GetName() == Name::Samwell);
		CHECK(pOrder->GetNext()->GetName() == Name::Jon);

			// ----------------------------------------------------
			// Check Sansa order
			// ----------------------------------------------------

			pDog = pOrder->GetHead();
			CHECK(pDog != 0);

			CHECK(pDog->GetCondiments() == 0x0E);
			CHECK(pDog->GetPrev() == 0);
			CHECK(pDog->GetNext()->GetCondiments() == 0xFD);

			pDog = pDog->GetNext();
			CHECK(pDog->GetCondiments() == 0xFD);
			CHECK(pDog->GetPrev()->GetCondiments() == 0x0E);
			CHECK(pDog->GetNext() == 0);


		pOrder = pOrder->GetNext();
		CHECK(pOrder != 0);

		CHECK(pOrder->GetName() == Name::Jon);
		CHECK(pOrder->GetPrev()->GetName() == Name::Sansa);
		CHECK(pOrder->GetNext() == 0);

			// ----------------------------------------------------
			// Check Jon order
			// ----------------------------------------------------

			pDog = pOrder->GetHead();
			CHECK(pDog != 0);

			CHECK(pDog->GetCondiments() == 0x0E);
			CHECK(pDog->GetPrev() == 0);
			CHECK(pDog->GetNext()->GetCondiments() == 0xFD);

			pDog = pDog->GetNext();
			CHECK(pDog->GetCondiments() == 0xFD);
			CHECK(pDog->GetPrev()->GetCondiments() == 0x0E);
			CHECK(pDog->GetNext() == 0);


	// -----------------------------------------------
	// Stand - remove 4 orders in a specific order
	// -----------------------------------------------

	// Remove
	pStand->Remove(Name::Cersei);

		// -------------------------------------------------------
		// Check stand
		// -------------------------------------------------------

		CHECK(pStand->GetCurrOrders() == 4);
		CHECK(pStand->GetPeakOrders() == 5);
		pOrder = pStand->GetHead();
		CHECK(pOrder != 0);

		pOrder = pStand->GetHead();
		CHECK(pOrder != 0);

		CHECK(pOrder->GetName() == Name::Jaime);
		CHECK(pOrder->GetPrev() == 0);
		CHECK(pOrder->GetNext()->GetName() == Name::Samwell);

		pOrder = pOrder->GetNext();
		CHECK(pOrder != 0);

		CHECK(pOrder->GetName() == Name::Samwell);
		CHECK(pOrder->GetPrev()->GetName() == Name::Jaime);
		CHECK(pOrder->GetNext()->GetName() == Name::Sansa);

		pOrder = pOrder->GetNext();
		CHECK(pOrder != 0);

		CHECK(pOrder->GetName() == Name::Sansa);
		CHECK(pOrder->GetPrev()->GetName() == Name::Samwell);
		CHECK(pOrder->GetNext()->GetName() == Name::Jon);

		pOrder = pOrder->GetNext();
		CHECK(pOrder != 0);

		CHECK(pOrder->GetName() == Name::Jon);
		CHECK(pOrder->GetPrev()->GetName() == Name::Sansa);
		CHECK(pOrder->GetNext() == 0);


	// Remove
	pStand->Remove(Name::Samwell);

		// -------------------------------------------------------
		// Check stand
		// -------------------------------------------------------

		CHECK(pStand->GetCurrOrders() == 3);
		CHECK(pStand->GetPeakOrders() == 5);
		pOrder = pStand->GetHead();
		CHECK(pOrder != 0);

		pOrder = pStand->GetHead();
		CHECK(pOrder != 0);

		CHECK(pOrder->GetName() == Name::Jaime);
		CHECK(pOrder->GetPrev() == 0);
		CHECK(pOrder->GetNext()->GetName() == Name::Sansa);

		pOrder = pOrder->GetNext();
		CHECK(pOrder != 0);

		CHECK(pOrder->GetName() == Name::Sansa);
		CHECK(pOrder->GetPrev()->GetName() == Name::Jaime);
		CHECK(pOrder->GetNext()->GetName() == Name::Jon);

		pOrder = pOrder->GetNext();
		CHECK(pOrder != 0);

		CHECK(pOrder->GetName() == Name::Jon);
		CHECK(pOrder->GetPrev()->GetName() == Name::Sansa);
		CHECK(pOrder->GetNext() == 0);
			

	// Remove
	pStand->Remove(Name::Jaime);

		// -------------------------------------------------------
		// Check stand
		// -------------------------------------------------------

		CHECK(pStand->GetCurrOrders() == 2);
		CHECK(pStand->GetPeakOrders() == 5);
		pOrder = pStand->GetHead();
		CHECK(pOrder != 0);

		pOrder = pStand->GetHead();
		CHECK(pOrder != 0);

		CHECK(pOrder->GetName() == Name::Sansa);
		CHECK(pOrder->GetPrev() == 0);
		CHECK(pOrder->GetNext()->GetName() == Name::Jon);

		pOrder = pOrder->GetNext();
		CHECK(pOrder != 0);

		CHECK(pOrder->GetName() == Name::Jon);
		CHECK(pOrder->GetPrev()->GetName() == Name::Sansa);
		CHECK(pOrder->GetNext() == 0);
			

	// Remove
	pStand->Remove(Name::Jon);
			
		// -------------------------------------------------------
		// Check stand
		// -------------------------------------------------------

		CHECK(pStand->GetCurrOrders() == 1);
		CHECK(pStand->GetPeakOrders() == 5);
		pOrder = pStand->GetHead();
		CHECK(pOrder != 0);

		pOrder = pStand->GetHead();
		CHECK(pOrder != 0);

		CHECK(pOrder->GetName() == Name::Sansa);
		CHECK(pOrder->GetPrev() == 0);
		CHECK(pOrder->GetNext() == 0);


	delete pStand;

} TEST_END


// ---  End of File ---------------
