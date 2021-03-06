
#ifndef __VENDING_MACHINE_MAIN_H

#define MAIN_MSG_PREFIX "Main: "
#define MAIN_INITIALIZATION_MESSAGE MAIN_MSG_PREFIX "Welcome to the Vending Machine Demo Frontend. For help, see README.md."
#define MAIN_FATAL_ERROR MAIN_MSG_PREFIX "There has been a fatal error! Going down..."

#define MAIN_PRODA_NAME "Cola" //The human-readable name of the first product.
#define MAIN_PRODA_VALUE 100   //The cost of the first product.
#define MAIN_PRODA_STOCK 48    //The initial inventory of the first product.

#define MAIN_PRODB_NAME "Chips" //The human-readable name of the second product.
#define MAIN_PRODB_VALUE 50     //The cost of the second product.
#define MAIN_PRODB_STOCK 50     //The initial inventory of the second product.

#define MAIN_PRODC_NAME "Candy" //The human-readable name of the third product.
#define MAIN_PRODC_VALUE 65     //The cost of the third product.
#define MAIN_PRODC_STOCK 100    //The initial inventory of the third product.

#define MAIN_COINCHANGER_QUARTERS 80 //Two full rolls of quarters, for a total of $20
#define MAIN_COINCHANGER_DIMES 100   //Two full rolls of dimes, for a total of $10
#define MAIN_COINCHANGER_NICKELS 80  //Two full rolls of nickels, for a total of $4

int MainEntry(int argc, char **argv);

#define __VENDING_MACHINE_MAIN_H
#endif

