
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
	ProductDestroy(prod);
}

void test_ProductSetStockShouldReturnTrue(void) {
	Product *prod = ProductCreate();
	TEST_ASSERT_TRUE(ProductSetStock(prod, 35));
	ProductDestroy(prod);
}

void test_ProductSetStockShouldPersist(void) {
	Product *prod = ProductCreate();
	TEST_ASSERT_TRUE(ProductSetStock(prod, 48));
	TEST_ASSERT_EQUAL_INT8(48, ProductGetStock(prod));
	ProductDestroy(prod);
}

void test_ProductSetStockInvalidValueShouldReturnFalse(void) {
	Product *prod = ProductCreate();
	TEST_ASSERT_FALSE(ProductSetStock(prod, 128));
	ProductDestroy(prod);
}

void test_ProductGetValueShouldStartUninitialized(void) {
	Product *prod = ProductCreate();
	TEST_ASSERT_EQUAL_INT8(PRODUCT_VALUE_UNINITIALIZED, ProductGetValue(prod));
	ProductDestroy(prod);
}

void test_ProductSetValueShouldReturnTrue(void) {
	Product *prod = ProductCreate();
	TEST_ASSERT_TRUE(ProductSetValue(prod, 100));
	ProductDestroy(prod);
}

void test_ProductSetValueShouldPersist(void) {
	Product *prod = ProductCreate();
	TEST_ASSERT_TRUE(ProductSetValue(prod, 65));
	TEST_ASSERT_EQUAL_INT8(65, ProductGetValue(prod));
	ProductDestroy(prod);
}

void test_ProductSetValueInvalidValueShouldReturnFalse(void) {
	Product *prod = ProductCreate();
	TEST_ASSERT_FALSE(ProductSetValue(prod, 128));
	ProductDestroy(prod);
}

int main(void) {
	UNITY_BEGIN();
	RUN_TEST(test_ProductCreateShouldReturnNonNull);
	RUN_TEST(test_ProductDestroyShouldReturnNull);
	RUN_TEST(test_ProductGetStockShouldStartUninitialized);
	RUN_TEST(test_ProductSetStockShouldReturnTrue);
	RUN_TEST(test_ProductSetStockShouldPersist);
	RUN_TEST(test_ProductSetStockInvalidValueShouldReturnFalse);
	RUN_TEST(test_ProductGetValueShouldStartUninitialized);
	RUN_TEST(test_ProductSetValueShouldReturnTrue);
	RUN_TEST(test_ProductSetValueShouldPersist);
	RUN_TEST(test_ProductSetValueInvalidValueShouldReturnFalse);
	return UNITY_END();
}

