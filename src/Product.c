
#include "Product.h"
#include "CoinSlot.h"
#include "Common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Create the Product object.
Product *ProductCreate(void) {
	Product *p = calloc(1, sizeof(Product));
	if(p) {
		p->stock = PROPERTY_UNINITIALIZED;
		p->value = PROPERTY_UNINITIALIZED;
	}
	return p;
}

//Destroy a Product object.
Product *ProductDestroy(Product *prod) {
	free(prod);
	return NULL;
}

//Allow passing us the CoinChanger object, so we can make change when vending.
bool ProductSetCoinChanger(Product *prod, CoinChanger *c) {
	prod->changer = c;
	return true;
}

//Allow passing us the CoinSlot object, so we can receive money in exchange for products when vending.
bool ProductSetCoinSlot(Product *prod, CoinSlot *s) {
	prod->slot = s;
	return true;
}

//Allow setting the name of a Product object.
bool ProductSetName(Product *prod, const char *n) {
	strncpy(prod->name, n, PRODUCT_NAME_MAXLEN);
	return true;
}

//Return the name of a Product object.
char *ProductGetName(Product *prod) {
	return prod->name;
}

//Allow setting the current stock of a Product object.
bool ProductSetStock(Product *prod, uint8_t s) {
	if(s > 127) {
		return false;
	}
	prod->stock = s;
	return true;
}

//Return the current stock of a Product object.
int8_t ProductGetStock(Product *prod) {
	return prod->stock;
}

//Allow setting the current value of a Product object.
bool ProductSetValue(Product *prod, uint8_t v) {
	if(v > 127) {
		return false;
	}
	prod->value = v;
	return true;
}

//Return the current value of a Product object.
int8_t ProductGetValue(Product *prod) {
	return prod->value;
}

//User requests vending of a Product
bool ProductRequestVend(Product *prod) {
	//Don't proceed unless we're fully initialized with a CoinChanger and a CoinSlot.
	if(prod->slot == NULL || prod->changer == NULL) {
		return false;
	}
	
	//In order to process a vend request, we need to make sure we have enough funds to cover the transaction.
	CoinSlotValue(prod->slot);
	
	//Flush the CoinSlot.
	CoinSlotFlush(prod->slot);
	
	//Finally vend the product.
	char msg[24];
	snprintf(msg, 24, "%s %s", PRODUCT_VEND_MESSAGE, prod->name);
	CommonOutput(msg);
	
	return true;
}

