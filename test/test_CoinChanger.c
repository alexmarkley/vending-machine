
#include "unity.h"
#include "CoinChanger.h"
#include "CoinReturn.h"
#include "mock_CoinReturn.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_CoinChangerCreateShouldReturnNonNull(void) {
	TEST_ASSERT_NOT_NULL(CoinChangerCreate());
}

void test_CoinChangerDestroyShouldReturnNull(void) {
	CoinChanger *changer = CoinChangerCreate();
	TEST_ASSERT_NULL(CoinChangerDestroy(changer));
}

void test_CoinChangerGetNickelsShouldStartUninitialized(void) {
	CoinChanger *changer = CoinChangerCreate();
	TEST_ASSERT_EQUAL_INT8(COINCHANGER_PROPERTY_UNINITIALIZED, CoinChangerGetNickels(changer));
	CoinChangerDestroy(changer);
}

void test_CoinChangerSetNickelsShouldReturnTrue(void) {
	CoinChanger *changer = CoinChangerCreate();
	TEST_ASSERT_TRUE(CoinChangerSetNickels(changer, 40));
	CoinChangerDestroy(changer);
}

void test_CoinChangerSetNickelsShouldPersist(void) {
	CoinChanger *changer = CoinChangerCreate();
	TEST_ASSERT_TRUE(CoinChangerSetNickels(changer, 80));
	TEST_ASSERT_EQUAL_INT8(80, CoinChangerGetNickels(changer));
	CoinChangerDestroy(changer);
}

void test_CoinChangerSetNickelsInvalidValueShouldReturnFalse(void) {
	CoinChanger *changer = CoinChangerCreate();
	TEST_ASSERT_FALSE(CoinChangerSetNickels(changer, 128));
	CoinChangerDestroy(changer);
}

void test_CoinChangerGetDimesShouldStartUninitialized(void) {
	CoinChanger *changer = CoinChangerCreate();
	TEST_ASSERT_EQUAL_INT8(COINCHANGER_PROPERTY_UNINITIALIZED, CoinChangerGetDimes(changer));
	CoinChangerDestroy(changer);
}

void test_CoinChangerSetDimesShouldReturnTrue(void) {
	CoinChanger *changer = CoinChangerCreate();
	TEST_ASSERT_TRUE(CoinChangerSetDimes(changer, 50));
	CoinChangerDestroy(changer);
}

void test_CoinChangerSetDimesShouldPersist(void) {
	CoinChanger *changer = CoinChangerCreate();
	TEST_ASSERT_TRUE(CoinChangerSetDimes(changer, 100));
	TEST_ASSERT_EQUAL_INT8(100, CoinChangerGetDimes(changer));
	CoinChangerDestroy(changer);
}

void test_CoinChangerSetDimesInvalidValueShouldReturnFalse(void) {
	CoinChanger *changer = CoinChangerCreate();
	TEST_ASSERT_FALSE(CoinChangerSetDimes(changer, 128));
	CoinChangerDestroy(changer);
}

void test_CoinChangerGetQuartersShouldStartUninitialized(void) {
	CoinChanger *changer = CoinChangerCreate();
	TEST_ASSERT_EQUAL_INT8(COINCHANGER_PROPERTY_UNINITIALIZED, CoinChangerGetQuarters(changer));
	CoinChangerDestroy(changer);
}

void test_CoinChangerSetQuartersShouldReturnTrue(void) {
	CoinChanger *changer = CoinChangerCreate();
	TEST_ASSERT_TRUE(CoinChangerSetQuarters(changer, 40));
	CoinChangerDestroy(changer);
}

void test_CoinChangerSetQuartersShouldPersist(void) {
	CoinChanger *changer = CoinChangerCreate();
	TEST_ASSERT_TRUE(CoinChangerSetQuarters(changer, 80));
	TEST_ASSERT_EQUAL_INT8(80, CoinChangerGetQuarters(changer));
	CoinChangerDestroy(changer);
}

void test_CoinChangerSetQuartersInvalidValueShouldReturnFalse(void) {
	CoinChanger *changer = CoinChangerCreate();
	TEST_ASSERT_FALSE(CoinChangerSetQuarters(changer, 128));
	CoinChangerDestroy(changer);
}

void test_CoinChangerMakeChangeForOneDollarWhenThereAreNoCoinsInTheChangerShouldReturnFalse(void) {
	CoinChanger *changer = CoinChangerCreate();
	TEST_ASSERT_FALSE(CoinChangerMakeChange(changer, 100));
	CoinChangerDestroy(changer);
}

void test_CoinChangerMakeChangeForOneDollarWhenThereAreFourQuartersInTheChangerShouldSendFourQuartersAndReturnTrue(void) {
	CoinChanger *changer = CoinChangerCreate();
	
	//Mock CoinReturn, expect four quarters to be ejected.
	CoinReturnEjectCoin_ExpectAndReturn(COINRETURN_QUARTER, true);
	CoinReturnEjectCoin_ExpectAndReturn(COINRETURN_QUARTER, true);
	CoinReturnEjectCoin_ExpectAndReturn(COINRETURN_QUARTER, true);
	CoinReturnEjectCoin_ExpectAndReturn(COINRETURN_QUARTER, true);
	
	//Insert four quarters into the CoinChanger.
	TEST_ASSERT_TRUE(CoinChangerSetQuarters(changer, 4));
	TEST_ASSERT_EQUAL_INT8(4, CoinChangerGetQuarters(changer));
	
	//Attempt to make change for a dollar.
	TEST_ASSERT_TRUE(CoinChangerMakeChange(changer, 100));
	
	//Confirm that we have no more quarters in our inventory.
	TEST_ASSERT_EQUAL_INT8(0, CoinChangerGetQuarters(changer));
	
	CoinChangerDestroy(changer);
}

