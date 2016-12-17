
#ifndef __VENDING_MACHINE_COINCHANGER_H

#include <stdint.h>

//Define the CoinChanger object.
typedef struct CoinChanger {
	int8_t x;
} CoinChanger;

//Functions within this module.
CoinChanger *CoinChangerCreate(void);

#define __VENDING_MACHINE_COINCHANGER_H
#endif
