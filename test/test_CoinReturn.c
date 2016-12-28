#include "unity.h"
#include "CoinReturn.h"
#include "Common.h"
#include "mock_Common.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_CoinReturnEjectInvalidCoinOutputsInvalidCoinEjected(void) {
	//Mock output, expect CoinReturn to output the correct string.
	CommonOutput_Expect(COINRETURN_INVALID_MSG);
	TEST_ASSERT_TRUE(CoinReturnEjectCoin(COIN_INVALID));
}

void test_CoinReturnEjectPennyOutputsPennyEjected(void) {
	//Mock output, expect CoinReturn to output the correct string.
	CommonOutput_Expect(COINRETURN_PENNY_MSG);
	TEST_ASSERT_TRUE(CoinReturnEjectCoin(COIN_PENNY));
}

