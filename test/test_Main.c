
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
	
	//Mock coinchanger creation.
	//(Need real allocated memory for the Product objects, not because Main dereferences them (it doesn't) but because Unity compares the memory blocks and it will crash if we use symbols instead of pointers to real allocated memory.)
	CoinChangerCreate_ExpectAndReturn(changer = calloc(1, sizeof(CoinChanger)));
	CoinChangerSetQuarters_ExpectAndReturn(changer, MAIN_COINCHANGER_QUARTERS, true);
	CoinChangerSetDimes_ExpectAndReturn(changer, MAIN_COINCHANGER_DIMES, true);
	CoinChangerSetNickels_ExpectAndReturn(changer, MAIN_COINCHANGER_NICKELS, true);
	
	//Mock coinslot creation.
	CoinSlotCreate_ExpectAndReturn(slot = calloc(1, sizeof(CoinSlot)));
	CoinSlotSetCoinChanger_ExpectAndReturn(slot, changer, true);
	CoinSlotUpdateDisplay_Expect(slot);
	
	//Mock product creation.
	ProductCreate_ExpectAndReturn(products[0] = calloc(1, sizeof(Product))); //PRODA
	ProductCreate_ExpectAndReturn(products[1] = calloc(1, sizeof(Product))); //PRODB
	ProductCreate_ExpectAndReturn(products[2] = calloc(1, sizeof(Product))); //PRODC
	ProductSetName_ExpectAndReturn(products[0], MAIN_PRODA_NAME, true);
	ProductSetName_ExpectAndReturn(products[1], MAIN_PRODB_NAME, true);
	ProductSetName_ExpectAndReturn(products[2], MAIN_PRODC_NAME, true);
	ProductSetStock_ExpectAndReturn(products[0], MAIN_PRODA_STOCK, true);
	ProductSetStock_ExpectAndReturn(products[1], MAIN_PRODB_STOCK, true);
	ProductSetStock_ExpectAndReturn(products[2], MAIN_PRODC_STOCK, true);
	ProductSetValue_ExpectAndReturn(products[0], MAIN_PRODA_VALUE, true);
	ProductSetValue_ExpectAndReturn(products[1], MAIN_PRODB_VALUE, true);
	ProductSetValue_ExpectAndReturn(products[2], MAIN_PRODC_VALUE, true);
	ProductSetCoinChanger_ExpectAndReturn(products[0], changer, true);
	ProductSetCoinChanger_ExpectAndReturn(products[1], changer, true);
	ProductSetCoinChanger_ExpectAndReturn(products[2], changer, true);
	ProductSetCoinSlot_ExpectAndReturn(products[0], slot, true);
	ProductSetCoinSlot_ExpectAndReturn(products[1], slot, true);
	ProductSetCoinSlot_ExpectAndReturn(products[2], slot, true);
	
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

void test_MainShouldFailGracefullyIfCoinChangerCreateFailsAndReturnOne(void) {
	//Mock output, expect the initialization banner and a fatal error.
	CommonOutput_ExpectAndReturn(MAIN_INITIALIZATION_MESSAGE, 1);
	CommonOutput_ExpectAndReturn(MAIN_FATAL_ERROR, 1);
	
	//Mock coinchanger creation.
	CoinChangerCreate_ExpectAndReturn(NULL); //Simulate a failure here.
	
	//Expect main to come back with an error code.
	TEST_ASSERT_EQUAL_INT(1, MainEntry(1, args));
}

void test_MainShouldFailGracefullyIfCoinChangerSetQuartersFailsAndReturnOne(void) {
	//Mock output, expect the initialization banner and a fatal error.
	CommonOutput_ExpectAndReturn(MAIN_INITIALIZATION_MESSAGE, 1);
	CommonOutput_ExpectAndReturn(MAIN_FATAL_ERROR, 1);
	
	//Mock coinchanger creation.
	CoinChangerCreate_ExpectAndReturn(changer = calloc(1, sizeof(CoinChanger)));
	CoinChangerSetQuarters_ExpectAndReturn(changer, MAIN_COINCHANGER_QUARTERS, false); //Simulate a failure here.
	
	//Expect main to come back with an error code.
	TEST_ASSERT_EQUAL_INT(1, MainEntry(1, args));
	
	//Don't leak memory, even in testing.
	free(changer);
}

