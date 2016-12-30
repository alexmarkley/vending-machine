
#include "Main.h"
#include "Common.h"
#include "Product.h"

//Do not define a main() function if we are under test.
#ifndef TEST
int main(int argc, char **argv) {
	return MainEntry(argc, argv);
}
#endif

//For all practical purposes, MainEntry() is our actual entry point, because it's testable.
int MainEntry(int argc, char **argv) {
	Product *products[3];
	const uint8_t products_initial_values[3] = {
		MAIN_PRODA_VALUE,
		MAIN_PRODB_VALUE,
		MAIN_PRODC_VALUE
	};
	const uint8_t products_initial_stocks[3] = {
		MAIN_PRODA_STOCK,
		MAIN_PRODB_STOCK,
		MAIN_PRODC_STOCK
	};
	
	//Output the initialization banner.
	CommonOutput(MAIN_INITIALIZATION_MESSAGE);
	
	//Set up our products.
	for(uint8_t x = 0; x < 3; x++) {
		if(!(products[x] = ProductCreate())) {
			CommonOutput(MAIN_FATAL_ERROR);
			return 1;
		}
		ProductSetValue(products[x], products_initial_values[x]);
		ProductSetStock(products[x], products_initial_stocks[x]);
	}
	
	return 0;
}

