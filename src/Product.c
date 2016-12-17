
#include "Product.h"

#include <stdlib.h>

//Create the Product object.
Product *ProductCreate(void) {
	Product *p = calloc(1, sizeof(Product));
	p->stock = PRODUCT_STOCK_UNINITIALIZED;
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
