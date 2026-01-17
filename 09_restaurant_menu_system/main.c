#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "restaurant.h"
#include "menu.h"

int main(int argc, char **argv){

    // Create two restaurants with initial discount rates
    Restaurant *floyds  = Restaurant_Construct("Floyd's", 0.2);
    Restaurant *montana = Restaurant_Construct("Montana", 0.3);

    // Store restaurants in an array for iteration
    Restaurant *restaurants[2] = {floyds, montana};

    // ----- Floyd's menu items -----
    Menu *fm1 = Menu_Construct(1, "Fish and Chips", 12.99);
    Menu *fm2 = Menu_Construct(2, "Ceasar Salad", 14.99);
    Menu *fm3 = Menu_Construct(3, "Hamburger Platter", 15.99);

    // Assign tags and add items to Floyd's menu
    Menu_AddTag(fm1, "fries");
    Menu_AddTag(fm1, "fish");
    Menu_AddTag(fm1, "deepfried");
    Restaurant_AddMenuItem(floyds, fm1);

    Menu_AddTag(fm2, "healthy");
    Menu_AddTag(fm2, "lettuce");
    Menu_AddTag(fm2, "salad");
    Menu_AddTag(fm2, "chicken");
    Restaurant_AddMenuItem(floyds, fm2);

    Menu_AddTag(fm3, "fries");
    Menu_AddTag(fm3, "poutine");
    Menu_AddTag(fm3, "deepfried");
    Restaurant_AddMenuItem(floyds, fm3);

    // ----- Montana's menu items -----
    Menu *mm1 = Menu_Construct(1, "BBQ Chicken Nachos", 16.49);
    Menu *mm2 = Menu_Construct(2, "Ribs and Coleslaw", 12.99);
    Menu *mm3 = Menu_Construct(3, "Steak Sandwich", 18.99);

    // Assign tags and add items to Montana's menu
    Menu_AddTag(mm1, "nachos");
    Menu_AddTag(mm1, "chicken");
    Menu_AddTag(mm1, "fried");
    Restaurant_AddMenuItem(montana, mm1);

    Menu_AddTag(mm2, "ribs");
    Menu_AddTag(mm2, "lettuce");
    Menu_AddTag(mm2, "salad");
    Menu_AddTag(mm2, "bbq");
    Restaurant_AddMenuItem(montana, mm2);

    Menu_AddTag(mm3, "beef");
    Menu_AddTag(mm3, "fries");
    Menu_AddTag(mm3, "bbq");
    Restaurant_AddMenuItem(montana, mm3);

    printf("Finished creating data\n");

    // Attempt to remove a non-existent menu item (expected failure)
    int remove1 = Restaurant_RemoveMenuItem(floyds, 5);
    printf("Attempting to remove something not on the menu (0=Fail): %d\n\n", remove1);

    // Print menu items tagged with "chicken" across all restaurants
    printf("Printing all prices for a Chicken-festival:");
    for (int i = 0; i < 2; i++){
        Restaurant_PrintFestivalItems(restaurants[i], "chicken");
    }
    printf("\n");

    // Increase Floyd's discount
    Restaurant_AdjustDiscount(floyds, 0.5);

    // Remove a valid menu item from Floyd's
    int remove2 = Restaurant_RemoveMenuItem(floyds, 3);
    printf("Attempting to remove Hamburger Platter from Floyd's (0=Fail): %d\n\n", remove2);

    // Print menu items tagged with "lettuce"
    printf("Printing all prices for a Salad-festival:");
    for (int i = 0; i < 2; i++){
        Restaurant_PrintFestivalItems(restaurants[i], "lettuce");
    }
    printf("\n");

    // Print full menus with discounts applied during a salad festival
    printf("Printing all items during a Salad-festival:");
    for (int i = 0; i < 2; i++){
        Restaurant_PrintMenuWithDiscount(restaurants[i], "salad");
    }

    // Clean up all dynamically allocated memory
    Restaurant_Destruct(floyds);
    Restaurant_Destruct(montana);

    return EXIT_SUCCESS;
}
