
#ifndef __VENDING_MACHINE_COINSLOT_H

#include <stdint.h>
#include <stdbool.h>
#include "CoinChanger.h"

//Enumerations within this module.
enum {
	COINSLOT_REJECTED_COINRETURN = -1,
	COINSLOT_REJECTED_SLOTFULL = -2
};

//Other definitions.
#define COINSLOT_MSG_PREFIX "CoinSlot: "
#define COINSLOT_INTAKE_MAXCOINS 25 //For mechanical reasons, we cannot accept more coins than this at once.
#define COINSLOT_INSERTCOIN_MESSAGE COINSLOT_MSG_PREFIX "INSERT COIN"
#define COINSLOT_EXACTCHANGE_MESSAGE COINSLOT_MSG_PREFIX "EXACT CHANGE ONLY"

//Define the CoinSlot object.
typedef struct CoinSlot {
	uint16_t value; //Current value stored in the intake of the coin slot.
	uint8_t intake[COINSLOT_INTAKE_MAXCOINS]; //Array of non-rejected coins the customer has inserted.
	
	CoinChanger *changer;
} CoinSlot;

//Functions within this module.
CoinSlot *CoinSlotCreate(void);
CoinSlot *CoinSlotDestroy(CoinSlot *slot);
bool CoinSlotSetCoinChanger(CoinSlot *slot, CoinChanger *c);
int16_t CoinSlotInsertCoin(CoinSlot *slot, uint8_t coin);
uint16_t CoinSlotValue(CoinSlot *slot);
void CoinSlotFlush(CoinSlot *slot);
bool CoinSlotReturnAll(CoinSlot *slot);
void CoinSlotUpdateDisplay(CoinSlot *slot);

#define __VENDING_MACHINE_COINSLOT_H
#endif
