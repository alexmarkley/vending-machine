
#include "unity.h"
#include "CoinSlot.h"

void test_CoinSlotCreateShouldReturnNonNull(void) {
	TEST_ASSERT_NOT_NULL(CoinSlotCreate());
}

int main(void) {
	UNITY_BEGIN();
	RUN_TEST(test_CoinSlotCreateShouldReturnNonNull);
	return UNITY_END();
	}
