
#include "Product.h"
#include "Common.h"

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
	return false;
}

