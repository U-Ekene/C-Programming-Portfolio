/*
 * census_query_filter.c
 *
 * Reads queries from Queries.csv and applies each query to Census.csv.
 * For every query, a filtered output CSV file is generated based on
 * region, age group, characteristics, and optional numeric conditions.
 *
 * Demonstrates file processing, dynamic memory management,
 * string tokenization, and conditional filtering in C.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Tokenizes a string using a delimiter and returns a NULL-terminated array */
char **delimit(char *str, char delimiter) {
    char **out = malloc(12 * sizeof(char *));
    if (out == NULL) return NULL;

    char *temp = malloc(strlen(str) + 1);
    if (temp == NULL) {
        free(out);
        return NULL;
    }
    strcpy(temp, str);

    int index = 0;
    char delim[2] = { delimiter, '\0' };
    char *delimited = strtok(temp, delim);

    while (delimited != NULL && index < 12) {
        out[index] = malloc(strlen(delimited) + 1);
        if (out[index] == NULL) {
            for (int j = 0; j < index; j++) free(out[j]);
            free(out);
            free(temp);
            return NULL;
        }
        strcpy(out[index], delimited);
        index++;
        delimited = strtok(NULL, delim);
    }

    out[index] = NULL;
    free(temp);
    return out;
}

/* Frees a NULL-terminated array of strings */
void freeArr(char **arr) {
    if (arr == NULL) return;
    for (int i = 0; arr[i] != NULL; i++) {
        free(arr[i]);
    }
    free(arr);
}

/* Returns true if list is "N/A" or contains the given value */
int isNAorInlist(char **list, char *val) {
    if (list == NULL || list[0] == NULL || strcmp(list[0], "N/A") == 0) {
        return 1;
    }
    for (int i = 0; list[i] != NULL; i++) {
        if (strcmp(list[i], val) == 0) {
            return 1;
        }
    }
    return 0;
}

int main(int argc, char **argv) {

    /* Open the query file */
    FILE *queries = fopen("Queries.csv", "r");
    if (queries == NULL) {
        printf("Issue when trying to open Queries.csv\n");
        return EXIT_FAILURE;
    }

    char thislineCen[1024];
    char thislineQry[1024];

    /* Process each query */
    while (fgets(thislineQry, sizeof(thislineQry), queries) != NULL) {

        /* Open census file for each query */
        FILE *census = fopen("Census.csv", "r");
        if (census == NULL) {
            printf("Issue when trying to open Census.csv\n");
            return EXIT_FAILURE;
        }

        /* Parse query fields */
        char **qry = delimit(thislineQry, ',');
        printf("Fetching query: %s\n", qry[0]);

        /* Create output file named by the query */
        FILE *output = fopen(qry[0], "w");
        if (output == NULL) {
            printf("Issue when trying to open output file\n");
            return EXIT_FAILURE;
        }

        char **reglist  = delimit(qry[1], '$');
        char **agelist  = delimit(qry[2], ' ');
        char **charlist = delimit(qry[3], ' ');

        /* Handle special-case region mapping */
        for (int i = 0; reglist[i] != NULL; i++) {
            char *fullstring =
                "Combined census subdivisions with 2021 population under 10000 New Brunswick";
            if (strcmp(reglist[i], "Combined") == 0) {
                free(reglist[i]);
                reglist[i] = malloc(strlen(fullstring) + 1);
                strcpy(reglist[i], fullstring);
            }
        }

        /* Parse optional numeric condition */
        char cond = 0;
        int doCond = 0;
        int checkVal = 0;

        if (qry[4] && strcmp(qry[4], "N/A") != 0) {
            if (sscanf(qry[4], " %c%d", &cond, &checkVal) == 2) {
                doCond = 1;
            }
        }

        /* Apply filters to each census row */
        while (fgets(thislineCen, sizeof(thislineCen), census) != NULL) {
            char **censline = delimit(thislineCen, ',');

            if (isNAorInlist(reglist, censline[4]) &&
                isNAorInlist(agelist, censline[6]) &&
                isNAorInlist(charlist, censline[8])) {

                int filtered = 1;

                if (doCond) {
                    int censusVal = atoi(censline[10]);
                    if (cond == '=' && censusVal != checkVal) filtered = 0;
                    if (cond == '>' && censusVal <= checkVal) filtered = 0;
                    if (cond == '<' && censusVal >= checkVal) filtered = 0;
                }

                if (filtered) {
                    fprintf(output, "%s", thislineCen);
                }
            }
            freeArr(censline);
        }

        /* Cleanup for this query */
        freeArr(charlist);
        freeArr(agelist);
        freeArr(reglist);
        freeArr(qry);
        fclose(output);
        fclose(census);
    }

    fclose(queries);
    printf("Done\n");
    return EXIT_SUCCESS;
}
