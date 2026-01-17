#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "flower.h"

/* Struct representing a doubly linked list of Flower nodes */
typedef struct{
    Flower *head;
} LinkedList;

/* 
* Functions for managing a linked list of flowers, including creation,
* insertion, removal, traversal, and lifecycle operations 
*/ 
Flower * Flower_Construct(int idIn, int monthsIn, char *flowertypeIn);
LinkedList * LinkedList_Construct();
void Flower_Destruct(Flower *flower);
void LinkedList_Destruct(LinkedList *list);
void Print_Flower(Flower *flower);
void Print_List(LinkedList *list);
int Flower_InsertFlower(Flower *flower, LinkedList *list);
int Flower_RemoveFlower(int removeId, LinkedList *list);
void Flower_DetachFlower(Flower *flower, LinkedList *list);
void Flower_Transplant(LinkedList *list, int fromId, int toId);
void Flower_Issue(LinkedList *list, int id, int extraMonths);
void Flower_Complete(LinkedList *list);

#endif
