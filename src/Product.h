
#ifndef __VENDING_MACHINE_PRODUCT_H

#include <stdint.h>

//Define the Product object.
typedef struct Product {
	uint8_t i;
} Product;

//Functions within this module.
Product *ProductCreate(void);
Product *ProductDestroy(Product *prod);


#define __VENDING_MACHINE_PRODUCT_H
#endif
