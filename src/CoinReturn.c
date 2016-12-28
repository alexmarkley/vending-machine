
#include "CoinReturn.h"
#include "Common.h"

bool CoinReturnEjectCoin(uint8_t coin) {
	switch(coin) {
		default:
			CommonOutput(COINRETURN_INVALID_MSG);
			break;
		case COIN_PENNY:
			CommonOutput(COINRETURN_PENNY_MSG);
			break;
		case COIN_NICKEL:
			CommonOutput(COINRETURN_NICKEL_MSG);
			break;
	}
	return true;
}

