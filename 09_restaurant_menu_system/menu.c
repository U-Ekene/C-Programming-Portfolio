#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"

/* Allocate and initialize a Menu item */
Menu * Menu_Construct(int idIn, const char *itemNameIn, float priceIn){
    Menu *m = malloc(sizeof(Menu));
    if(m == NULL){
        return NULL;
    }

    m->id = idIn;
    m->numTags = 0;
    m->price = priceIn;

    for (int i = 0; i < 5; i++) {
        m->tags[i] = NULL;
    }

    m->itemName = strdup(itemNameIn);
    if (m->itemName == NULL){
        free(m);
        return NULL;
    }

    return m;
}

/* Print a menu item and its tags */
void Menu_PrintItems(Menu *m){
    if(m == NULL){
        printf("No Items\n");
        return;
    }

    printf("%d. %s, %f\n\t", m->id, m->itemName, m->price);

    if(m->numTags == 0){
        printf("No tags\n");
    }

    for(int i = 0; i < m->numTags; i++){
        printf("%s ", m->tags[i]);
    }
    printf("\n");
}

/* Add a tag to a menu item (max 5) */
int Menu_AddTag(Menu *m, const char *tag){
    if(m->numTags == 5){
        printf("No space for tag");
        return 0;
    }

    m->tags[m->numTags] = strdup(tag);
    if(m->tags[m->numTags] == NULL){
        return 0;
    }

    m->numTags++;
    return 1;
}

/* Free all memory owned by a Menu item */
void Menu_Destruct(Menu *m){
    free(m->itemName);

    for (int i = 0; i < m->numTags; i++){
        free(m->tags[i]);
    }

    free(m);
}
