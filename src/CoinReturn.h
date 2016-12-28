
#ifndef __VENDING_MACHINE_COINRETURN_H

#include <stdint.h>
#include <stdbool.h>

enum {
	COINRETURN_QUARTER = 25,
	COINRETURN_DIME = 10,
	COINRETURN_NICKEL = 5
};

//Functions within this module.
bool CoinReturnEjectCoin(uint8_t coin);

#define __VENDING_MACHINE_COINRETURN_H
#endif
