
#include "unity.h"
#include "CoinSlot.h"
#include "Common.h"
#include "mock_CoinReturn.h"
#include "mock_Common.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

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
	//Mock CoinReturn, expect a penny to be ejected.
	CoinReturnEjectCoin_ExpectAndReturn(COIN_PENNY, true);
	TEST_ASSERT_EQUAL_INT16(COINSLOT_REJECTED_COINRETURN, CoinSlotInsertCoin(slot, COIN_PENNY));
	CoinSlotDestroy(slot);
}

void test_CoinSlotInsertShouldAcceptANickelAndReturnFive(void) {
	CoinSlot *slot = CoinSlotCreate();
	
	//Expect the display to be implicitly updated with the accumulated value of the inserted coins.
	CommonOutput_ExpectAndReturn(COINSLOT_MSG_PREFIX "$0.05", 1);
	
	TEST_ASSERT_EQUAL_INT16(5, CoinSlotInsertCoin(slot, COIN_NICKEL));
	CoinSlotDestroy(slot);
}

void test_CoinSlotInsertShouldAcceptADimeAndReturnTen(void) {
	CoinSlot *slot = CoinSlotCreate();
	
	//Expect the display to be implicitly updated with the accumulated value of the inserted coins.
	CommonOutput_ExpectAndReturn(COINSLOT_MSG_PREFIX "$0.10", 1);
	
	TEST_ASSERT_EQUAL_INT16(10, CoinSlotInsertCoin(slot, COIN_DIME));
	CoinSlotDestroy(slot);
}

void test_CoinSlotInsertShouldAcceptAQuarterAndReturnTwentyFive(void) {
	CoinSlot *slot = CoinSlotCreate();
	
	//Expect the display to be implicitly updated with the accumulated value of the inserted coins.
	CommonOutput_ExpectAndReturn(COINSLOT_MSG_PREFIX "$0.25", 1);
	
	TEST_ASSERT_EQUAL_INT16(25, CoinSlotInsertCoin(slot, COIN_QUARTER));
	CoinSlotDestroy(slot);
}

void test_CoinSlotInsertShouldAccumulateValueWhileInsertingCoins(void) {
	CoinSlot *slot = CoinSlotCreate();
	
	//Expect the display to be implicitly updated with the accumulated value of the inserted coins.
	CommonOutput_ExpectAndReturn(COINSLOT_MSG_PREFIX "$0.25", 1);
	CommonOutput_ExpectAndReturn(COINSLOT_MSG_PREFIX "$0.35", 1);
	CommonOutput_ExpectAndReturn(COINSLOT_MSG_PREFIX "$0.40", 1);
	
	TEST_ASSERT_EQUAL_INT16(25, CoinSlotInsertCoin(slot, COIN_QUARTER));
	TEST_ASSERT_EQUAL_INT16(35, CoinSlotInsertCoin(slot, COIN_DIME));
	TEST_ASSERT_EQUAL_INT16(40, CoinSlotInsertCoin(slot, COIN_NICKEL));
	CoinSlotDestroy(slot);
}

void test_CoinSlotInsertShouldRejectCoinsWhenSlotIsFull(void) {
	CoinSlot *slot = CoinSlotCreate();
	
	//Expect the display to be implicitly updated with the accumulated value of the inserted coins.
	uint16_t value = 0;
	char display[COINSLOT_INTAKE_MAXCOINS][20];
	for(int i = 0; i < COINSLOT_INTAKE_MAXCOINS; i++) {
		value += COIN_NICKEL;
		uint16_t dollars = (value / (uint16_t)100);
		uint8_t cents = value - (dollars * 100);
		//Build the mock's expected display string. (max "CoinSlot: $NNNNN.NN\0")
		snprintf(display[i], 20, COINSLOT_MSG_PREFIX "$%" PRIu16 ".%02" PRIu8, dollars, cents);
		CommonOutput_ExpectAndReturn(display[i], 1);
	}
	
	//Insert the maximum number of coins.
	for(int i = 0; i < COINSLOT_INTAKE_MAXCOINS; i++) {
		CoinSlotInsertCoin(slot, COIN_NICKEL);
	}
	TEST_ASSERT_EQUAL_INT16(COINSLOT_REJECTED_SLOTFULL, CoinSlotInsertCoin(slot, COIN_NICKEL));
	CoinSlotDestroy(slot);
}

