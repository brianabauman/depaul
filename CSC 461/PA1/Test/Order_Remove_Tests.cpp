//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------- 
#include "Framework.h"
#include "_UnitTestConfiguration.h"

#include "HotDog.h"
#include "Order.h"
#include "Stand.h"

// --- DO NOT MODIFY ---
TEST(Remove_Orders, OrderGroup, Remove_Orders_Test_Enable)
{
	// -----------------------------------------------
	// Create a Jamie order
	// -----------------------------------------------
	Order *pJamieOrder = new Order(Name::Jaime);
		CHECK(pJamieOrder != 0);
		CHECK(pJamieOrder->GetName() == Name::Jaime);
		CHECK(pJamieOrder->GetNext() == 0);
		CHECK(pJamieOrder->GetPrev() == 0);

		HotDog  *A = new HotDog();
		CHECK(A != 0);

		A->Add(Condiments::Yellow_Mustard);
		A->Add(Condiments::Chopped_Onions);
		A->Add(Condiments::Pickle_Spear);
		A->Add(Condiments::Celery_Salt);
		CHECK(A->GetCondiments() == 0xAA);

	pJamieOrder->Add(A);

		HotDog  *B = new HotDog();
		CHECK(B != 0);

		B->Add(Condiments::Yellow_Mustard);
		B->Add(Condiments::Chopped_Onions);
		B->Add(Condiments::Pickle_Spear);
		B->Add(Condiments::Celery_Salt);
		B->Add(Condiments::Ketchup);
		B->Add(Condiments::Tomato_Wedge);
		CHECK(B->GetCondiments() == 0xBB);

	pJamieOrder->Add(B);

		HotDog  *C = new HotDog();
		CHECK(C != 0);

		C->Add(Condiments::Green_Relish);
		C->Add(Condiments::Chopped_Onions);
		C->Add(Condiments::Sport_Peppers);
		C->Add(Condiments::Celery_Salt);
		CHECK(C->GetCondiments() == 0xCC);

	pJamieOrder->Add(C);

		HotDog  *D = new HotDog();
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
	// Create a Cersei order
	// -----------------------------------------------
	Order *pCerseiOrder = new Order(Name::Cersei);
		CHECK(pCerseiOrder != 0);
		CHECK(pCerseiOrder->GetName() == Name::Cersei);
		CHECK(pCerseiOrder->GetNext() == 0);
		CHECK(pCerseiOrder->GetPrev() == 0);

		HotDog  *E = new HotDog();
		CHECK(E != 0);

		E->Add(Condiments::Everything);
		E->Minus(Condiments::Tomato_Wedge);
		CHECK(E->GetCondiments() == 0xEE);

	pCerseiOrder->Add(E);

		HotDog  *F = new HotDog();
		CHECK(F != 0);

		F->Add(Condiments::Everything);
		F->Add(Condiments::Ketchup);
		CHECK(F->GetCondiments() == 0xFF);

	pCerseiOrder->Add(F);

		pDog = pCerseiOrder->GetHead();
		CHECK(pDog != 0);

		CHECK(pDog->GetCondiments() == 0xEE);
		CHECK(pDog->GetPrev() == 0);
		CHECK(pDog->GetNext()->GetCondiments() == 0xFF);

		pDog = pDog->GetNext();
		CHECK(pDog->GetCondiments() == 0xFF);
		CHECK(pDog->GetPrev()->GetCondiments() == 0xEE);
		CHECK(pDog->GetNext() == 0);


	// -----------------------------------------------
	// Create a Arya order
	// -----------------------------------------------
	Order *pAryaOrder = new Order(Name::Arya);
		CHECK(pAryaOrder != 0);
		CHECK(pAryaOrder->GetName() == Name::Arya);
		CHECK(pAryaOrder->GetNext() == 0);
		CHECK(pAryaOrder->GetPrev() == 0);

		HotDog  *M11 = new HotDog();
		CHECK(M11 != 0);

		M11->Add(Condiments::Ketchup);
		M11->Add(Condiments::Tomato_Wedge);
		CHECK(M11->GetCondiments() == 0x11);

	pAryaOrder->Add(M11);

		HotDog  *M22 = new HotDog();
		CHECK(M22 != 0);

		M22->Add(Condiments::Yellow_Mustard);
		M22->Add(Condiments::Pickle_Spear);
		CHECK(M22->GetCondiments() == 0x22);

	pAryaOrder->Add(M22);

		HotDog *M22_1 = new HotDog(*M22);
		CHECK(M22_1 != 0)

	pAryaOrder->Add(M22_1);

		HotDog *M22_2 = new HotDog(*M22);
		CHECK(M22_2 != 0);

	pAryaOrder->Add(M22_2);

		HotDog *M22_3 = new HotDog(*M22);
		CHECK(M22_3 != 0);

	pAryaOrder->Add(M22_3);

		pDog = pAryaOrder->GetHead();
		CHECK(pDog != 0);

		CHECK(pDog->GetCondiments() == 0x11);
		CHECK(pDog->GetPrev() == 0);
		CHECK(pDog->GetNext()->GetCondiments() == 0x22);

		pDog = pDog->GetNext();
		CHECK(pDog->GetCondiments() == 0x22);
		CHECK(pDog->GetPrev()->GetCondiments() == 0x11);
		CHECK(pDog->GetNext()->GetCondiments() == 0x22);

		pDog = pDog->GetNext();
		CHECK(pDog->GetCondiments() == 0x22);
		CHECK(pDog->GetPrev()->GetCondiments() == 0x22);
		CHECK(pDog->GetNext()->GetCondiments() == 0x22);

		pDog = pDog->GetNext();
		CHECK(pDog->GetCondiments() == 0x22);
		CHECK(pDog->GetPrev()->GetCondiments() == 0x22);
		CHECK(pDog->GetNext()->GetCondiments() == 0x22);

		pDog = pDog->GetNext();
		CHECK(pDog->GetCondiments() == 0x22);
		CHECK(pDog->GetPrev()->GetCondiments() == 0x22);
		CHECK(pDog->GetNext() == 0);

	// -----------------------------------------------
	// Create a Sansa order
	// -----------------------------------------------
	Order *pSansaOrder = new Order(Name::Sansa);
		CHECK(pSansaOrder != 0);
		CHECK(pSansaOrder->GetName() == Name::Sansa);
		CHECK(pSansaOrder->GetNext() == 0);
		CHECK(pSansaOrder->GetPrev() == 0);

		HotDog  *M33 = new HotDog();
		CHECK(M33 != 0);

		M33->Add(Condiments::Ketchup);
		M33->Add(Condiments::Yellow_Mustard);
		M33->Add(Condiments::Tomato_Wedge);
		M33->Add(Condiments::Pickle_Spear);
		CHECK(M33->GetCondiments() == 0x33);

	pSansaOrder->Add(M33);

		HotDog  *M00 = new HotDog();
		CHECK(M00 != 0);
		CHECK(M00->GetCondiments() == 0x00);

	pSansaOrder->Add(M00);

		HotDog  *M00_1 = new HotDog();
		CHECK(M00_1 != 0);
		CHECK(M00_1->GetCondiments() == 0x00);

	pSansaOrder->Add(M00_1);

		HotDog  *M44 = new HotDog();
		CHECK(M44 != 0);

		M44->Add(Condiments::Green_Relish);
		M44->Add(Condiments::Sport_Peppers);
		CHECK(M44->GetCondiments() == 0x44);

	pSansaOrder->Add(M44);

		pDog = pSansaOrder->GetHead();
		CHECK(pDog != 0);

		CHECK(pDog->GetCondiments() == 0x33);
		CHECK(pDog->GetPrev() == 0);
		CHECK(pDog->GetNext()->GetCondiments() == 0x0);

		pDog = pDog->GetNext();
		CHECK(pDog->GetCondiments() == 0x0);
		CHECK(pDog->GetPrev()->GetCondiments() == 0x33);
		CHECK(pDog->GetNext()->GetCondiments() == 0x0);

		pDog = pDog->GetNext();
		CHECK(pDog->GetCondiments() == 0x0);
		CHECK(pDog->GetPrev()->GetCondiments() == 0x0);
		CHECK(pDog->GetNext()->GetCondiments() == 0x44);

		pDog = pDog->GetNext();
		CHECK(pDog->GetCondiments() == 0x44);
		CHECK(pDog->GetPrev()->GetCondiments() == 0x0);
		CHECK(pDog->GetNext() == 0);

	// -----------------------------------------------
	// Stand - add 4 orders
	// -----------------------------------------------

	Stand stand;
		CHECK(stand.GetCurrOrders() == 0);
		CHECK(stand.GetPeakOrders() == 0);
		CHECK(stand.GetHead() == 0);

	stand.Add(pJamieOrder);
		CHECK(stand.GetCurrOrders() == 1);
		CHECK(stand.GetPeakOrders() == 1);

		Order *pOrder = stand.GetHead();
		CHECK(pOrder != 0);

		CHECK(pOrder->GetName() == Name::Jaime);
		CHECK(pOrder->GetPrev() == 0);
		CHECK(pOrder->GetNext() == 0);


	stand.Add(pCerseiOrder);
		CHECK(stand.GetCurrOrders() == 2);
		CHECK(stand.GetPeakOrders() == 2);

		pOrder = stand.GetHead();
		CHECK(pOrder != 0);

		CHECK(pOrder->GetName() == Name::Jaime);
		CHECK(pOrder->GetPrev() == 0);
		CHECK(pOrder->GetNext()->GetName() == Name::Cersei);

		pOrder = pOrder->GetNext();
		CHECK(pOrder != 0);

		CHECK(pOrder->GetName() == Name::Cersei);
		CHECK(pOrder->GetPrev()->GetName() == Name::Jaime);
		CHECK(pOrder->GetNext() == 0);

	stand.Add(pAryaOrder);

		CHECK(stand.GetCurrOrders() == 3);
		CHECK(stand.GetPeakOrders() == 3);

		pOrder = stand.GetHead();
		CHECK(pOrder != 0);

		CHECK(pOrder->GetName() == Name::Jaime);
		CHECK(pOrder->GetPrev() == 0);
		CHECK(pOrder->GetNext()->GetName() == Name::Cersei);

		pOrder = pOrder->GetNext();
		CHECK(pOrder != 0);

		CHECK(pOrder->GetName() == Name::Cersei);
		CHECK(pOrder->GetPrev()->GetName() == Name::Jaime);
		CHECK(pOrder->GetNext()->GetName() == Name::Arya);

		pOrder = pOrder->GetNext();
		CHECK(pOrder != 0);

		CHECK(pOrder->GetName() == Name::Arya);
		CHECK(pOrder->GetPrev()->GetName() == Name::Cersei);
		CHECK(pOrder->GetNext() == 0);

	stand.Add(pSansaOrder);

	// ---------------------------------------------------
	//  Verify the 4 orders with hotdogs
	// ---------------------------------------------------

	CHECK(stand.GetCurrOrders() == 4);
	CHECK(stand.GetPeakOrders() == 4);

	pOrder = stand.GetHead();
		CHECK(pOrder != 0);

		CHECK(pOrder->GetName() == Name::Jaime);
		CHECK(pOrder->GetPrev() == 0);
		CHECK(pOrder->GetNext()->GetName() == Name::Cersei);

	pDog = pOrder->GetHead();
		CHECK(pDog != 0);

		// Verify Jaime's order
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
		CHECK(pDog->GetNext() == 0)


	pOrder = pOrder->GetNext();
		CHECK(pOrder != 0);

		// Verify Cersei's order
		CHECK(pOrder->GetName() == Name::Cersei);
		CHECK(pOrder->GetPrev()->GetName() == Name::Jaime);
		CHECK(pOrder->GetNext()->GetName() == Name::Arya);

		pDog = pOrder->GetHead();
		CHECK(pDog != 0);

		CHECK(pDog->GetCondiments() == 0xEE);
		CHECK(pDog->GetPrev() == 0);
		CHECK(pDog->GetNext()->GetCondiments() == 0xFF);

		pDog = pDog->GetNext();
		CHECK(pDog->GetCondiments() == 0xFF);
		CHECK(pDog->GetPrev()->GetCondiments() == 0xEE);
		CHECK(pDog->GetNext() == 0);

	pOrder = pOrder->GetNext();
		CHECK(pOrder != 0);

		// Verify Arya's order
		CHECK(pOrder->GetName() == Name::Arya);
		CHECK(pOrder->GetPrev()->GetName() == Name::Cersei);
		CHECK(pOrder->GetNext()->GetName() == Name::Sansa);

		pDog = pOrder->GetHead();
		CHECK(pDog != 0);

		CHECK(pDog->GetCondiments() == 0x11);
		CHECK(pDog->GetPrev() == 0);
		CHECK(pDog->GetNext()->GetCondiments() == 0x22);

		pDog = pDog->GetNext();
		CHECK(pDog->GetCondiments() == 0x22);
		CHECK(pDog->GetPrev()->GetCondiments() == 0x11);
		CHECK(pDog->GetNext()->GetCondiments() == 0x22);

		pDog = pDog->GetNext();
		CHECK(pDog->GetCondiments() == 0x22);
		CHECK(pDog->GetPrev()->GetCondiments() == 0x22);
		CHECK(pDog->GetNext()->GetCondiments() == 0x22);

		pDog = pDog->GetNext();
		CHECK(pDog->GetCondiments() == 0x22);
		CHECK(pDog->GetPrev()->GetCondiments() == 0x22);
		CHECK(pDog->GetNext()->GetCondiments() == 0x22);

		pDog = pDog->GetNext();
		CHECK(pDog->GetCondiments() == 0x22);
		CHECK(pDog->GetPrev()->GetCondiments() == 0x22);
		CHECK(pDog->GetNext() == 0);

	pOrder = pOrder->GetNext();
		CHECK(pOrder != 0);

		// Verify Sansa's order
		CHECK(pOrder->GetName() == Name::Sansa);
		CHECK(pOrder->GetPrev()->GetName() == Name::Arya);
		CHECK(pOrder->GetNext() == 0);

		pDog = pOrder->GetHead();
		CHECK(pDog != 0);

		CHECK(pDog->GetCondiments() == 0x33);
		CHECK(pDog->GetPrev() == 0);
		CHECK(pDog->GetNext()->GetCondiments() == 0x0);

		pDog = pDog->GetNext();
		CHECK(pDog->GetCondiments() == 0x0);
		CHECK(pDog->GetPrev()->GetCondiments() == 0x33);
		CHECK(pDog->GetNext()->GetCondiments() == 0x0);

		pDog = pDog->GetNext();
		CHECK(pDog->GetCondiments() == 0x0);
		CHECK(pDog->GetPrev()->GetCondiments() == 0x0);
		CHECK(pDog->GetNext()->GetCondiments() == 0x44);

		pDog = pDog->GetNext();
		CHECK(pDog->GetCondiments() == 0x44);
		CHECK(pDog->GetPrev()->GetCondiments() == 0x0);
		CHECK(pDog->GetNext() == 0);

	// -----------------------------------------------
	// Remove Orders one at a Time
	// 
	//     Setup is done:  Jamie->Cersei->Arya->Sansa
	// -----------------------------------------------

		// -----------------------------------------------
		// Delete Arya
		//     Jamie->Cersei->Sansa
		// -----------------------------------------------
		stand.Remove(Name::Arya);

			CHECK(stand.GetCurrOrders() == 3);
			CHECK(stand.GetPeakOrders() == 4);

			pOrder = stand.GetHead();
			CHECK(pOrder != 0);

			CHECK(pOrder->GetName() == Name::Jaime);
			CHECK(pOrder->GetPrev() == 0);
			CHECK(pOrder->GetNext()->GetName() == Name::Cersei);

			pOrder = pOrder->GetNext();
			CHECK(pOrder != 0);

			CHECK(pOrder->GetName() == Name::Cersei);
			CHECK(pOrder->GetPrev()->GetName() == Name::Jaime);
			CHECK(pOrder->GetNext()->GetName() == Name::Sansa);
	
			pOrder = pOrder->GetNext();
			CHECK(pOrder != 0);

			CHECK(pOrder->GetName() == Name::Sansa);
			CHECK(pOrder->GetPrev()->GetName() == Name::Cersei);
			CHECK(pOrder->GetNext() == 0);

		// -----------------------------------------------
		// Delete Jamie
		//     Cersei->Sansa
		// -----------------------------------------------
		stand.Remove(Name::Jaime);

			CHECK(stand.GetCurrOrders() == 2);
			CHECK(stand.GetPeakOrders() == 4);

			pOrder = stand.GetHead();
			CHECK(pOrder != 0);

			CHECK(pOrder->GetName() == Name::Cersei);
			CHECK(pOrder->GetPrev() == 0);
			CHECK(pOrder->GetNext()->GetName() == Name::Sansa);

			pOrder = pOrder->GetNext();
			CHECK(pOrder != 0);

			CHECK(pOrder->GetName() == Name::Sansa);
			CHECK(pOrder->GetPrev()->GetName() == Name::Cersei);
			CHECK(pOrder->GetNext() == 0);

		// -----------------------------------------------
		// Delete Sansa
		//     Cersei
		// -----------------------------------------------
		stand.Remove(Name::Sansa);

			CHECK(stand.GetCurrOrders() == 1);
			CHECK(stand.GetPeakOrders() == 4);

			pOrder = stand.GetHead();
			CHECK(pOrder != 0);

			CHECK(pOrder->GetName() == Name::Cersei);
			CHECK(pOrder->GetPrev() == 0);
			CHECK(pOrder->GetNext() == 0);

		// -----------------------------------------------
		// Delete Cersei
		//     empty
		// -----------------------------------------------
		stand.Remove(Name::Cersei);

			CHECK(stand.GetCurrOrders() == 0);
			CHECK(stand.GetPeakOrders() == 4);

			pOrder = stand.GetHead();
			CHECK(pOrder == 0);

} TEST_END


// ---  End of File ---------------
