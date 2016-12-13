
#include "Product.h"

#include <stdlib.h>

//Create the Product object.
Product *ProductCreate(void) {
	Product *p = calloc(1, sizeof(Product));
	return p;
}
