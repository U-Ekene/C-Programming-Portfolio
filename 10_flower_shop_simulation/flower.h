#ifndef FLOWER_H
#define FLOWER_H

/* Struct representing a flower node in a doubly linked list */
typedef struct Flower{
    struct Flower * next;
    struct Flower * prev;
    int id;
    int months;
    int originalMonths;
    char *flowertype;
    
}Flower;

#endif