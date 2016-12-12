
#ifndef __VENDING_MACHINE_COINSLOT_H

#include <stdint.h>

//Define the CoinSlot object.
typedef struct CoinSlot {
	uint8_t x;
} CoinSlot;

//Enumerations within this module.
enum {
	COINSLOT_REJECTED_COINRETURN = -1
};

enum {
	COINSLOT_PENNY = -1
};

//Functions within this module.
CoinSlot *CoinSlotCreate(void);
int16_t CoinSlotInsertCoin(CoinSlot *slot, uint8_t *coin);

#define __VENDING_MACHINE_COINSLOT_H
#endif
