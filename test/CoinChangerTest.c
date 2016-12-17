
#include "unity.h"
#include "CoinChanger.h"

void test_CoinChangerCreateShouldReturnNonNull(void) {
	TEST_ASSERT_NOT_NULL(CoinChangerCreate());
}

int main(void) {
	UNITY_BEGIN();
	RUN_TEST(test_CoinChangerCreateShouldReturnNonNull);
	return UNITY_END();
}
