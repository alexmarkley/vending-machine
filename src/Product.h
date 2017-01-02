
#ifndef __VENDING_MACHINE_PRODUCT_H

#include "CoinChanger.h"
#include "CoinSlot.h"
#include <stdint.h>
#include <stdbool.h>

//Misc definitions.
#define PRODUCT_NAME_MAXLEN 8
#define PRODUCT_VEND_MESSAGE "Product: Vended"

//Define the Product object.
typedef struct Product {
	char name[PRODUCT_NAME_MAXLEN];
	int8_t stock;
	int8_t value;
	
	CoinChanger *changer;
	CoinSlot *slot;
} Product;

//Functions within this module.
Product *ProductCreate(void);
Product *ProductDestroy(Product *prod);
bool ProductSetCoinChanger(Product *prod, CoinChanger *c);
bool ProductSetCoinSlot(Product *prod, CoinSlot *s);
bool ProductSetName(Product *prod, const char *n);
char *ProductGetName(Product *prod);
bool ProductSetStock(Product *prod, uint8_t s);
int8_t ProductGetStock(Product *prod);
bool ProductSetValue(Product *prod, uint8_t v);
int8_t ProductGetValue(Product *prod);
bool ProductRequestVend(Product *prod);

#define __VENDING_MACHINE_PRODUCT_H
#endif
