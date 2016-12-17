
#ifndef __VENDING_MACHINE_PRODUCT_H

#include <stdint.h>
#include <stdbool.h>

//Misc definitions.
#define PRODUCT_STOCK_UNINITIALIZED (-1)
#define PRODUCT_VALUE_UNINITIALIZED (-1)

//Define the Product object.
typedef struct Product {
	int8_t stock;
	int8_t value;
} Product;

//Functions within this module.
Product *ProductCreate(void);
Product *ProductDestroy(Product *prod);
bool ProductSetStock(Product *prod, uint8_t s);
int8_t ProductGetStock(Product *prod);
bool ProductSetValue(Product *prod, uint8_t v);
int8_t ProductGetValue(Product *prod);

#define __VENDING_MACHINE_PRODUCT_H
#endif
