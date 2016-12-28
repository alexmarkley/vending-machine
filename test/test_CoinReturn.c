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
	CommonOutput_ExpectAndReturn(COINRETURN_INVALID_MSG, 1);
	TEST_ASSERT_TRUE(CoinReturnEjectCoin(COIN_INVALID));
}

void test_CoinReturnEjectPennyOutputsPennyEjected(void) {
	//Mock output, expect CoinReturn to output the correct string.
	CommonOutput_ExpectAndReturn(COINRETURN_PENNY_MSG, 1);
	TEST_ASSERT_TRUE(CoinReturnEjectCoin(COIN_PENNY));
}

void test_CoinReturnEjectNickelOutputsNickelEjected(void) {
	//Mock output, expect CoinReturn to output the correct string.
	CommonOutput_ExpectAndReturn(COINRETURN_NICKEL_MSG, 1);
	TEST_ASSERT_TRUE(CoinReturnEjectCoin(COIN_NICKEL));
}

void test_CoinReturnEjectDimeOutputsDimeEjected(void) {
	//Mock output, expect CoinReturn to output the correct string.
	CommonOutput_ExpectAndReturn(COINRETURN_DIME_MSG, 1);
	TEST_ASSERT_TRUE(CoinReturnEjectCoin(COIN_DIME));
}

void test_CoinReturnEjectQuarterOutputsQuarterEjected(void) {
	//Mock output, expect CoinReturn to output the correct string.
	CommonOutput_ExpectAndReturn(COINRETURN_QUARTER_MSG, 1);
	TEST_ASSERT_TRUE(CoinReturnEjectCoin(COIN_QUARTER));
}

