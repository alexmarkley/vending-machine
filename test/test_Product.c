
#include "unity.h"
#include "Product.h"
#include "CoinChanger.h"
#include "Common.h"

#include <stdlib.h>

CoinChanger *changer;

void setUp(void) {
}

void tearDown(void) {
}

void test_ProductCreateShouldReturnNonNull(void) {
	TEST_ASSERT_NOT_NULL(ProductCreate());
}

void test_ProductDestroyShouldReturnNull(void) {
	Product *prod = ProductCreate();
	TEST_ASSERT_NULL(ProductDestroy(prod));
}

void test_ProductSetCoinChangerShouldSetInternalStateAndReturnTrue(void) {
	Product *prod = ProductCreate();
	TEST_ASSERT_TRUE(ProductSetCoinChanger(prod, changer = calloc(1, sizeof(CoinChanger))));
	TEST_ASSERT_EQUAL_PTR(changer, prod->changer);
	ProductDestroy(prod);
	free(changer);
}

void test_ProductGetNameShouldStartNull(void) {
	Product *prod = ProductCreate();
	TEST_ASSERT_EQUAL_STRING("", ProductGetName(prod));
	ProductDestroy(prod);
}

void test_ProductSetNameShouldReturnTrue(void) {
	Product *prod = ProductCreate();
	TEST_ASSERT_TRUE(ProductSetName(prod, "TEST"));
	ProductDestroy(prod);
}

void test_ProductSetNameShouldPersist(void) {
	Product *prod = ProductCreate();
	TEST_ASSERT_TRUE(ProductSetName(prod, "TEST"));
	TEST_ASSERT_EQUAL_STRING("TEST", ProductGetName(prod));
	ProductDestroy(prod);
}

void test_ProductGetStockShouldStartUninitialized(void) {
	Product *prod = ProductCreate();
	TEST_ASSERT_EQUAL_INT8(PROPERTY_UNINITIALIZED, ProductGetStock(prod));
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
	TEST_ASSERT_EQUAL_INT8(PROPERTY_UNINITIALIZED, ProductGetValue(prod));
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

void test_ProductRequestVendInitiallyShouldFailAndReturnFalse(void) {
	Product *prod = ProductCreate();
	TEST_ASSERT_FALSE(ProductRequestVend(prod));
	ProductDestroy(prod);
}

