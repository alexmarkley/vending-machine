
#include "CoinChanger.h"

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
	//Determine how much of the amount can be doled out in quarters.
	uint8_t outQuarters = (uint8_t)(amount / (uint16_t)25);
	//Less if we are limited by our inventory.
	if(changer->quarters < outQuarters) {
		outQuarters = changer->quarters;
	}
	//Calculate the remainder.
	amount -= outQuarters * 25;
	
	//If amount is zero, we successfully made change for the full amount.
	if(amount == 0) {
		changer->quarters -= outQuarters;
		
		//Success;
		return true;
	}
	
	//We did not successfully make change for the full amount.
	return false;
}

