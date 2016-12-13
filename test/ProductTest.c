
#include "unity.h"
#include "Product.h"

void test_ProductCreateShouldReturnNonNull(void) {
	TEST_ASSERT_NOT_NULL(ProductCreate());
}

void test_ProductDestroyShouldReturnNull(void) {
	Product *prod = ProductCreate();
	TEST_ASSERT_NULL(ProductDestroy(prod));
}

int main(void) {
	UNITY_BEGIN();
	RUN_TEST(test_ProductCreateShouldReturnNonNull);
	RUN_TEST(test_ProductDestroyShouldReturnNull);
	return UNITY_END();
}