void test_MainShouldFailGracefullyIfCoinChangerSetDimesFailsAndReturnOne(void) {
	//Mock output, expect the initialization banner and a fatal error.
	CommonOutput_ExpectAndReturn(MAIN_INITIALIZATION_MESSAGE, 1);
	CommonOutput_ExpectAndReturn(MAIN_FATAL_ERROR, 1);
	
	//Mock coinchanger creation.
	CoinChangerCreate_ExpectAndReturn(changer = calloc(1, sizeof(CoinChanger)));
	CoinChangerSetQuarters_ExpectAndReturn(changer, MAIN_COINCHANGER_QUARTERS, true);
	CoinChangerSetDimes_ExpectAndReturn(changer, MAIN_COINCHANGER_DIMES, false); //Simulate a failure here.
	
	//Expect main to come back with an error code.
	TEST_ASSERT_EQUAL_INT(1, MainEntry(1, args));
	
	//Don't leak memory, even in testing.
	free(changer);
}

void test_MainShouldFailGracefullyIfCoinChangerSetNickelsFailsAndReturnOne(void) {
	//Mock output, expect the initialization banner and a fatal error.
	CommonOutput_ExpectAndReturn(MAIN_INITIALIZATION_MESSAGE, 1);
	CommonOutput_ExpectAndReturn(MAIN_FATAL_ERROR, 1);
	
	//Mock coinchanger creation.
	CoinChangerCreate_ExpectAndReturn(changer = calloc(1, sizeof(CoinChanger)));
	CoinChangerSetQuarters_ExpectAndReturn(changer, MAIN_COINCHANGER_QUARTERS, true);
	CoinChangerSetDimes_ExpectAndReturn(changer, MAIN_COINCHANGER_DIMES, true);
	CoinChangerSetNickels_ExpectAndReturn(changer, MAIN_COINCHANGER_NICKELS, false); //Simulate a failure here.
	
	//Expect main to come back with an error code.
	TEST_ASSERT_EQUAL_INT(1, MainEntry(1, args));
	
	//Don't leak memory, even in testing.
	free(changer);
}

void test_MainShouldFailGracefullyIfCoinSlotCreateFailsAndReturnOne(void) {
	//Mock output, expect the initialization banner and a fatal error.
	CommonOutput_ExpectAndReturn(MAIN_INITIALIZATION_MESSAGE, 1);
	CommonOutput_ExpectAndReturn(MAIN_FATAL_ERROR, 1);
	
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
	free(changer);
}

void test_MainShouldFailGracefullyIfProductCreateFailsAndReturnOne(void) {
	//Mock output, expect the initialization banner and a fatal error.
	CommonOutput_ExpectAndReturn(MAIN_INITIALIZATION_MESSAGE, 1);
	CommonOutput_ExpectAndReturn(MAIN_FATAL_ERROR, 1);
	
	//Mock coinchanger creation.
	CoinChangerCreate_ExpectAndReturn(changer = calloc(1, sizeof(CoinChanger)));
	CoinChangerSetQuarters_ExpectAndReturn(changer, MAIN_COINCHANGER_QUARTERS, true);
	CoinChangerSetDimes_ExpectAndReturn(changer, MAIN_COINCHANGER_DIMES, true);
	CoinChangerSetNickels_ExpectAndReturn(changer, MAIN_COINCHANGER_NICKELS, true);
	
	//Mock coinslot creation.
	CoinSlotCreate_ExpectAndReturn(slot = calloc(1, sizeof(CoinSlot)));
	CoinSlotSetCoinChanger_ExpectAndReturn(slot, changer, true);
	
	//Mock product creation. (Return NULL to simulate an allocation failure.)
	ProductCreate_ExpectAndReturn(NULL); //PRODA
	
	//Expect main to come back with an error code.
	TEST_ASSERT_EQUAL_INT(1, MainEntry(1, args));
	
	//Don't leak memory, even in testing.
	free(changer);
	free(slot);
}

