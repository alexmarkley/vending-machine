
#include "unity.h"
#include "Main.h"
#include "Common.h"
#include "CoinSlot.h"
#include "mock_Common.h"
#include "mock_Product.h"
#include "mock_CoinChanger.h"
#include "mock_CoinSlot.h"

#include <stdlib.h>

char *args[1] = {"./vending-machine"};
Product *products[3];
CoinChanger *changer;
CoinSlot *slot;

void setUp(void) {
}

void tearDown(void) {
}

void normalMainSetUp(void) {
	//Mock output, expect the initialization banner.
	CommonOutput_ExpectAndReturn(MAIN_INITIALIZATION_MESSAGE, 1);
	
	//Mock product creation.
	//(Need real allocated memory for the Product objects, not because Main dereferences them (it doesn't) but because Unity compares the memory blocks and it will crash if we use symbols instead of pointers to real allocated memory.)
	ProductCreate_ExpectAndReturn(products[0] = calloc(1, sizeof(Product))); //PRODA
	ProductCreate_ExpectAndReturn(products[1] = calloc(1, sizeof(Product))); //PRODB
	ProductCreate_ExpectAndReturn(products[2] = calloc(1, sizeof(Product))); //PRODC
	ProductSetStock_ExpectAndReturn(products[0], MAIN_PRODA_STOCK, true);
	ProductSetStock_ExpectAndReturn(products[1], MAIN_PRODB_STOCK, true);
	ProductSetStock_ExpectAndReturn(products[2], MAIN_PRODC_STOCK, true);
	ProductSetValue_ExpectAndReturn(products[0], MAIN_PRODA_VALUE, true);
	ProductSetValue_ExpectAndReturn(products[1], MAIN_PRODB_VALUE, true);
	ProductSetValue_ExpectAndReturn(products[2], MAIN_PRODC_VALUE, true);
	
	//Mock coinchanger creation.
	CoinChangerCreate_ExpectAndReturn(changer = calloc(1, sizeof(CoinChanger)));
	CoinChangerSetQuarters_ExpectAndReturn(changer, MAIN_COINCHANGER_QUARTERS, true);
	CoinChangerSetDimes_ExpectAndReturn(changer, MAIN_COINCHANGER_DIMES, true);
	CoinChangerSetNickels_ExpectAndReturn(changer, MAIN_COINCHANGER_NICKELS, true);
	
	//Mock coinslot creation.
	CoinSlotCreate_ExpectAndReturn(slot = calloc(1, sizeof(CoinSlot)));
	CoinSlotUpdateDisplay_Expect(slot);
	
	//Mock product destruction.
	ProductDestroy_ExpectAndReturn(products[0], NULL);
	ProductDestroy_ExpectAndReturn(products[1], NULL);
	ProductDestroy_ExpectAndReturn(products[2], NULL);
	
	//Mock coinchanger destruction.
	CoinChangerDestroy_ExpectAndReturn(changer, NULL);
	
	//Mock coinslot destruction.
	CoinSlotDestroy_ExpectAndReturn(slot, NULL);
}

void normalMainTearDown(void) {
	//Don't leak memory, even in testing.
	free(products[0]);
	free(products[1]);
	free(products[2]);
	free(changer);
	free(slot);
}

void test_MainShouldOutputTheInitializationBannerSetUpEverythingAndReturnZero(void) {
	normalMainSetUp();
	
	//Mock user input. (Q for quit)
	CommonInput_ExpectAndReturn('Q');
	
	TEST_ASSERT_EQUAL_INT(0, MainEntry(1, args));
	
	normalMainTearDown();
}

void test_MainShouldFailGracefullyIfProductCreateFailsAndReturnOne(void) {
	//Mock output, expect the initialization banner and a fatal error.
	CommonOutput_ExpectAndReturn(MAIN_INITIALIZATION_MESSAGE, 1);
	CommonOutput_ExpectAndReturn(MAIN_FATAL_ERROR, 1);
	
	//Mock product creation. (Return NULL to simulate an allocation failure.)
	ProductCreate_ExpectAndReturn(NULL); //PRODA
	
	//Expect main to come back with an error code.
	TEST_ASSERT_EQUAL_INT(1, MainEntry(1, args));
}

