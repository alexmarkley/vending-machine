
#include "Main.h"
#include "Common.h"
#include "Product.h"
#include "CoinChanger.h"

#include <stdbool.h>
#include <stdio.h>

//Do not define a main() function if we are under test.
#ifndef TEST
int main(int argc, char **argv) {
	return MainEntry(argc, argv);
}
#endif

//For all practical purposes, MainEntry() is our actual entry point, because it's testable.
int MainEntry(int argc, char **argv) {
	bool running = true;
	Product *products[3];
	CoinChanger *changer;
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
		if(!ProductSetValue(products[x], products_initial_values[x])) {
			CommonOutput(MAIN_FATAL_ERROR);
			return 1;
		}
		if(!ProductSetStock(products[x], products_initial_stocks[x])) {
			CommonOutput(MAIN_FATAL_ERROR);
			return 1;
		}
	}
	
	//Set up the CoinChanger.
	if(!(changer = CoinChangerCreate())) {
		CommonOutput(MAIN_FATAL_ERROR);
		return 1;
	}
	if(!CoinChangerSetQuarters(changer, MAIN_COINCHANGER_QUARTERS)) {
		CommonOutput(MAIN_FATAL_ERROR);
		return 1;
	}
	if(!CoinChangerSetDimes(changer, MAIN_COINCHANGER_DIMES)) {
		CommonOutput(MAIN_FATAL_ERROR);
		return 1;
	}
	if(!CoinChangerSetNickels(changer, MAIN_COINCHANGER_NICKELS)) {
		CommonOutput(MAIN_FATAL_ERROR);
		return 1;
	}
	
	//Main running loop.
	while(running) {
		//Solicit input from the user.
		printf(" > ");
		char command = CommonInput();
		switch(command) {
			case 'Q':
				running = false;
				break;
		}
	}
	
	//Clean up!
	for(uint8_t x = 0; x < 3; x++) {
		ProductDestroy(products[x]);
	}
	CoinChangerDestroy(changer);
	
	return 0;
}

