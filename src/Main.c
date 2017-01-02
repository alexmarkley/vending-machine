
#include "Main.h"
#include "Common.h"
#include "Product.h"
#include "CoinChanger.h"
#include "CoinSlot.h"

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
	CoinSlot *slot;
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
	
	//Set up the CoinSlot.
	if(!(slot = CoinSlotCreate())) {
		CommonOutput(MAIN_FATAL_ERROR);
		return 1;
	}
	
	//Initially ask CoinSlot to update the display.
	CoinSlotUpdateDisplay(slot);
	
	//Main running loop.
	while(running) {
		//Solicit input from the user.
		printf(" > ");
		char command = CommonInput();
		uint8_t whichProduct;
		switch(command) {
			case 0:
			case 'Q':
				running = false;
				break;
			case 'p':
				CoinSlotInsertCoin(slot, COIN_PENNY);
				break;
			case 'n':
				CoinSlotInsertCoin(slot, COIN_NICKEL);
				break;
			case 'd':
				CoinSlotInsertCoin(slot, COIN_DIME);
				break;
			case 'q':
				CoinSlotInsertCoin(slot, COIN_QUARTER);
				break;
			case 'r':
				CoinSlotReturnAll(slot);
				break;
			case '1':
			case '2':
			case '3':
				whichProduct = command - (uint8_t)'1';
				ProductRequestVend(products[whichProduct]);
				break;
		}
	}
	
	//Clean up!
	for(uint8_t x = 0; x < 3; x++) {
		ProductDestroy(products[x]);
	}
	CoinChangerDestroy(changer);
	CoinSlotDestroy(slot);
	
	return 0;
}

