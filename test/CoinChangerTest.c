
#include "unity.h"
#include "CoinChanger.h"

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

int main(void) {
	UNITY_BEGIN();
	RUN_TEST(test_CoinChangerCreateShouldReturnNonNull);
	RUN_TEST(test_CoinChangerDestroyShouldReturnNull);
	RUN_TEST(test_CoinChangerGetNickelsShouldStartUninitialized);
	RUN_TEST(test_CoinChangerSetNickelsShouldReturnTrue);
	return UNITY_END();
}