void test_MainShouldFailGracefullyIfProductSetNameFailsAndReturnOne(void) {
	//Mock output, expect the initialization banner and a fatal error.
	CommonOutput_ExpectAndReturn(MAIN_INITIALIZATION_MESSAGE, 1);
	CommonOutput_ExpectAndReturn(MAIN_FATAL_ERROR, 1);
	
	//Mock coinchanger creation.
	CoinChangerCreate_ExpectAndReturn(changer = calloc(1, sizeof(CoinChanger)));
	CoinChangerSetQuarters_ExpectAndReturn(changer, MAIN_COINCHANGER_QUARTERS, true);
	CoinChangerSetDimes_ExpectAndReturn(changer, MAIN_COINCHANGER_DIMES, true);
	CoinChangerSetNickels_ExpectAndReturn(changer, MAIN_COINCHANGER_NICKELS, true);
	
	//Mock coinslot creation.
	CoinSlotCreate_ExpectAndReturn(slot = calloc(1, sizeof(CoinSlot)));
	CoinSlotSetCoinChanger_ExpectAndReturn(slot, changer, true);
	
	//Mock product creation as explained above.
	ProductCreate_ExpectAndReturn(products[0] = calloc(1, sizeof(Product))); //PRODA
	ProductSetName_ExpectAndReturn(products[0], MAIN_PRODA_NAME, false); //Simulate a failure here.
	
	//Expect main to come back with an error code.
	TEST_ASSERT_EQUAL_INT(1, MainEntry(1, args));
	
	//Don't leak memory, even in testing.
	free(products[0]);
	free(changer);
	free(slot);
}

void test_MainShouldFailGracefullyIfProductSetValueFailsAndReturnOne(void) {
	//Mock output, expect the initialization banner and a fatal error.
	CommonOutput_ExpectAndReturn(MAIN_INITIALIZATION_MESSAGE, 1);
	CommonOutput_ExpectAndReturn(MAIN_FATAL_ERROR, 1);
	
	//Mock coinchanger creation.
	CoinChangerCreate_ExpectAndReturn(changer = calloc(1, sizeof(CoinChanger)));
	CoinChangerSetQuarters_ExpectAndReturn(changer, MAIN_COINCHANGER_QUARTERS, true);
	CoinChangerSetDimes_ExpectAndReturn(changer, MAIN_COINCHANGER_DIMES, true);
	CoinChangerSetNickels_ExpectAndReturn(changer, MAIN_COINCHANGER_NICKELS, true);
	
	//Mock coinslot creation.
	CoinSlotCreate_ExpectAndReturn(slot = calloc(1, sizeof(CoinSlot)));
	CoinSlotSetCoinChanger_ExpectAndReturn(slot, changer, true);
	
	//Mock product creation as explained above.
	ProductCreate_ExpectAndReturn(products[0] = calloc(1, sizeof(Product))); //PRODA
	ProductCreate_ExpectAndReturn(products[1] = calloc(1, sizeof(Product))); //PRODB
	ProductSetName_ExpectAndReturn(products[0], MAIN_PRODA_NAME, true);
	ProductSetName_ExpectAndReturn(products[1], MAIN_PRODB_NAME, true);
	ProductSetStock_ExpectAndReturn(products[0], MAIN_PRODA_STOCK, true);
	ProductSetValue_ExpectAndReturn(products[0], MAIN_PRODA_VALUE, true);
	ProductSetValue_ExpectAndReturn(products[1], MAIN_PRODB_VALUE, false); //Simulate a failure here.
	ProductSetCoinChanger_ExpectAndReturn(products[0], changer, true);
	ProductSetCoinSlot_ExpectAndReturn(products[0], slot, true);
	
	//Expect main to come back with an error code.
	TEST_ASSERT_EQUAL_INT(1, MainEntry(1, args));
	
	//Don't leak memory, even in testing.
	free(products[0]);
	free(products[1]);
	free(changer);
	free(slot);
}

