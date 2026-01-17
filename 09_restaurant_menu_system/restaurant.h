#ifndef RESTAURANT_H
#define RESTAURANT_H

#include "menu.h"

// Struct that represents a restaurant and its menu
typedef struct{
    char *name;
    Menu *menu[20];
    int numItems;
    float discount;
} Restaurant;

// Functions for managing restaurants, their menus, and discounts
Restaurant * Restaurant_Construct(const char *nameIn, float discountIn);
int Restaurant_AddMenuItem(Restaurant *r, Menu *m);
void Restaurant_PrintMenu(Restaurant *r);
int Restaurant_RemoveMenuItem(Restaurant *r, int remove);
void Restaurant_PrintFestivalItems(Restaurant *r, char *festival);
void Restaurant_AdjustDiscount(Restaurant *r, float newVal);
void Restaurant_PrintMenuWithDiscount(Restaurant *r, char *festival);
void Restaurant_Destruct(Restaurant *r);

#endif
