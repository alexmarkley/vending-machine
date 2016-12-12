
#include "unity.h"
#include "CoinSlot.h"

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

int main(void) {
	UNITY_BEGIN();
	RUN_TEST(test_CoinSlotCreateShouldReturnNonNull);
	RUN_TEST(test_CoinSlotDestroyShouldReturnNull);
	RUN_TEST(test_CoinSlotInsertShouldRejectPenniesIntoCoinReturn);
	RUN_TEST(test_CoinSlotInsertShouldAcceptANickelAndReturnFive);
	RUN_TEST(test_CoinSlotInsertShouldAcceptADimeAndReturnTen);
	RUN_TEST(test_CoinSlotInsertShouldAcceptAQuarterAndReturnTwentyFive);
	RUN_TEST(test_CoinSlotInsertShouldAccumulateValueWhileInsertingCoins);
	RUN_TEST(test_CoinSlotInsertShouldRejectCoinsWhenSlotIsFull);
	return UNITY_END();
}
