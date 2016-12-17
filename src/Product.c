
#include "Product.h"

#include <stdlib.h>

//Create the Product object.
Product *ProductCreate(void) {
	Product *p = calloc(1, sizeof(Product));
	p->stock = PRODUCT_STOCK_UNINITIALIZED;
	p->value = PRODUCT_VALUE_UNINITIALIZED;
	return p;
}

//Destroy a Product object.
Product *ProductDestroy(Product *prod) {
	free(prod);
	return NULL;
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