void test_MainShouldFailGracefullyIfProductSetStockFailsAndReturnOne(void) {
	//Mock output, expect the initialization banner and a fatal error.
	CommonOutput_ExpectAndReturn(MAIN_INITIALIZATION_MESSAGE, 1);
	CommonOutput_ExpectAndReturn(MAIN_FATAL_ERROR, 1);
	
	//Mock coinchanger creation.
	CoinChangerCreate_ExpectAndReturn(changer = calloc(1, sizeof(CoinChanger)));
	CoinChangerSetQuarters_ExpectAndReturn(changer, MAIN_COINCHANGER_QUARTERS, true);
	CoinChangerSetDimes_ExpectAndReturn(changer, MAIN_COINCHANGER_DIMES, true);
	CoinChangerSetNickels_ExpectAndReturn(changer, MAIN_COINCHANGER_NICKELS, true);
	
	//Mock coinslot creation.
	CoinSlotCreate_ExpectAndReturn(slot = calloc(1, sizeof(CoinSlot)));
	CoinSlotSetCoinChanger_ExpectAndReturn(slot, changer, true);
	
	//Mock product creation.
	ProductCreate_ExpectAndReturn(products[0] = calloc(1, sizeof(Product))); //PRODA
	ProductCreate_ExpectAndReturn(products[1] = calloc(1, sizeof(Product))); //PRODB
	ProductCreate_ExpectAndReturn(products[2] = calloc(1, sizeof(Product))); //PRODC
	ProductSetName_ExpectAndReturn(products[0], MAIN_PRODA_NAME, true);
	ProductSetName_ExpectAndReturn(products[1], MAIN_PRODB_NAME, true);
	ProductSetName_ExpectAndReturn(products[2], MAIN_PRODC_NAME, true);
	ProductSetValue_ExpectAndReturn(products[0], MAIN_PRODA_VALUE, true);
	ProductSetValue_ExpectAndReturn(products[1], MAIN_PRODB_VALUE, true);
	ProductSetValue_ExpectAndReturn(products[2], MAIN_PRODC_VALUE, true);
	ProductSetStock_ExpectAndReturn(products[0], MAIN_PRODA_STOCK, true);
	ProductSetStock_ExpectAndReturn(products[1], MAIN_PRODB_STOCK, true);
	ProductSetStock_ExpectAndReturn(products[2], MAIN_PRODC_STOCK, false); //Simulate failure here.
	ProductSetCoinChanger_ExpectAndReturn(products[0], changer, true);
	ProductSetCoinChanger_ExpectAndReturn(products[1], changer, true);
	ProductSetCoinSlot_ExpectAndReturn(products[0], slot, true);
	ProductSetCoinSlot_ExpectAndReturn(products[1], slot, true);
	
	//Expect main to come back with an error code.
	TEST_ASSERT_EQUAL_INT(1, MainEntry(1, args));
	
	//Don't leak memory, even in testing.
	free(products[0]);
	free(products[1]);
	free(products[2]);
	free(changer);
	free(slot);
}

