
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

//Return the current stock of a Product object.
int8_t ProductGetStock(Product *prod) {
	return prod->stock;
}
