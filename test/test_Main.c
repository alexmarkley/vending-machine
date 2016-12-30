
#include "unity.h"
#include "Main.h"
#include "Common.h"
#include "mock_Common.h"
#include "mock_Product.h"

#include <stdlib.h>

void setUp(void) {
}

void tearDown(void) {
}

void test_MainShouldOutputTheInitializationBannerSetUpThreeProductsAndReturnZero(void) {
	char *args[1] = {"./vending-machine"};
	Product *products[3];
	
	//Mock output, expect the initialization banner.
	CommonOutput_ExpectAndReturn(MAIN_INITIALIZATION_MESSAGE, 1);
	
	//Mock product creation.
	//(Need real allocated memory for the Product objects, not because Main dereferences them (it doesn't) but because Unity compares the memory blocks and it will crash if we use symbols instead of pointers to real allocated memory.)
	ProductCreate_ExpectAndReturn(products[0] = calloc(1, sizeof(Product))); //PRODA
	ProductCreate_ExpectAndReturn(products[1] = calloc(1, sizeof(Product))); //PRODB
	ProductCreate_ExpectAndReturn(products[2] = calloc(1, sizeof(Product))); //PRODC
	ProductSetStock_ExpectAndReturn(products[0], MAIN_PRODA_STOCK, true);
	ProductSetStock_ExpectAndReturn(products[1], MAIN_PRODB_STOCK, true);
	ProductSetStock_ExpectAndReturn(products[2], MAIN_PRODC_STOCK, true);
	ProductSetValue_ExpectAndReturn(products[0], MAIN_PRODA_VALUE, true);
	ProductSetValue_ExpectAndReturn(products[1], MAIN_PRODB_VALUE, true);
	ProductSetValue_ExpectAndReturn(products[2], MAIN_PRODC_VALUE, true);
	
	TEST_ASSERT_EQUAL_INT(0, MainEntry(1, args));
	
	//Don't leak memory, even in testing.
	free(products[0]);
	free(products[1]);
	free(products[2]);
}

void test_MainShouldFailGracefullyIfProductCreateFailsAndReturnOne(void) {
	char *args[1] = {"./vending-machine"};
	
	//Mock output, expect the initialization banner and a fatal error.
	CommonOutput_ExpectAndReturn(MAIN_INITIALIZATION_MESSAGE, 1);
	CommonOutput_ExpectAndReturn(MAIN_FATAL_ERROR, 1);
	
	//Mock product creation. (Return NULL to simulate an allocation failure.)
	ProductCreate_ExpectAndReturn(NULL); //PRODA
	
	//Expect main to come back with an error code.
	TEST_ASSERT_EQUAL_INT(1, MainEntry(1, args));
}

void test_MainShouldFailGracefullyIfProductSetValueFailsAndReturnOne(void) {
	char *args[1] = {"./vending-machine"};
	Product *products[2];
	
	//Mock output, expect the initialization banner and a fatal error.
	CommonOutput_ExpectAndReturn(MAIN_INITIALIZATION_MESSAGE, 1);
	CommonOutput_ExpectAndReturn(MAIN_FATAL_ERROR, 1);
	
	//Mock product creation as explained above.
	ProductCreate_ExpectAndReturn(products[0] = calloc(1, sizeof(Product))); //PRODA
	ProductCreate_ExpectAndReturn(products[1] = calloc(1, sizeof(Product))); //PRODB
	ProductSetStock_ExpectAndReturn(products[0], MAIN_PRODA_STOCK, true);
	ProductSetValue_ExpectAndReturn(products[0], MAIN_PRODA_VALUE, true);
	ProductSetValue_ExpectAndReturn(products[1], MAIN_PRODB_VALUE, false); //Simulate a failure here.
	
	//Expect main to come back with an error code.
	TEST_ASSERT_EQUAL_INT(1, MainEntry(1, args));
	
	//Don't leak memory, even in testing.
	free(products[0]);
	free(products[1]);
}

void test_MainShouldFailGracefullyIfProductSetStockFailsAndReturnOne(void) {
	char *args[1] = {"./vending-machine"};
	Product *products[3];
	
	//Mock output, expect the initialization banner and a fatal error.
	CommonOutput_ExpectAndReturn(MAIN_INITIALIZATION_MESSAGE, 1);
	CommonOutput_ExpectAndReturn(MAIN_FATAL_ERROR, 1);
	
	//Mock product creation.
	//(Need real allocated memory for the Product objects, not because Main dereferences them (it doesn't) but because Unity compares the memory blocks and it will crash if we use symbols instead of pointers to real allocated memory.)
	ProductCreate_ExpectAndReturn(products[0] = calloc(1, sizeof(Product))); //PRODA
	ProductCreate_ExpectAndReturn(products[1] = calloc(1, sizeof(Product))); //PRODB
	ProductCreate_ExpectAndReturn(products[2] = calloc(1, sizeof(Product))); //PRODC
	ProductSetStock_ExpectAndReturn(products[0], MAIN_PRODA_STOCK, true);
	ProductSetStock_ExpectAndReturn(products[1], MAIN_PRODB_STOCK, true);
	ProductSetStock_ExpectAndReturn(products[2], MAIN_PRODC_STOCK, false); //Simulate failure here.
	ProductSetValue_ExpectAndReturn(products[0], MAIN_PRODA_VALUE, true);
	ProductSetValue_ExpectAndReturn(products[1], MAIN_PRODB_VALUE, true);
	ProductSetValue_ExpectAndReturn(products[2], MAIN_PRODC_VALUE, true);
	
	//Expect main to come back with an error code.
	TEST_ASSERT_EQUAL_INT(1, MainEntry(1, args));
	
	//Don't leak memory, even in testing.
	free(products[0]);
	free(products[1]);
	free(products[2]);
}