void test_CoinSlotAfterInsertingFourQuartersValueShouldReturnOneHundred(void) {
	CoinSlot *slot = CoinSlotCreate();
	
	//Expect the display to be implicitly updated with the accumulated value of the inserted coins.
	CommonOutput_ExpectAndReturn(COINSLOT_MSG_PREFIX "$0.25", 1);
	CommonOutput_ExpectAndReturn(COINSLOT_MSG_PREFIX "$0.50", 1);
	CommonOutput_ExpectAndReturn(COINSLOT_MSG_PREFIX "$0.75", 1);
	CommonOutput_ExpectAndReturn(COINSLOT_MSG_PREFIX "$1.00", 1);
	
	//Insert a dollar in quarters.
	CoinSlotInsertCoin(slot, COIN_QUARTER);
	CoinSlotInsertCoin(slot, COIN_QUARTER);
	CoinSlotInsertCoin(slot, COIN_QUARTER);
	CoinSlotInsertCoin(slot, COIN_QUARTER);
	TEST_ASSERT_EQUAL_INT16(100, CoinSlotValue(slot));
	CoinSlotDestroy(slot);
}

void test_CoinSlotAfterFlushingInsertShouldAcceptAQuarterAndReturnTwentyFive(void) {
	CoinSlot *slot = CoinSlotCreate();
	
	//Expect the display to be implicitly updated with the accumulated value of the inserted coins.
	CommonOutput_ExpectAndReturn(COINSLOT_MSG_PREFIX "$0.10", 1);
	CommonOutput_ExpectAndReturn(COINSLOT_MSG_PREFIX "$0.15", 1);
	CommonOutput_ExpectAndReturn(COINSLOT_MSG_PREFIX "$0.25", 1);
	
	//Insert a dime and a nickel.
	CoinSlotInsertCoin(slot, COIN_DIME);
	CoinSlotInsertCoin(slot, COIN_NICKEL);
	//Flush everything out of the CoinSlot
	CoinSlotFlush(slot);
	TEST_ASSERT_EQUAL_INT16(25, CoinSlotInsertCoin(slot, COIN_QUARTER));
	CoinSlotDestroy(slot);
}

void test_CoinSlotReturnAllShouldReturnInsertedCoins(void) {
	CoinSlot *slot = CoinSlotCreate();
	
	//Expect the display to be implicitly updated with the accumulated value of the inserted coins.
	CommonOutput_ExpectAndReturn(COINSLOT_MSG_PREFIX "$0.05", 1);
	CommonOutput_ExpectAndReturn(COINSLOT_MSG_PREFIX "$0.15", 1);
	CommonOutput_ExpectAndReturn(COINSLOT_MSG_PREFIX "$0.40", 1);
	CommonOutput_ExpectAndReturn(COINSLOT_INSERTCOIN_MESSAGE, 1);
	
	//Mock CoinReturn, expect a nickel, a dime, and a quarter to be ejected.
	CoinReturnEjectCoin_ExpectAndReturn(COIN_NICKEL, true);
	CoinReturnEjectCoin_ExpectAndReturn(COIN_DIME, true);
	CoinReturnEjectCoin_ExpectAndReturn(COIN_QUARTER, true);
	
	//Insert coins into the CoinSlot
	TEST_ASSERT_EQUAL_INT16(5, CoinSlotInsertCoin(slot, COIN_NICKEL));
	TEST_ASSERT_EQUAL_INT16(15, CoinSlotInsertCoin(slot, COIN_DIME));
	TEST_ASSERT_EQUAL_INT16(40, CoinSlotInsertCoin(slot, COIN_QUARTER));
	
	//Engage the coin return
	TEST_ASSERT_TRUE(CoinSlotReturnAll(slot));
	
	//Confirm that the CoinSlot's value is now zero.
	TEST_ASSERT_EQUAL_INT16(0, CoinSlotValue(slot));
	
	CoinSlotDestroy(slot);
}

void test_CoinSlotUpdateDisplayWhenNoCoinsAreInsertedShouldOutputInsertCoin(void) {
	CoinSlot *slot = CoinSlotCreate();
	
	//Expect the INSERT COIN message.
	CommonOutput_ExpectAndReturn(COINSLOT_INSERTCOIN_MESSAGE, 1);
	
	//Explicitly update the display.
	CoinSlotUpdateDisplay(slot);
	
	CoinSlotDestroy(slot);
}

