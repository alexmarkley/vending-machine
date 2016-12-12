
#include "unity.h"
#include "CoinSlot.h"

void test_CoinSlotCreateShouldReturnNonNull(void) {
	TEST_ASSERT_NOT_NULL(CoinSlotCreate());
}

void test_CoinSlotInsertShouldRejectPenniesIntoCoinReturn(void) {
	CoinSlot *slot = CoinSlotCreate();
	TEST_ASSERT_EQUAL_INT16(COINSLOT_REJECTED_COINRETURN, CoinSlotInsertCoin(slot, COINSLOT_PENNY));
}

int main(void) {
	UNITY_BEGIN();
	RUN_TEST(test_CoinSlotCreateShouldReturnNonNull);
	RUN_TEST(test_CoinSlotInsertShouldRejectPenniesIntoCoinReturn);
	return UNITY_END();
	}
