
#include "CoinSlot.h"

#include <stdlib.h>
#include <stdbool.h>

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

//Insert a coin into the CoinSlot
int16_t CoinSlotInsertCoin(CoinSlot *slot, uint8_t coin) {
	//Check coin value for validity.
	if(coin != COINSLOT_NICKEL && coin != COINSLOT_DIME && coin != COINSLOT_QUARTER) {
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
	
	return slot->value;
}
