
#include "unity.h"
#include "CoinSlot.h"

void test_CoinSlotCreateShouldReturnNonNull(void) {
	TEST_ASSERT_NOT_NULL(CoinSlotCreate());
}

void test_CoinSlotInsertShouldRejectPenniesIntoCoinReturn(void) {
	CoinSlot *slot = CoinSlotCreate();
	TEST_ASSERT_EQUAL_INT16(COINSLOT_REJECTED_COINRETURN, CoinSlotInsertCoin(slot, COINSLOT_PENNY));
}

void test_CoinSlotInsertShouldAcceptANickelAndReturnFive(void) {
	CoinSlot *slot = CoinSlotCreate();
	TEST_ASSERT_EQUAL_INT16(5, CoinSlotInsertCoin(slot, COINSLOT_NICKEL));
}

void test_CoinSlotInsertShouldAcceptADimeAndReturnTen(void) {
	CoinSlot *slot = CoinSlotCreate();
	TEST_ASSERT_EQUAL_INT16(10, CoinSlotInsertCoin(slot, COINSLOT_DIME));
}

void test_CoinSlotInsertShouldAcceptAQuarterAndReturnTwentyFive(void) {
	CoinSlot *slot = CoinSlotCreate();
	TEST_ASSERT_EQUAL_INT16(25, CoinSlotInsertCoin(slot, COINSLOT_QUARTER));
}

void test_CoinSlotInsertShouldAccumulateValueWhileInsertingCoins(void) {
	CoinSlot *slot = CoinSlotCreate();
	TEST_ASSERT_EQUAL_INT16(25, CoinSlotInsertCoin(slot, COINSLOT_QUARTER));
	TEST_ASSERT_EQUAL_INT16(35, CoinSlotInsertCoin(slot, COINSLOT_DIME));
	TEST_ASSERT_EQUAL_INT16(40, CoinSlotInsertCoin(slot, COINSLOT_NICKEL));
}

int main(void) {
	UNITY_BEGIN();
	RUN_TEST(test_CoinSlotCreateShouldReturnNonNull);
	RUN_TEST(test_CoinSlotInsertShouldRejectPenniesIntoCoinReturn);
	RUN_TEST(test_CoinSlotInsertShouldAcceptANickelAndReturnFive);
	RUN_TEST(test_CoinSlotInsertShouldAcceptADimeAndReturnTen);
	RUN_TEST(test_CoinSlotInsertShouldAcceptAQuarterAndReturnTwentyFive);
	RUN_TEST(test_CoinSlotInsertShouldAccumulateValueWhileInsertingCoins);
	return UNITY_END();
	}
