
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
	
	//Output the initialization banner.
	CommonOutput(MAIN_INITIALIZATION_MESSAGE);
	
	//Set up our products.
	products[0] = ProductCreate();
	ProductSetValue(products[0], MAIN_PRODA_VALUE);
	ProductSetStock(products[0], MAIN_PRODA_STOCK);
	
	products[1] = ProductCreate();
	ProductSetValue(products[1], MAIN_PRODB_VALUE);
	ProductSetStock(products[1], MAIN_PRODB_STOCK);
	
	products[2] = ProductCreate();
	ProductSetValue(products[2], MAIN_PRODC_VALUE);
	ProductSetStock(products[2], MAIN_PRODC_STOCK);
	
	return 0;
}