void test_MainShouldFailGracefullyIfProductSetValueFailsAndReturnOne(void) {
	//Mock output, expect the initialization banner and a fatal error.
	CommonOutput_ExpectAndReturn(MAIN_INITIALIZATION_MESSAGE, 1);
	CommonOutput_ExpectAndReturn(MAIN_FATAL_ERROR, 1);
	
	//Mock product creation as explained above.
	ProductCreate_ExpectAndReturn(products[0] = calloc(1, sizeof(Product))); //PRODA
	ProductCreate_ExpectAndReturn(products[1] = calloc(1, sizeof(Product))); //PRODB
	ProductSetStock_ExpectAndReturn(products[0], MAIN_PRODA_STOCK, true);
	ProductSetValue_ExpectAndReturn(products[0], MAIN_PRODA_VALUE, true);
	ProductSetValue_ExpectAndReturn(products[1], MAIN_PRODB_VALUE, false); //Simulate a failure here.
	
	//Expect main to come back with an error code.
	TEST_ASSERT_EQUAL_INT(1, MainEntry(1, args));
	
	//Don't leak memory, even in testing.
	free(products[0]);
	free(products[1]);
}

void test_MainShouldFailGracefullyIfProductSetStockFailsAndReturnOne(void) {
	//Mock output, expect the initialization banner and a fatal error.
	CommonOutput_ExpectAndReturn(MAIN_INITIALIZATION_MESSAGE, 1);
	CommonOutput_ExpectAndReturn(MAIN_FATAL_ERROR, 1);
	
	//Mock product creation.
	ProductCreate_ExpectAndReturn(products[0] = calloc(1, sizeof(Product))); //PRODA
	ProductCreate_ExpectAndReturn(products[1] = calloc(1, sizeof(Product))); //PRODB
	ProductCreate_ExpectAndReturn(products[2] = calloc(1, sizeof(Product))); //PRODC
	ProductSetStock_ExpectAndReturn(products[0], MAIN_PRODA_STOCK, true);
	ProductSetStock_ExpectAndReturn(products[1], MAIN_PRODB_STOCK, true);
	ProductSetStock_ExpectAndReturn(products[2], MAIN_PRODC_STOCK, false); //Simulate failure here.
	ProductSetValue_ExpectAndReturn(products[0], MAIN_PRODA_VALUE, true);
	ProductSetValue_ExpectAndReturn(products[1], MAIN_PRODB_VALUE, true);
	ProductSetValue_ExpectAndReturn(products[2], MAIN_PRODC_VALUE, true);
	
	//Expect main to come back with an error code.
	TEST_ASSERT_EQUAL_INT(1, MainEntry(1, args));
	
	//Don't leak memory, even in testing.
	free(products[0]);
	free(products[1]);
	free(products[2]);
}

void test_MainShouldFailGracefullyIfCoinChangerCreateFailsAndReturnOne(void) {
	//Mock output, expect the initialization banner and a fatal error.
	CommonOutput_ExpectAndReturn(MAIN_INITIALIZATION_MESSAGE, 1);
	CommonOutput_ExpectAndReturn(MAIN_FATAL_ERROR, 1);
	
	//Mock product creation.
	ProductCreate_ExpectAndReturn(products[0] = calloc(1, sizeof(Product))); //PRODA
	ProductCreate_ExpectAndReturn(products[1] = calloc(1, sizeof(Product))); //PRODB
	ProductCreate_ExpectAndReturn(products[2] = calloc(1, sizeof(Product))); //PRODC
	ProductSetStock_ExpectAndReturn(products[0], MAIN_PRODA_STOCK, true);
	ProductSetStock_ExpectAndReturn(products[1], MAIN_PRODB_STOCK, true);
	ProductSetStock_ExpectAndReturn(products[2], MAIN_PRODC_STOCK, true);
	ProductSetValue_ExpectAndReturn(products[0], MAIN_PRODA_VALUE, true);
	ProductSetValue_ExpectAndReturn(products[1], MAIN_PRODB_VALUE, true);
	ProductSetValue_ExpectAndReturn(products[2], MAIN_PRODC_VALUE, true);
	
	//Mock coinchanger creation.
	CoinChangerCreate_ExpectAndReturn(NULL); //Simulate a failure here.
	
	//Expect main to come back with an error code.
	TEST_ASSERT_EQUAL_INT(1, MainEntry(1, args));
	
	//Don't leak memory, even in testing.
	free(products[0]);
	free(products[1]);
	free(products[2]);
}

