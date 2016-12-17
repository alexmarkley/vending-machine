
#include "unity.h"
#include "Product.h"

void test_ProductCreateShouldReturnNonNull(void) {
	TEST_ASSERT_NOT_NULL(ProductCreate());
}

void test_ProductDestroyShouldReturnNull(void) {
	Product *prod = ProductCreate();
	TEST_ASSERT_NULL(ProductDestroy(prod));
}

void test_ProductGetStockShouldStartUninitialized(void) {
	Product *prod = ProductCreate();
	TEST_ASSERT_EQUAL_INT8(PRODUCT_STOCK_UNINITIALIZED, ProductGetStock(prod));
}

void test_ProductSetStockShouldReturnTrue(void) {
	Product *prod = ProductCreate();
	TEST_ASSERT_TRUE(ProductSetStock(prod, 35));
}

int main(void) {
	UNITY_BEGIN();
	RUN_TEST(test_ProductCreateShouldReturnNonNull);
	RUN_TEST(test_ProductDestroyShouldReturnNull);
	RUN_TEST(test_ProductGetStockShouldStartUninitialized);
	RUN_TEST(test_ProductSetStockShouldReturnTrue);
	return UNITY_END();
}

