
#include "Product.h"

#include <stdlib.h>

//Create the Product object.
Product *ProductCreate(void) {
	Product *p = calloc(1, sizeof(Product));
	return p;
}

//Destroy a Product object.
Product *ProductDestroy(Product *prod) {
	free(prod);
	return NULL;
}