void test_MainShouldFailGracefullyIfCoinChangerSetQuartersFailsAndReturnOne(void) {
	//Mock output, expect the initialization banner and a fatal error.
	CommonOutput_ExpectAndReturn(MAIN_INITIALIZATION_MESSAGE, 1);
	CommonOutput_ExpectAndReturn(MAIN_FATAL_ERROR, 1);
	
	//Mock product creation.
	ProductCreate_ExpectAndReturn(products[0] = calloc(1, sizeof(Product))); //PRODA
	ProductCreate_ExpectAndReturn(products[1] = calloc(1, sizeof(Product))); //PRODB
	ProductCreate_ExpectAndReturn(products[2] = calloc(1, sizeof(Product))); //PRODC
	ProductSetStock_ExpectAndReturn(products[0], MAIN_PRODA_STOCK, true);
	ProductSetStock_ExpectAndReturn(products[1], MAIN_PRODB_STOCK, true);
	ProductSetStock_ExpectAndReturn(products[2], MAIN_PRODC_STOCK, true);
	ProductSetValue_ExpectAndReturn(products[0], MAIN_PRODA_VALUE, true);
	ProductSetValue_ExpectAndReturn(products[1], MAIN_PRODB_VALUE, true);
	ProductSetValue_ExpectAndReturn(products[2], MAIN_PRODC_VALUE, true);
	
	//Mock coinchanger creation.
	CoinChangerCreate_ExpectAndReturn(changer = calloc(1, sizeof(CoinChanger)));
	CoinChangerSetQuarters_ExpectAndReturn(changer, MAIN_COINCHANGER_QUARTERS, false); //Simulate a failure here.
	
	//Expect main to come back with an error code.
	TEST_ASSERT_EQUAL_INT(1, MainEntry(1, args));
	
	//Don't leak memory, even in testing.
	free(products[0]);
	free(products[1]);
	free(products[2]);
	free(changer);
}

void test_MainShouldFailGracefullyIfCoinChangerSetDimesFailsAndReturnOne(void) {
	//Mock output, expect the initialization banner and a fatal error.
	CommonOutput_ExpectAndReturn(MAIN_INITIALIZATION_MESSAGE, 1);
	CommonOutput_ExpectAndReturn(MAIN_FATAL_ERROR, 1);
	
	//Mock product creation.
	ProductCreate_ExpectAndReturn(products[0] = calloc(1, sizeof(Product))); //PRODA
	ProductCreate_ExpectAndReturn(products[1] = calloc(1, sizeof(Product))); //PRODB
	ProductCreate_ExpectAndReturn(products[2] = calloc(1, sizeof(Product))); //PRODC
	ProductSetStock_ExpectAndReturn(products[0], MAIN_PRODA_STOCK, true);
	ProductSetStock_ExpectAndReturn(products[1], MAIN_PRODB_STOCK, true);
	ProductSetStock_ExpectAndReturn(products[2], MAIN_PRODC_STOCK, true);
	ProductSetValue_ExpectAndReturn(products[0], MAIN_PRODA_VALUE, true);
	ProductSetValue_ExpectAndReturn(products[1], MAIN_PRODB_VALUE, true);
	ProductSetValue_ExpectAndReturn(products[2], MAIN_PRODC_VALUE, true);
	
	//Mock coinchanger creation.
	CoinChangerCreate_ExpectAndReturn(changer = calloc(1, sizeof(CoinChanger)));
	CoinChangerSetQuarters_ExpectAndReturn(changer, MAIN_COINCHANGER_QUARTERS, true);
	CoinChangerSetDimes_ExpectAndReturn(changer, MAIN_COINCHANGER_DIMES, false); //Simulate a failure here.
	
	//Expect main to come back with an error code.
	TEST_ASSERT_EQUAL_INT(1, MainEntry(1, args));
	
	//Don't leak memory, even in testing.
	free(products[0]);
	free(products[1]);
	free(products[2]);
	free(changer);
}

void test_MainShouldFailGracefullyIfCoinChangerSetNickelsFailsAndReturnOne(void) {
	//Mock output, expect the initialization banner and a fatal error.
	CommonOutput_ExpectAndReturn(MAIN_INITIALIZATION_MESSAGE, 1);
	CommonOutput_ExpectAndReturn(MAIN_FATAL_ERROR, 1);
	
	//Mock product creation.
	ProductCreate_ExpectAndReturn(products[0] = calloc(1, sizeof(Product))); //PRODA
	ProductCreate_ExpectAndReturn(products[1] = calloc(1, sizeof(Product))); //PRODB
	ProductCreate_ExpectAndReturn(products[2] = calloc(1, sizeof(Product))); //PRODC
	ProductSetStock_ExpectAndReturn(products[0], MAIN_PRODA_STOCK, true);
	ProductSetStock_ExpectAndReturn(products[1], MAIN_PRODB_STOCK, true);
	ProductSetStock_ExpectAndReturn(products[2], MAIN_PRODC_STOCK, true);
	ProductSetValue_ExpectAndReturn(products[0], MAIN_PRODA_VALUE, true);
	ProductSetValue_ExpectAndReturn(products[1], MAIN_PRODB_VALUE, true);
	ProductSetValue_ExpectAndReturn(products[2], MAIN_PRODC_VALUE, true);
	
	//Mock coinchanger creation.
	CoinChangerCreate_ExpectAndReturn(changer = calloc(1, sizeof(CoinChanger)));
	CoinChangerSetQuarters_ExpectAndReturn(changer, MAIN_COINCHANGER_QUARTERS, true);
	CoinChangerSetDimes_ExpectAndReturn(changer, MAIN_COINCHANGER_DIMES, true);
	CoinChangerSetNickels_ExpectAndReturn(changer, MAIN_COINCHANGER_NICKELS, false); //Simulate a failure here.
	
	//Expect main to come back with an error code.
	TEST_ASSERT_EQUAL_INT(1, MainEntry(1, args));
	
	//Don't leak memory, even in testing.
	free(products[0]);
	free(products[1]);
	free(products[2]);
	free(changer);
}

