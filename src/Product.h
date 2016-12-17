
#ifndef __VENDING_MACHINE_PRODUCT_H

#include <stdint.h>

//Misc definitions.
#define PRODUCT_STOCK_UNINITIALIZED (-1)

//Define the Product object.
typedef struct Product {
	uint8_t stock;
} Product;

//Functions within this module.
Product *ProductCreate(void);
Product *ProductDestroy(Product *prod);
int8_t ProductGetStock(Product *prod);


#define __VENDING_MACHINE_PRODUCT_H
#endif
