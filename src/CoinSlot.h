
#ifndef __VENDING_MACHINE_COINSLOT_H

#include <stdint.h>

typedef struct CoinSlot {
	uint8_t x;
} CoinSlot;

CoinSlot *CoinSlotCreate(void);

#define __VENDING_MACHINE_COINSLOT_H
#endif
