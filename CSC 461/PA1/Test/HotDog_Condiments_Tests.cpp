//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2019
//----------------------------------------------------------------------------- 
#include "Framework.h"
#include "_UnitTestConfiguration.h"

#include "HotDog.h"
#include "Order.h"

// --- DO NOT MODIFY ---
TEST(Condiments_HotDog, HotdogGroup, Condiments_HotDog_Test_Enable)
{
	// -----------------------------------------------
	// Jaime order:
	// -----------------------------------------------
	HotDog  hotdog_A;
	hotdog_A.Add(Condiments::Everything);
	CHECK(hotdog_A.GetCondiments() == 0xFE);

	HotDog  hotdog_B;
	hotdog_B.Add(Condiments::Yellow_Mustard);
	hotdog_B.Add(Condiments::Sport_Peppers);
	CHECK(hotdog_B.GetCondiments() == 0x42);

	HotDog  hotdog_C;
	hotdog_C.Add(Condiments::Celery_Salt);
	hotdog_C.Add(Condiments::Tomato_Wedge);
	hotdog_C.Add(Condiments::Green_Relish);
	CHECK(hotdog_C.GetCondiments() == 0x94);

	// -----------------------------------------------
	// Cersei order:
	// -----------------------------------------------
	HotDog hotdog_D;
	hotdog_D.Add(Condiments::Plain);
	CHECK(hotdog_D.GetCondiments() == 0x0);

	// -----------------------------------------------
	// Arya order:
	// -----------------------------------------------
	HotDog hotdog_E;
	hotdog_E.Add(Condiments::Everything);
	hotdog_E.Minus(Condiments::Green_Relish);
	hotdog_E.Add(Condiments::Everything);
	hotdog_E.Add(Condiments::Ketchup);
	hotdog_E.Minus(Condiments::Sport_Peppers);
	CHECK(hotdog_E.GetCondiments() == 0xBF);

	// -----------------------------------------------
	// Sansa order:
	// -----------------------------------------------
	HotDog hotdog_F;
	hotdog_F.Add(Condiments::Chopped_Onions);
	hotdog_F.Add(Condiments::Yellow_Mustard);
	hotdog_F.Add(Condiments::Green_Relish);
	hotdog_F.Minus(Condiments::Green_Relish);
	hotdog_F.Minus(Condiments::Green_Relish);
	CHECK(hotdog_F.GetCondiments() == 0x0A);

	HotDog hotdog_G;
	hotdog_G.Add(Condiments::Everything);
	hotdog_G.Add(Condiments::Ketchup);
	hotdog_G.Minus(Condiments::Yellow_Mustard);
	CHECK(hotdog_G.GetCondiments() == 0xFD);

	// -----------------------------------------------
	// Samwell order:
	// -----------------------------------------------
	HotDog hotdog_H;
	hotdog_H.Add(Condiments::Chopped_Onions);
	hotdog_H.Add(Condiments::Yellow_Mustard);
	hotdog_H.Add(Condiments::Celery_Salt);
	hotdog_H.Minus(Condiments::Celery_Salt);
	hotdog_H.Add(Condiments::Ketchup);
	hotdog_H.Add(Condiments::Celery_Salt);
	CHECK(hotdog_H.GetCondiments() == 0x8B);

	HotDog hotdog_I;
	hotdog_I.Add(Condiments::Yellow_Mustard);
	hotdog_I.Add(Condiments::Pickle_Spear);
	CHECK(hotdog_I.GetCondiments() == 0x22);

	// -----------------------------------------------
	// Tyrion order:
	// -----------------------------------------------
	HotDog hotdog_J;
	hotdog_J.Add(Condiments::Green_Relish);
	hotdog_J.Add(Condiments::Yellow_Mustard);
	hotdog_J.Add(Condiments::Sport_Peppers);
	hotdog_J.Add(Condiments::Yellow_Mustard);
	CHECK(hotdog_J.GetCondiments() == 0x46);
} TEST_END


// ---  End of File ---------------