void test_CoinChangerMakeChangeForSeventyCentsWhenThereAreTwoQuartersAndTwoDimesInTheChangerShouldSendTwoQuartersAndTwoDimesAndReturnTrue(void) {
	CoinChanger *changer = CoinChangerCreate();
	
	//Mock CoinReturn, expect two quarters and two dimes to be ejected.
	CoinReturnEjectCoin_ExpectAndReturn(COINRETURN_QUARTER, true);
	CoinReturnEjectCoin_ExpectAndReturn(COINRETURN_QUARTER, true);
	CoinReturnEjectCoin_ExpectAndReturn(COINRETURN_DIME, true);
	CoinReturnEjectCoin_ExpectAndReturn(COINRETURN_DIME, true);
	
	//Insert two quarters into the CoinChanger.
	TEST_ASSERT_TRUE(CoinChangerSetQuarters(changer, 2));
	TEST_ASSERT_EQUAL_INT8(2, CoinChangerGetQuarters(changer));
	
	//Insert two dimes into the CoinChanger.
	TEST_ASSERT_TRUE(CoinChangerSetDimes(changer, 2));
	TEST_ASSERT_EQUAL_INT8(2, CoinChangerGetDimes(changer));
	
	//Attempt to make change for seventy cents.
	TEST_ASSERT_TRUE(CoinChangerMakeChange(changer, 70));
	
	//Confirm that we have no more quarters or dimes in our inventory.
	TEST_ASSERT_EQUAL_INT8(0, CoinChangerGetQuarters(changer));
	TEST_ASSERT_EQUAL_INT8(0, CoinChangerGetDimes(changer));
	
	CoinChangerDestroy(changer);
}

void test_CoinChangerMakeChangeForSixtyFiveCentsWhenChangerIsStockedShouldSendTwoQuartersOneDimeAndOneNickelAndReturnTrue(void) {
	CoinChanger *changer = CoinChangerCreate();
	
	//Mock CoinReturn, expect two quarters, one dime, and one nickel to be ejected.
	CoinReturnEjectCoin_ExpectAndReturn(COINRETURN_QUARTER, true);
	CoinReturnEjectCoin_ExpectAndReturn(COINRETURN_QUARTER, true);
	CoinReturnEjectCoin_ExpectAndReturn(COINRETURN_DIME, true);
	CoinReturnEjectCoin_ExpectAndReturn(COINRETURN_NICKEL, true);
	
	//Insert two full rolls of quarters into the CoinChanger.
	TEST_ASSERT_TRUE(CoinChangerSetQuarters(changer, 80));
	TEST_ASSERT_EQUAL_INT8(80, CoinChangerGetQuarters(changer));
	
	//Insert two full rolls of dimes into the CoinChanger.
	TEST_ASSERT_TRUE(CoinChangerSetDimes(changer, 100));
	TEST_ASSERT_EQUAL_INT8(100, CoinChangerGetDimes(changer));
	
	//Insert two full rolls of nickels into the CoinChanger.
	TEST_ASSERT_TRUE(CoinChangerSetNickels(changer, 80));
	TEST_ASSERT_EQUAL_INT8(80, CoinChangerGetNickels(changer));
	
	//Attempt to make change for sixty-five cents.
	TEST_ASSERT_TRUE(CoinChangerMakeChange(changer, 65));
	
	//Confirm that we have correspondingly reduced our inventory.
	TEST_ASSERT_EQUAL_INT8(78, CoinChangerGetQuarters(changer));
	TEST_ASSERT_EQUAL_INT8(99, CoinChangerGetDimes(changer));
	TEST_ASSERT_EQUAL_INT8(79, CoinChangerGetNickels(changer));
	
	CoinChangerDestroy(changer);
}

void test_CoinChangerMakeChangeForTwentyFiveCentsWhenThereAreTwoDimesAndOneNickelInTheChangerShouldSendTwoDimesAndOneNickelAndReturnTrue(void) {
	CoinChanger *changer = CoinChangerCreate();
	
	//// NOTE: This is a tricky test case. It calls out a bug where uninitialized CoinChanger coin
	//// values (internally represented as -1) were being multiplied into the remainder (stored
	//// internally as an unsigned integer) and causing an unsigned integer underflow. Hence the
	//// CoinChanger would think that it was trying to make change for almost $600 and fail.
	//// This bug is now fixed.
	
	//Mock CoinReturn, expect two dimes and one nickel to be ejected.
	CoinReturnEjectCoin_ExpectAndReturn(COINRETURN_DIME, true);
	CoinReturnEjectCoin_ExpectAndReturn(COINRETURN_DIME, true);
	CoinReturnEjectCoin_ExpectAndReturn(COINRETURN_NICKEL, true);
	
	//Insert two dimes into the CoinChanger.
	TEST_ASSERT_TRUE(CoinChangerSetDimes(changer, 2));
	TEST_ASSERT_EQUAL_INT8(2, CoinChangerGetDimes(changer));
	
	//Insert one nickel into the CoinChanger.
	TEST_ASSERT_TRUE(CoinChangerSetNickels(changer, 1));
	TEST_ASSERT_EQUAL_INT8(1, CoinChangerGetNickels(changer));
	
	//Attempt to make change for twenty-five cents.
	TEST_ASSERT_TRUE(CoinChangerMakeChange(changer, 25));
	
	//Confirm that we have no more dimes or nickels in our inventory.
	TEST_ASSERT_EQUAL_INT8(0, CoinChangerGetDimes(changer));
	TEST_ASSERT_EQUAL_INT8(0, CoinChangerGetNickels(changer));
	
	CoinChangerDestroy(changer);
}

