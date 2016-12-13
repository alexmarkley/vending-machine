
#include "unity.h"
#include "Product.h"

void test_ProductCreateShouldReturnNonNull(void) {
	TEST_ASSERT_NOT_NULL(ProductCreate());
}

int main(void) {
	UNITY_BEGIN();
	RUN_TEST(test_ProductCreateShouldReturnNonNull);
	return UNITY_END();
}

