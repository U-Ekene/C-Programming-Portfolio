#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "restaurant.h"
#include "menu.h"

/* Allocate and initialize a Restaurant */
Restaurant * Restaurant_Construct(const char *nameIn, float discountIn){
    Restaurant *r = malloc(sizeof(Restaurant));
    if(r == NULL){
        return NULL;
    }
    
    r->name = strdup(nameIn);
    if (r->name == NULL){ 
        free(r); 
        return NULL; 
    }

    r->discount = discountIn;
    r->numItems = 0;

    for (int i = 0; i < 20; i++) {
        r->menu[i] = NULL;  
    }

    return r;
}

/* Add a menu item to the restaurant (max 20 items) */
int Restaurant_AddMenuItem(Restaurant *r, Menu *m){
    if(r->numItems >= 20){
        return 0;
    }

    r->menu[r->numItems] = m;
    r->numItems++;

    return 1;
}

/* Print the restaurant name and all menu items */
void Restaurant_PrintMenu(Restaurant *r){
    if(r == NULL){
        printf("No Restaurant");
        return;
    }

    printf("%s\n", r->name);
    
    if(r->numItems == 0){
        printf("No Menu Items\n");
        return;
    }

    for(int i = 0; i < r->numItems; i++){
        Menu_PrintItems(r->menu[i]);  
        printf("\n");
    }
} 

/* Remove a menu item by ID */
int Restaurant_RemoveMenuItem(Restaurant *r, int remove){
    int found = 0;
    int removeIndex = -1;

    for(int i = 0; i < r->numItems; i++){
        if(r->menu[i]->id == remove){
            found = 1;
            removeIndex = i;
            break;
        }
    }

    if(found == 0){
        return 0;
    }

    Menu_Destruct(r->menu[removeIndex]);
    
    for(int j = removeIndex; j < r->numItems - 1; j++){
        r->menu[j] = r->menu[j + 1];
    }

    r->menu[r->numItems - 1] = NULL;
    r->numItems--;
    return 1;
}

/* Print menu items that match a festival tag with discount applied */
void Restaurant_PrintFestivalItems(Restaurant *r, char *festival){
    if(r == NULL){
        printf("No Restaurant");
        return;
    }

    printf("\n%s\n", r->name); 

    for(int i = 0; i < r->numItems; i++){
        int hasTag = 0;

        for(int j = 0; j < r->menu[i]->numTags; j++){
            if(strcmp(r->menu[i]->tags[j], festival) == 0){
                hasTag = 1;
                break;
            }
        }

        if(hasTag){
            float newPrice = r->menu[i]->price * (1 - r->discount);

            printf("%d. %s, %f\n\t",
                   r->menu[i]->id,
                   r->menu[i]->itemName,
                   newPrice);

            if(r->menu[i]->numTags == 0){
                printf("No tags\n");
            }
            for(int k = 0; k < r->menu[i]->numTags; k++){
                printf("%s ", r->menu[i]->tags[k]);
            }
            printf("\n");
        }
    }
}

/* Update the restaurant discount */
void Restaurant_AdjustDiscount(Restaurant *r, float newVal){
    if (r == NULL) {
        return;
    }

    r->discount = newVal;
    printf("Changed discount for %s to %f\n", r->name, r->discount);
}

/* Print full menu, applying discount only to festival-tagged items */
void Restaurant_PrintMenuWithDiscount(Restaurant *r, char *festival){
    if(r == NULL){
        printf("No Restaurant");
        return;
    }

    printf("\n%s\n", r->name); 

    for(int i = 0; i < r->numItems; i++){
        float price = r->menu[i]->price;
        int hasTag = 0;

        for (int j = 0; j < r->menu[i]->numTags; j++){
            if (strcmp(r->menu[i]->tags[j], festival) == 0){
                hasTag = 1;
                break;
            }
        }

        if(hasTag){
            price = r->menu[i]->price * (1 - r->discount);
        }

        printf("%d. %s, %f\n\t",
               r->menu[i]->id,
               r->menu[i]->itemName,
               price);

        if (r->menu[i]->numTags == 0){
            printf("No tags");
        }
        else{
            for (int k = 0; k < r->menu[i]->numTags; k++){
                printf("%s ", r->menu[i]->tags[k]);
            }
        }
        printf("\n");
    }
}

/* Free all memory owned by the restaurant */
void Restaurant_Destruct(Restaurant *r){
    free(r->name);

    for (int i = 0; i < r->numItems; i++) {
        Menu_Destruct(r->menu[i]);
    }

    free(r);
}
