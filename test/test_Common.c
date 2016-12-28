#include "unity.h"
#include "Common.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_CommonOutputSevenByteStringReturnsEight(void) {
	//CommonOutput depends on printf and appends a newline (\n) to the end of each passed string.
	//The return value is the total number of characters printed, up to and including the \n.
	TEST_ASSERT_EQUAL_INT(8, CommonOutput("TESTING"));
}

