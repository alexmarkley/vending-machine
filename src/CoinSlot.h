
#ifndef __VENDING_MACHINE_COINSLOT_H

#include <stdint.h>

//Enumerations within this module.
enum {
	COINSLOT_REJECTED_COINRETURN = -1,
	COINSLOT_REJECTED_SLOTFULL = -2
};

enum {
	COINSLOT_PENNY = -1,
	COINSLOT_NICKEL = 5,
	COINSLOT_DIME = 10,
	COINSLOT_QUARTER = 25
};

//Other definitions.
#define COINSLOT_INTAKE_MAXCOINS 25 //For mechanical reasons, we cannot accept more coins than this at once.

//Define the CoinSlot object.
typedef struct CoinSlot {
	uint16_t value; //Current value stored in the intake of the coin slot.
	uint8_t intake[COINSLOT_INTAKE_MAXCOINS]; //Array of non-rejected coins the customer has inserted.
} CoinSlot;

//Functions within this module.
CoinSlot *CoinSlotCreate(void);
int16_t CoinSlotInsertCoin(CoinSlot *slot, uint8_t coin);

#define __VENDING_MACHINE_COINSLOT_H
#endif
