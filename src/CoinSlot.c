
#include "CoinSlot.h"
#include "CoinReturn.h"
#include "Common.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>

//Create the CoinSlot object.
CoinSlot *CoinSlotCreate(void) {
	CoinSlot *s = calloc(1, sizeof(CoinSlot));
	return s;
}

//Destroy a CoinSlot object.
CoinSlot *CoinSlotDestroy(CoinSlot *slot) {
	free(slot);
	return NULL;
}

//Allow passing us the CoinChanger object, so we can check for EXACT CHANGE ONLY conditions.
bool CoinSlotSetCoinChanger(CoinSlot *slot, CoinChanger *c) {
	slot->changer = c;
	return true;
}

//Insert a coin into the CoinSlot
int16_t CoinSlotInsertCoin(CoinSlot *slot, uint8_t coin) {
	//Check coin value for validity.
	if(coin != COIN_NICKEL && coin != COIN_DIME && coin != COIN_QUARTER) {
		//Whatever this coin is, it is being/has been ejected via the coin return.
		CoinReturnEjectCoin(coin);
		return COINSLOT_REJECTED_COINRETURN;
	}
	
	//Seek an empty index in the intake array for this coin.
	bool foundFit = false;
	for(uint8_t i = 0; i < COINSLOT_INTAKE_MAXCOINS; i++) {
		//If this index has a zero value, there is no coin stored here.
		if(slot->intake[i] == 0) {
			//We found a fit for this coin.
			foundFit = true;
			//Store this coin's value in this slot.
			slot->intake[i] = coin;
			//Increment this slot's current value accordingly.
			slot->value += coin;
			//Get out of here!
			break;
		}
	}
	
	//If we didn't find a fit, this is a particular kind of failure case.
	if(!foundFit) {
		return COINSLOT_REJECTED_SLOTFULL;
	}
	
	//Once the slot value has been incremented, we should update the display with the new value.
	CoinSlotUpdateDisplay(slot);
	
	return slot->value;
}

//Return the current value stored in the CoinSlot intake.
uint16_t CoinSlotValue(CoinSlot *slot) {
	return slot->value;
}

//Flush the internal state of a CoinSlot.
void CoinSlotFlush(CoinSlot *slot) {
	slot->value = 0;
	for(uint8_t i = 0; i < COINSLOT_INTAKE_MAXCOINS; i++) {
		slot->intake[i] = 0;
	}
	
	//Once the slot has been flushed, we should update the display with the INSERT COIN message.
	CoinSlotUpdateDisplay(slot);
}

//Send all of the coins in the CoinSlot back via the CoinReturn.
bool CoinSlotReturnAll(CoinSlot *slot) {
	bool success = true;
	
	//Loop through the intake of this CoinSlot.
	for(uint8_t i = 0; slot->intake[i]; i++) {
		//Eject this coin via the CoinReturn.
		if(!CoinReturnEjectCoin(slot->intake[i])) {
			success = false;
			break;
		}
	}
	
	//Flush the CoinSlot.
	CoinSlotFlush(slot);

	return success;
}

//Update the display with the current status of the coin slot.
void CoinSlotUpdateDisplay(CoinSlot *slot) {
	if(slot->value == 0) {
		if(slot->changer != NULL) {
			CommonOutput(COINSLOT_INSERTCOIN_MESSAGE);
		}
		return;
	} else {
		//Break out dollars and cents from the slot value.
		uint16_t dollars = (slot->value / (uint16_t)100);
		uint8_t cents = slot->value - (dollars * 100);
		//Build a display string. (max "CoinSlot: $NNNNN.NN\0")
		char display[20];
		snprintf(display, 20, COINSLOT_MSG_PREFIX "$%" PRIu16 ".%02" PRIu8, dollars, cents);
		CommonOutput(display);
	}
}

