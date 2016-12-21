
#ifndef __VENDING_MACHINE_COINCHANGER_H

#include <stdint.h>
#include <stdbool.h>

//Misc definitions.
#define COINCHANGER_PROPERTY_UNINITIALIZED (-1)

//Define the CoinChanger object.
typedef struct CoinChanger {
	int8_t nickels;
} CoinChanger;

//Functions within this module.
CoinChanger *CoinChangerCreate(void);
CoinChanger *CoinChangerDestroy(CoinChanger *changer);
bool CoinChangerSetNickels(CoinChanger *changer, uint8_t n);
int8_t CoinChangerGetNickels(CoinChanger *changer);

#define __VENDING_MACHINE_COINCHANGER_H
#endif
