#ifndef MENU_H
#define MENU_H

/* Struct that represents a single menu item */
typedef struct{
    int id;
    char *itemName;
    float price;
    int numTags;
    char *tags[5];
} Menu;

/* Functions for managing the lifecycle and behavior of Menu objects */
Menu * Menu_Construct(int idIn, const char *itemNameIn, float priceIn);
void Menu_PrintItems(Menu *m);
int Menu_AddTag(Menu *m, const char *tag);
void Menu_Destruct(Menu *m);

#endif