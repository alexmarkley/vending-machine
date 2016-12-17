
#include "unity.h"
#include "Product.h"

void test_ProductCreateShouldReturnNonNull(void) {
	TEST_ASSERT_NOT_NULL(ProductCreate());
}

void test_ProductDestroyShouldReturnNull(void) {
	Product *prod = ProductCreate();
	TEST_ASSERT_NULL(ProductDestroy(prod));
}

void test_ProductUninitializedStockShouldBeNegativeOne(void) {
	Product *prod = ProductCreate();
	TEST_ASSERT_EQUAL_INT8(PRODUCT_STOCK_UNINITIALIZED, ProductGetStock(prod));
}

int main(void) {
	UNITY_BEGIN();
	RUN_TEST(test_ProductCreateShouldReturnNonNull);
	RUN_TEST(test_ProductDestroyShouldReturnNull);
	RUN_TEST(test_ProductUninitializedStockShouldBeNegativeOne);
	return UNITY_END();
}

