
#include "unity.h"
#include "Product.h"
#include "CoinChanger.h"
#include "CoinSlot.h"
#include "Common.h"
#include "mock_CoinSlot.h"
#include "mock_Common.h"

#include <stdlib.h>

Product *prod;
CoinChanger *changer;
CoinSlot *slot;

void setUp(void) {
}

void tearDown(void) {
}

void normalProductSetUp(void) {
	TEST_ASSERT_NOT_NULL(prod = ProductCreate());
	TEST_ASSERT_TRUE(ProductSetCoinChanger(prod, changer = calloc(1, sizeof(CoinChanger))));
	TEST_ASSERT_TRUE(ProductSetCoinSlot(prod, slot = calloc(1, sizeof(CoinSlot))));
	TEST_ASSERT_TRUE(ProductSetValue(prod, 50));
	TEST_ASSERT_TRUE(ProductSetStock(prod, 1));
	TEST_ASSERT_TRUE(ProductSetName(prod, "TEST"));
}

void normalProductTearDown(void) {
	TEST_ASSERT_NULL(ProductDestroy(prod));
	free(changer);
	free(slot);
}

void test_ProductCreateShouldReturnNonNull(void) {
	TEST_ASSERT_NOT_NULL(ProductCreate());
}

void test_ProductDestroyShouldReturnNull(void) {
	TEST_ASSERT_NOT_NULL(prod = ProductCreate());
	TEST_ASSERT_NULL(ProductDestroy(prod));
}

void test_ProductSetCoinChangerShouldSetInternalStateAndReturnTrue(void) {
	TEST_ASSERT_NOT_NULL(prod = ProductCreate());
	TEST_ASSERT_TRUE(ProductSetCoinChanger(prod, changer = calloc(1, sizeof(CoinChanger))));
	TEST_ASSERT_EQUAL_PTR(changer, prod->changer);
	ProductDestroy(prod);
	free(changer);
}

void test_ProductSetCoinSlotShouldSetInternalStateAndReturnTrue(void) {
	TEST_ASSERT_NOT_NULL(prod = ProductCreate());
	TEST_ASSERT_TRUE(ProductSetCoinSlot(prod, slot = calloc(1, sizeof(CoinSlot))));
	TEST_ASSERT_EQUAL_PTR(slot, prod->slot);
	ProductDestroy(prod);
	free(slot);
}

void test_ProductGetNameShouldStartNull(void) {
	TEST_ASSERT_NOT_NULL(prod = ProductCreate());
	TEST_ASSERT_EQUAL_STRING("", ProductGetName(prod));
	ProductDestroy(prod);
}

void test_ProductSetNameShouldReturnTrue(void) {
	TEST_ASSERT_NOT_NULL(prod = ProductCreate());
	TEST_ASSERT_TRUE(ProductSetName(prod, "TEST"));
	ProductDestroy(prod);
}

void test_ProductSetNameShouldPersist(void) {
	TEST_ASSERT_NOT_NULL(prod = ProductCreate());
	TEST_ASSERT_TRUE(ProductSetName(prod, "TEST"));
	TEST_ASSERT_EQUAL_STRING("TEST", ProductGetName(prod));
	ProductDestroy(prod);
}

void test_ProductGetStockShouldStartUninitialized(void) {
	TEST_ASSERT_NOT_NULL(prod = ProductCreate());
	TEST_ASSERT_EQUAL_INT8(PROPERTY_UNINITIALIZED, ProductGetStock(prod));
	ProductDestroy(prod);
}

void test_ProductSetStockShouldReturnTrue(void) {
	TEST_ASSERT_NOT_NULL(prod = ProductCreate());
	TEST_ASSERT_TRUE(ProductSetStock(prod, 35));
	ProductDestroy(prod);
}

void test_ProductSetStockShouldPersist(void) {
	TEST_ASSERT_NOT_NULL(prod = ProductCreate());
	TEST_ASSERT_TRUE(ProductSetStock(prod, 48));
	TEST_ASSERT_EQUAL_INT8(48, ProductGetStock(prod));
	ProductDestroy(prod);
}

void test_ProductSetStockInvalidValueShouldReturnFalse(void) {
	TEST_ASSERT_NOT_NULL(prod = ProductCreate());
	TEST_ASSERT_FALSE(ProductSetStock(prod, 128));
	ProductDestroy(prod);
}

void test_ProductGetValueShouldStartUninitialized(void) {
	TEST_ASSERT_NOT_NULL(prod = ProductCreate());
	TEST_ASSERT_EQUAL_INT8(PROPERTY_UNINITIALIZED, ProductGetValue(prod));
	ProductDestroy(prod);
}

void test_ProductSetValueShouldReturnTrue(void) {
	TEST_ASSERT_NOT_NULL(prod = ProductCreate());
	TEST_ASSERT_TRUE(ProductSetValue(prod, 100));
	ProductDestroy(prod);
}

void test_ProductSetValueShouldPersist(void) {
	TEST_ASSERT_NOT_NULL(prod = ProductCreate());
	TEST_ASSERT_TRUE(ProductSetValue(prod, 65));
	TEST_ASSERT_EQUAL_INT8(65, ProductGetValue(prod));
	ProductDestroy(prod);
}

void test_ProductSetValueInvalidValueShouldReturnFalse(void) {
	TEST_ASSERT_NOT_NULL(prod = ProductCreate());
	TEST_ASSERT_FALSE(ProductSetValue(prod, 128));
	ProductDestroy(prod);
}

void test_ProductRequestVendInitiallyShouldFailAndReturnFalse(void) {
	TEST_ASSERT_NOT_NULL(prod = ProductCreate());
	TEST_ASSERT_FALSE(ProductRequestVend(prod));
	ProductDestroy(prod);
}

void test_ProductRequestVendShouldVendProductIfEnoughMoneyHasBeenInsertedIntoCoinSlot(void) {
	normalProductSetUp();
	
	//Check for enough funds to process the transaction and flush the slot once the transaction is complete.
	CoinSlotValue_ExpectAndReturn(slot, 50);
	CoinSlotFlush_Expect(slot);
	
	//Check for vend message.
	CommonOutput_ExpectAndReturn(PRODUCT_VEND_MESSAGE " TEST", 1);
	
	//Request vending.
	TEST_ASSERT_TRUE(ProductRequestVend(prod));
	
	normalProductTearDown();
}

void test_ProductRequestVendShouldNotVendProductIfNotEnoughMoneyHasBeenInsertedIntoCoinSlot(void) {
	normalProductSetUp();
	
	//Check for enough funds to process the transaction (not enough) and expect the display to be explicitly updated once.
	CoinSlotValue_ExpectAndReturn(slot, 25);
	CoinSlotUpdateDisplay_Expect(slot);
	
	//Check for price message.
	CommonOutput_ExpectAndReturn("PRICE $0.50", 1);
	
	//Request vending.
	TEST_ASSERT_FALSE(ProductRequestVend(prod));
	
	normalProductTearDown();
}


