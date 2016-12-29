
#ifndef __VENDING_MACHINE_COMMON_H

enum {
	COIN_INVALID = -1,
	COIN_PENNY = 1,
	COIN_NICKEL = 5,
	COIN_DIME = 10,
	COIN_QUARTER = 25
};

#define PROPERTY_UNINITIALIZED (-1)

//Functions within this module.
int CommonOutput(const char *str);

#define __VENDING_MACHINE_COMMON_H
#endif
