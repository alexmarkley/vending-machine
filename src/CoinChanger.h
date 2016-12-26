
#ifndef __VENDING_MACHINE_COINCHANGER_H

#include <stdint.h>
#include <stdbool.h>

//Misc definitions.
#define COINCHANGER_PROPERTY_UNINITIALIZED (-1)

//Define the CoinChanger object.
typedef struct CoinChanger {
	int8_t nickels;
	int8_t dimes;
	int8_t quarters;
} CoinChanger;

//Functions within this module.
CoinChanger *CoinChangerCreate(void);
CoinChanger *CoinChangerDestroy(CoinChanger *changer);
bool CoinChangerSetNickels(CoinChanger *changer, uint8_t n);
int8_t CoinChangerGetNickels(CoinChanger *changer);
bool CoinChangerSetDimes(CoinChanger *changer, uint8_t d);
int8_t CoinChangerGetDimes(CoinChanger *changer);
bool CoinChangerSetQuarters(CoinChanger *changer, uint8_t q);
int8_t CoinChangerGetQuarters(CoinChanger *changer);
bool CoinChangerMakeChange(CoinChanger *changer, uint16_t amount);

#define __VENDING_MACHINE_COINCHANGER_H
#endif
