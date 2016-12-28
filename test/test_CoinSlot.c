
#include "unity.h"
#include "CoinSlot.h"
#include "CoinReturn.h"
#include "mock_CoinReturn.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_CoinSlotCreateShouldReturnNonNull(void) {
	TEST_ASSERT_NOT_NULL(CoinSlotCreate());
}

void test_CoinSlotDestroyShouldReturnNull(void) {
	CoinSlot *slot = CoinSlotCreate();
	TEST_ASSERT_NULL(CoinSlotDestroy(slot));
}

void test_CoinSlotInsertShouldRejectPenniesIntoCoinReturn(void) {
	CoinSlot *slot = CoinSlotCreate();
	TEST_ASSERT_EQUAL_INT16(COINSLOT_REJECTED_COINRETURN, CoinSlotInsertCoin(slot, COINSLOT_PENNY));
	CoinSlotDestroy(slot);
}

void test_CoinSlotInsertShouldAcceptANickelAndReturnFive(void) {
	CoinSlot *slot = CoinSlotCreate();
	TEST_ASSERT_EQUAL_INT16(5, CoinSlotInsertCoin(slot, COINSLOT_NICKEL));
	CoinSlotDestroy(slot);
}

void test_CoinSlotInsertShouldAcceptADimeAndReturnTen(void) {
	CoinSlot *slot = CoinSlotCreate();
	TEST_ASSERT_EQUAL_INT16(10, CoinSlotInsertCoin(slot, COINSLOT_DIME));
	CoinSlotDestroy(slot);
}

void test_CoinSlotInsertShouldAcceptAQuarterAndReturnTwentyFive(void) {
	CoinSlot *slot = CoinSlotCreate();
	TEST_ASSERT_EQUAL_INT16(25, CoinSlotInsertCoin(slot, COINSLOT_QUARTER));
	CoinSlotDestroy(slot);
}

void test_CoinSlotInsertShouldAccumulateValueWhileInsertingCoins(void) {
	CoinSlot *slot = CoinSlotCreate();
	TEST_ASSERT_EQUAL_INT16(25, CoinSlotInsertCoin(slot, COINSLOT_QUARTER));
	TEST_ASSERT_EQUAL_INT16(35, CoinSlotInsertCoin(slot, COINSLOT_DIME));
	TEST_ASSERT_EQUAL_INT16(40, CoinSlotInsertCoin(slot, COINSLOT_NICKEL));
	CoinSlotDestroy(slot);
}

void test_CoinSlotInsertShouldRejectCoinsWhenSlotIsFull(void) {
	CoinSlot *slot = CoinSlotCreate();
	//Insert the maximum number of coins.
	for(int i = 0; i < COINSLOT_INTAKE_MAXCOINS; i++) {
		CoinSlotInsertCoin(slot, COINSLOT_NICKEL);
	}
	TEST_ASSERT_EQUAL_INT16(COINSLOT_REJECTED_SLOTFULL, CoinSlotInsertCoin(slot, COINSLOT_NICKEL));
	CoinSlotDestroy(slot);
}

void test_CoinSlotAfterInsertingFourQuartersValueShouldReturnOneHundred(void) {
	CoinSlot *slot = CoinSlotCreate();
	//Insert a dollar in quarters.
	CoinSlotInsertCoin(slot, COINSLOT_QUARTER);
	CoinSlotInsertCoin(slot, COINSLOT_QUARTER);
	CoinSlotInsertCoin(slot, COINSLOT_QUARTER);
	CoinSlotInsertCoin(slot, COINSLOT_QUARTER);
	TEST_ASSERT_EQUAL_INT16(100, CoinSlotValue(slot));
	CoinSlotDestroy(slot);
}

void test_CoinSlotAfterFlushingInsertShouldAcceptAQuarterAndReturnTwentyFive(void) {
	CoinSlot *slot = CoinSlotCreate();
	//Insert a dime and a nickel.
	CoinSlotInsertCoin(slot, COINSLOT_DIME);
	CoinSlotInsertCoin(slot, COINSLOT_NICKEL);
	//Flush everything out of the CoinSlot
	CoinSlotFlush(slot);
	TEST_ASSERT_EQUAL_INT16(25, CoinSlotInsertCoin(slot, COINSLOT_QUARTER));
	CoinSlotDestroy(slot);
}

void test_CoinSlotReturnAllShouldReturnInsertedCoins(void) {
	CoinSlot *slot = CoinSlotCreate();
	
	//Mock CoinReturn, expect a nickel, a dime, and a quarter to be ejected.
	CoinReturnEjectCoin_ExpectAndReturn(COINRETURN_NICKEL, true);
	CoinReturnEjectCoin_ExpectAndReturn(COINRETURN_DIME, true);
	CoinReturnEjectCoin_ExpectAndReturn(COINRETURN_QUARTER, true);
	
	//Insert coins into the CoinSlot
	TEST_ASSERT_EQUAL_INT16(5, CoinSlotInsertCoin(slot, COINSLOT_NICKEL));
	TEST_ASSERT_EQUAL_INT16(15, CoinSlotInsertCoin(slot, COINSLOT_DIME));
	TEST_ASSERT_EQUAL_INT16(40, CoinSlotInsertCoin(slot, COINSLOT_QUARTER));
	
	//Engage the coin return
	TEST_ASSERT_TRUE(CoinSlotReturnAll(slot));
	
	//Confirm that the CoinSlot's value is now zero.
	TEST_ASSERT_EQUAL_INT16(0, CoinSlotValue(slot));
	
	CoinSlotDestroy(slot);
}