void test_MainShouldFailGracefullyIfProductSetCoinChangerFailsAndReturnOne(void) {
	//Mock output, expect the initialization banner and a fatal error.
	CommonOutput_ExpectAndReturn(MAIN_INITIALIZATION_MESSAGE, 1);
	CommonOutput_ExpectAndReturn(MAIN_FATAL_ERROR, 1);
	
	//Mock coinchanger creation.
	CoinChangerCreate_ExpectAndReturn(changer = calloc(1, sizeof(CoinChanger)));
	CoinChangerSetQuarters_ExpectAndReturn(changer, MAIN_COINCHANGER_QUARTERS, true);
	CoinChangerSetDimes_ExpectAndReturn(changer, MAIN_COINCHANGER_DIMES, true);
	CoinChangerSetNickels_ExpectAndReturn(changer, MAIN_COINCHANGER_NICKELS, true);
	
	//Mock coinslot creation.
	CoinSlotCreate_ExpectAndReturn(slot = calloc(1, sizeof(CoinSlot)));
	CoinSlotSetCoinChanger_ExpectAndReturn(slot, changer, true);
	
	//Mock product creation.
	ProductCreate_ExpectAndReturn(products[0] = calloc(1, sizeof(Product))); //PRODA
	ProductSetName_ExpectAndReturn(products[0], MAIN_PRODA_NAME, true);
	ProductSetValue_ExpectAndReturn(products[0], MAIN_PRODA_VALUE, true);
	ProductSetStock_ExpectAndReturn(products[0], MAIN_PRODA_STOCK, true);
	ProductSetCoinChanger_ExpectAndReturn(products[0], changer, false); //Simulate failure here.
	
	//Expect main to come back with an error code.
	TEST_ASSERT_EQUAL_INT(1, MainEntry(1, args));
	
	//Don't leak memory, even in testing.
	free(products[0]);
	free(changer);
	free(slot);
}

void test_MainShouldFailGracefullyIfProductSetCoinSlotFailsAndReturnOne(void) {
	//Mock output, expect the initialization banner and a fatal error.
	CommonOutput_ExpectAndReturn(MAIN_INITIALIZATION_MESSAGE, 1);
	CommonOutput_ExpectAndReturn(MAIN_FATAL_ERROR, 1);
	
	//Mock coinchanger creation.
	CoinChangerCreate_ExpectAndReturn(changer = calloc(1, sizeof(CoinChanger)));
	CoinChangerSetQuarters_ExpectAndReturn(changer, MAIN_COINCHANGER_QUARTERS, true);
	CoinChangerSetDimes_ExpectAndReturn(changer, MAIN_COINCHANGER_DIMES, true);
	CoinChangerSetNickels_ExpectAndReturn(changer, MAIN_COINCHANGER_NICKELS, true);
	
	//Mock coinslot creation.
	CoinSlotCreate_ExpectAndReturn(slot = calloc(1, sizeof(CoinSlot)));
	CoinSlotSetCoinChanger_ExpectAndReturn(slot, changer, true);
	
	//Mock product creation.
	ProductCreate_ExpectAndReturn(products[0] = calloc(1, sizeof(Product))); //PRODA
	ProductSetName_ExpectAndReturn(products[0], MAIN_PRODA_NAME, true);
	ProductSetValue_ExpectAndReturn(products[0], MAIN_PRODA_VALUE, true);
	ProductSetStock_ExpectAndReturn(products[0], MAIN_PRODA_STOCK, true);
	ProductSetCoinChanger_ExpectAndReturn(products[0], changer, true);
	ProductSetCoinSlot_ExpectAndReturn(products[0], slot, false); //Simulate failure here.
	
	//Expect main to come back with an error code.
	TEST_ASSERT_EQUAL_INT(1, MainEntry(1, args));
	
	//Don't leak memory, even in testing.
	free(products[0]);
	free(changer);
	free(slot);
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

void test_MainShouldInitiateProductVendWhenUserRequestsProductVend(void) {
	normalMainSetUp();
	
	//Expect Main to send the request to the appropriate Product objects.
	ProductRequestVend_ExpectAndReturn(products[0], false);
	ProductRequestVend_ExpectAndReturn(products[1], false);
	ProductRequestVend_ExpectAndReturn(products[2], false);
	
	//Mock user input. (Products 0-2 mapped to ASCII 1-3)
	CommonInput_ExpectAndReturn('1');
	CommonInput_ExpectAndReturn('2');
	CommonInput_ExpectAndReturn('3');
	CommonInput_ExpectAndReturn('Q');
	
	TEST_ASSERT_EQUAL_INT(0, MainEntry(1, args));
	
	normalMainTearDown();
}


