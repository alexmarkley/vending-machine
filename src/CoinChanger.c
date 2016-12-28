
#include "CoinChanger.h"
#include "CoinReturn.h"

#include <stdlib.h>

//Create the CoinChanger object.
CoinChanger *CoinChangerCreate(void) {
	CoinChanger *c = calloc(1, sizeof(CoinChanger));
	c->nickels = COINCHANGER_PROPERTY_UNINITIALIZED;
	c->dimes = COINCHANGER_PROPERTY_UNINITIALIZED;
	c->quarters = COINCHANGER_PROPERTY_UNINITIALIZED;
	return c;
}

//Destroy a CoinChanger object.
CoinChanger *CoinChangerDestroy(CoinChanger *changer) {
	free(changer);
	return NULL;
}

//Allow setting the current number of nickels in the CoinChanger object.
bool CoinChangerSetNickels(CoinChanger *changer, uint8_t n) {
	if(n > 127) {
		return false;
	}
	changer->nickels = n;
	return true;
}

//Return the current number of nickels in the CoinChanger object.
int8_t CoinChangerGetNickels(CoinChanger *changer) {
	return changer->nickels;
}

//Allow setting the current number of dimes in the CoinChanger object.
bool CoinChangerSetDimes(CoinChanger *changer, uint8_t d) {
	if(d > 127) {
		return false;
	}
	changer->dimes = d;
	return true;
}

//Return the current number of dimes in the CoinChanger object.
int8_t CoinChangerGetDimes(CoinChanger *changer) {
	return changer->dimes;
}

bool CoinChangerSetQuarters(CoinChanger *changer, uint8_t q) {
	if(q > 127) {
		return false;
	}
	changer->quarters = q;
	return true;
}

//Return the current number of quarters in the CoinChanger object.
int8_t CoinChangerGetQuarters(CoinChanger *changer) {
	return changer->quarters;
}

//If possible, using the coins we have in our inventory, make change for the amount requested.
bool CoinChangerMakeChange(CoinChanger *changer, uint16_t amount) {
	uint8_t outQuarters = 0, outDimes = 0;
	
	//Determine how much of the amount can be doled out in quarters.
	outQuarters = (uint8_t)(amount / (uint16_t)25);
	//Less if we are limited by our inventory.
	if(changer->quarters < outQuarters) {
		outQuarters = changer->quarters;
	}
	//Calculate the remainder.
	amount -= outQuarters * 25;
	
	//Is there a remainder?
	if(amount > 0) {
		//Determine how much of the remaining amount can be doled out in dimes.
		outDimes = (uint8_t)(amount / (uint16_t)10);
		//Less if we are limited by our inventory.
		if(changer->dimes < outDimes) {
			outDimes = changer->dimes;
		}
		//Calculate the remainder.
		amount -= outDimes * 10;
	}
	
	//If remaining amount is zero, we successfully made change for the full amount.
	if(amount == 0) {
		//Ask CoinReturn to eject coins, starting with quarters.
		for(uint8_t x = 0; x < outQuarters; x++) {
			//Attempt to eject a coin.
			if(!CoinReturnEjectCoin(COINRETURN_QUARTER)) {
				//On failure, return false.
				return false;
			}
			//Update our inventory to match reality.
			changer->quarters--;
		}
		
		//Next eject Dimes
		for(uint8_t x = 0; x < outDimes; x++) {
			//Attempt to eject a coin.
			if(!CoinReturnEjectCoin(COINRETURN_DIME)) {
				//On failure, return false.
				return false;
			}
			//Update our inventory to match reality.
			changer->dimes--;
		}
		
		//Success.
		return true;
	}
	
	//We did not successfully make change for the full amount.
	return false;
}

