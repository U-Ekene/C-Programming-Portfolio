#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"   

// Removes trailing newline characters from input lines
void trim_newline(char *s) {
    s[strcspn(s, "\r\n")] = '\0';
}

int main(int argc, char ** argv) {

    // Open request file containing flower shop commands
    FILE *input = fopen("Requests.txt", "r");
    if (input == NULL) {
        printf("Error: could not open Requests.txt\n");
        return EXIT_FAILURE;
    }

    // Create flower list and initialize starting ID
    LinkedList *list = LinkedList_Construct();
    int nextId = 8000;

    char line[256];

    // Process commands line-by-line
    while (fgets(line, sizeof(line), input) != NULL) {
        trim_newline(line);

        // ===================== PLANT =====================
        // Adds a new flower to the list
        if (strcmp(line, "PLANT") == 0) {
            printf("\nPLANT:\n");

            if (fgets(line, sizeof(line), input) != NULL){
                trim_newline(line);

                int months = atoi(strtok(line, ", "));
                char *name = strtok(NULL, ", ");

                Flower *f = Flower_Construct(nextId, months, name);
                nextId++;

                if (f == NULL) {
                    printf("Error: Failed to create plant\n");
                    continue;
                }

                Flower_InsertFlower(f, list);
                Print_List(list);
            }
        }

        // ===================== ISSUE =====================
        // Adds extra growing months to an existing flower
        else if (strcmp(line, "ISSUE") == 0) {
            printf("\nISSUE:\n");

            if (fgets(line, sizeof(line), input) != NULL){
                trim_newline(line);

                int id = atoi(strtok(line, ", "));
                int extraMonths = atoi(strtok(NULL, ", "));

                printf("Handling issue: ID %d +%d months\n", id, extraMonths);

                Flower_Issue(list, id, extraMonths);
                Print_List(list);
            }
        }

        // ===================== TRANSPLANT =====================
        // Transfers growth from one flower to another
        else if (strcmp(line, "TRANSPLANT") == 0) {
            printf("\nTRANSPLANT:\n");

            if (fgets(line, sizeof(line), input) != NULL){
                trim_newline(line);

                int fromId = atoi(strtok(line, ", "));
                int toId = atoi(strtok(NULL, ", "));

                printf("Transplanting: %d to %d\n", fromId, toId);

                Flower_Transplant(list, fromId, toId);
                Print_List(list);
            }
        }

        // ===================== COMPLETE =====================
        // Advances time and resets flowers that finish growing
        else if (strcmp(line, "COMPLETE") == 0) {

            if (fgets(line, sizeof(line), input) != NULL){
                trim_newline(line);

                printf("\n%s COMPLETED:\n", line);

                Flower_Complete(list);
                Print_List(list);
            }
        }

        // ===================== UNKNOWN COMMAND =====================
        else {
            printf("Unknown command: %s\n", line);
        }
    }

    // Cleanup
    fclose(input);
    LinkedList_Destruct(list);

    return EXIT_SUCCESS;
}
