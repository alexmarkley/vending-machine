
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

int main(void) {
	UNITY_BEGIN();
	RUN_TEST(test_CoinChangerCreateShouldReturnNonNull);
	RUN_TEST(test_CoinChangerDestroyShouldReturnNull);
	RUN_TEST(test_CoinChangerGetNickelsShouldStartUninitialized);
	RUN_TEST(test_CoinChangerSetNickelsShouldReturnTrue);
	RUN_TEST(test_CoinChangerSetNickelsShouldPersist);
	RUN_TEST(test_CoinChangerSetNickelsInvalidValueShouldReturnFalse);
	RUN_TEST(test_CoinChangerGetDimesShouldStartUninitialized);
	RUN_TEST(test_CoinChangerSetDimesShouldReturnTrue);
	RUN_TEST(test_CoinChangerSetDimesShouldPersist);
	RUN_TEST(test_CoinChangerSetDimesInvalidValueShouldReturnFalse);
	RUN_TEST(test_CoinChangerGetQuartersShouldStartUninitialized);
	RUN_TEST(test_CoinChangerSetQuartersShouldReturnTrue);
	RUN_TEST(test_CoinChangerSetQuartersShouldPersist);
	RUN_TEST(test_CoinChangerSetQuartersInvalidValueShouldReturnFalse);
	RUN_TEST(test_CoinChangerMakeChangeForOneDollarWhenThereAreNoCoinsInTheChangerShouldReturnFalse);
	return UNITY_END();
}
