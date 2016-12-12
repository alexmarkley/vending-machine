
#include "CoinSlot.h"

#include <stdlib.h>

CoinSlot *CoinSlotCreate(void) {
	CoinSlot *s = calloc(1, sizeof(CoinSlot));
	return s;
}