void test_MainShouldFailGracefullyIfCoinSlotCreateFailsAndReturnOne(void) {
	//Mock output, expect the initialization banner and a fatal error.
	CommonOutput_ExpectAndReturn(MAIN_INITIALIZATION_MESSAGE, 1);
	CommonOutput_ExpectAndReturn(MAIN_FATAL_ERROR, 1);
	
	//Mock product creation.
	ProductCreate_ExpectAndReturn(products[0] = calloc(1, sizeof(Product))); //PRODA
	ProductCreate_ExpectAndReturn(products[1] = calloc(1, sizeof(Product))); //PRODB
	ProductCreate_ExpectAndReturn(products[2] = calloc(1, sizeof(Product))); //PRODC
	ProductSetStock_ExpectAndReturn(products[0], MAIN_PRODA_STOCK, true);
	ProductSetStock_ExpectAndReturn(products[1], MAIN_PRODB_STOCK, true);
	ProductSetStock_ExpectAndReturn(products[2], MAIN_PRODC_STOCK, true);
	ProductSetValue_ExpectAndReturn(products[0], MAIN_PRODA_VALUE, true);
	ProductSetValue_ExpectAndReturn(products[1], MAIN_PRODB_VALUE, true);
	ProductSetValue_ExpectAndReturn(products[2], MAIN_PRODC_VALUE, true);
	
	//Mock coinchanger creation.
	CoinChangerCreate_ExpectAndReturn(changer = calloc(1, sizeof(CoinChanger)));
	CoinChangerSetQuarters_ExpectAndReturn(changer, MAIN_COINCHANGER_QUARTERS, true);
	CoinChangerSetDimes_ExpectAndReturn(changer, MAIN_COINCHANGER_DIMES, true);
	CoinChangerSetNickels_ExpectAndReturn(changer, MAIN_COINCHANGER_NICKELS, true);
	
	//Mock coinslot creation.
	CoinSlotCreate_ExpectAndReturn(NULL); //Simulate failure here.
	
	//Expect main to come back with an error code.
	TEST_ASSERT_EQUAL_INT(1, MainEntry(1, args));
	
	//Don't leak memory, even in testing.
	free(products[0]);
	free(products[1]);
	free(products[2]);
	free(changer);
}

void test_MainShouldInsertCorrectCoinsWhenUserInsertsCoins(void) {
	normalMainSetUp();
	
	//Mock coinslot input.
	CoinSlotInsertCoin_ExpectAndReturn(slot, COIN_PENNY, COINSLOT_REJECTED_COINRETURN);
	CoinSlotInsertCoin_ExpectAndReturn(slot, COIN_NICKEL, 5);
	CoinSlotInsertCoin_ExpectAndReturn(slot, COIN_DIME, 15);
	CoinSlotInsertCoin_ExpectAndReturn(slot, COIN_QUARTER, 40);
	
	//Mock user input. (p for Penny, n for Nickel, d for Dime, q for Quarter, then Q for quit)
	CommonInput_ExpectAndReturn('p');
	CommonInput_ExpectAndReturn('n');
	CommonInput_ExpectAndReturn('d');
	CommonInput_ExpectAndReturn('q');
	CommonInput_ExpectAndReturn('Q');
	
	TEST_ASSERT_EQUAL_INT(0, MainEntry(1, args));
	
	normalMainTearDown();
}

void test_MainShouldTriggerCoinReturnWhenUserRequestsCoinReturn(void) {
	normalMainSetUp();
	
	//Mock coinslot return.
	CoinSlotReturnAll_ExpectAndReturn(slot, true);
	
	//Mock user input. (r for Return, then Q for quit)
	CommonInput_ExpectAndReturn('r');
	CommonInput_ExpectAndReturn('Q');
	
	TEST_ASSERT_EQUAL_INT(0, MainEntry(1, args));
	
	normalMainTearDown();
}

void test_MainShouldTerminateGracefullyIfCommonInputReturnsZeroAndReturnZero(void) {
	normalMainSetUp();
	
	//Mock user input. (Zero means EOF)
	CommonInput_ExpectAndReturn((char)0);
	
	TEST_ASSERT_EQUAL_INT(0, MainEntry(1, args));
	
	normalMainTearDown();
}

