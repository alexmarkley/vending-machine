
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
	if(coin != COINSLOT_NICKEL) {
		return COINSLOT_REJECTED_COINRETURN;
	}
	
	return coin;
}
