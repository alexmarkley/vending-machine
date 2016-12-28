
#ifndef __VENDING_MACHINE_COINRETURN_H

#include <stdint.h>
#include <stdbool.h>

#define COINRETURN_INVALID_MSG "CoinReturn: Invalid Coin Ejected"
#define COINRETURN_PENNY_MSG "CoinReturn: Penny Ejected"
#define COINRETURN_NICKEL_MSG "CoinReturn: Nickel Ejected"
#define COINRETURN_DIME_MSG "CoinReturn: Dime Ejected"

//Functions within this module.
bool CoinReturnEjectCoin(uint8_t coin);

#define __VENDING_MACHINE_COINRETURN_H
#endif
