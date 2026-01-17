#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flower.h"
#include "linkedlist.h"

/*
 * Constructs and initializes a Flower object.
 * Each flower tracks growth time and is designed to live inside a linked list.
 */
Flower * Flower_Construct(int idIn, int monthsIn, char *flowertypeIn){
    Flower * flower = malloc(sizeof(Flower));
    if(flower == NULL){
        return NULL;
    }

    flower->id = idIn;
    flower->months = monthsIn;
    flower->originalMonths = monthsIn;
    flower->flowertype = strdup(flowertypeIn);
    flower->next = NULL;
    flower->prev = NULL;

    return flower;
}

/*
 * Creates an empty linked list to manage Flower objects.
 */
LinkedList * LinkedList_Construct(){
    LinkedList * list = malloc(sizeof(LinkedList));
    if(list == NULL){
        return NULL;
    }

    list->head = NULL;
    return list;
}

/*
 * Frees a single Flower and its dynamically allocated fields.
 */
void Flower_Destruct(Flower *flower){
    free(flower->flowertype);
    free(flower);
}

/*
 * Frees an entire linked list and all flowers contained within it.
 */
void LinkedList_Destruct(LinkedList *list){
    Flower *prev = NULL;
    Flower *curr = list->head;

    while(curr != NULL){
        if(prev != NULL){
            Flower_Destruct(prev);
        }
        prev = curr;
        curr = curr->next;
    }
    if(prev != NULL){
        Flower_Destruct(prev);
    }
    free(list);
}

/*
 * Prints a single flower’s information.
 */
void Print_Flower(Flower *flower){
    printf("ID: %d %s MONTHS UNTIL MATURITY: %d\n",
           flower->id, flower->flowertype, flower->months);
}

/*
 * Prints all flowers in the list in order.
 */
void Print_List(LinkedList *list){
    printf("Flower Shop:\n");
    Flower *curr = list->head;

    if (curr == NULL){
        printf("No flowers\n");
        return;
    }

    while (curr != NULL){
        printf("\t");
        Print_Flower(curr);
        curr = curr->next;
    }
}

/*
 * Inserts a flower into the list, keeping it sorted by months until maturity.
 */
int Flower_InsertFlower(Flower *flower, LinkedList *list){
    if(list->head == NULL){
        list->head = flower;
        return 1;
    }
    else if(list->head->months >= flower->months){
        Flower *oldHead = list->head;
        oldHead->prev = flower;
        flower->next = oldHead;
        list->head = flower;
        return 1;
    }
    else{
        Flower *curr = list->head;

        while(curr->next != NULL && curr->next->months <= flower->months){
            curr = curr->next;
        }

        flower->next = curr->next;
        flower->prev = curr;

        if (curr->next != NULL){
            curr->next->prev = flower;
        }
        curr->next = flower;
        return 1;
    }
}

/*
 * Removes a flower by ID and frees its memory.
 */
int Flower_RemoveFlower(int removeId, LinkedList *list){
    if(list->head == NULL){
        return 0;
    }

    if(list->head->id == removeId){
        Flower *oldHead = list->head;
        list->head = oldHead->next;
        if(list->head != NULL){
            list->head->prev = NULL;
        }
        Flower_Destruct(oldHead);
        return 1;
    }

    Flower *curr = list->head;
    while (curr != NULL && curr->id != removeId){
        curr = curr->next;
    }

    if (curr == NULL){
        return 0;
    }

    curr->prev->next = curr->next;
    if(curr->next != NULL){
        curr->next->prev = curr->prev;
    }

    Flower_Destruct(curr);
    return 1;
}

/*
 * Detaches a flower from the list without freeing it.
 * Used when repositioning flowers.
 */
void Flower_DetachFlower(Flower *flower, LinkedList *list){
    if (flower->prev != NULL){
        flower->prev->next = flower->next;
    }
    else{
        list->head = flower->next;
    }

    if (flower->next != NULL){
        flower->next->prev = flower->prev;
    }

    flower->prev = NULL;
    flower->next = NULL;
}

/*
 * Moves growth from one flowerbed to another if compatible.
 */
void Flower_Transplant(LinkedList *list, int fromId, int toId){
    Flower *curr = list->head;
    Flower *from = NULL;
    Flower *to = NULL;

    while (curr != NULL){
        if (curr->id == fromId) from = curr;
        else if (curr->id == toId) to = curr;
        curr = curr->next;
    }

    if (from == NULL || to == NULL){
        printf("Plant with ID was not found\n\n");
        return;
    }

    if (from->months != to->months || strcmp(from->flowertype, to->flowertype) != 0){
        printf("Error: flowerbeds do not match\n");
        return;
    }

    Flower_RemoveFlower(fromId, list);
    Flower_DetachFlower(to, list);
    to->months += 1;
    Flower_InsertFlower(to, list);
}

/*
 * Applies a delay to a flower and repositions it in the list.
 */
void Flower_Issue(LinkedList *list, int targetid, int extraMonths){
    Flower *curr = list->head;

    while (curr != NULL && curr->id != targetid){
        curr = curr->next;
    }

    if (curr == NULL){
        printf("Plant with ID was not found\n\n");
        return;
    }

    Flower_DetachFlower(curr, list);
    curr->months += extraMonths;
    Flower_InsertFlower(curr, list);
}

/*
 * Advances time by one month for all flowers,
 * resetting and repositioning those that complete their cycle.
 */
void Flower_Complete(LinkedList *list){
    Flower *curr = list->head;

    while (curr != NULL){
        Flower *next = curr->next;
        curr->months -= 1;

        if (curr->months == 0){
            curr->months = curr->originalMonths;
            Flower_DetachFlower(curr, list);
            Flower_InsertFlower(curr, list);
        }
        curr = next;
    }
}
