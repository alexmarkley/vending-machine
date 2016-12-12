
#include "CoinSlot.h"

#include <stdlib.h>

//Create the CoinSlot object.
CoinSlot *CoinSlotCreate(void) {
	CoinSlot *s = calloc(1, sizeof(CoinSlot));
	return s;
}

//Insert a coin into the CoinSlot
int16_t CoinSlotInsertCoin(CoinSlot *slot, uint8_t coin) {
	//Check coin value for validity.
	if(coin != COINSLOT_NICKEL && coin != COINSLOT_DIME && coin != COINSLOT_QUARTER) {
		return COINSLOT_REJECTED_COINRETURN;
	}
	
	//Seek an empty slot in the intake array for this coin.
	for(uint8_t i = 0; i < COINSLOT_INTAKE_MAXCOINS; i++) {
		//If this slot has a zero value, there is no coin stored here.
		if(slot->intake[i] == 0) {
			//Store this coin's value in this slot.
			slot->intake[i] = coin;
			//Increment this slot's current value accordingly.
			slot->value += coin;
			//Get out of here!
			break;
		}
	}
	
	return slot->value;
}
