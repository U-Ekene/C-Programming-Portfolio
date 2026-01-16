#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Splits a string into tokens using a single-character delimiter.
 * Returns a NULL-terminated array of pointers to tokens within the original string.
 * The returned array must be freed by the caller, but not the tokens themselves.
 */
char **delimit(char * str, char delimiter){
    char **out = malloc(12 * sizeof(char *));
    if(out == NULL){
        return NULL;
    }

    int index = 0;

    /* Build delimiter string for strtok */
    char delim[2];
    delim[0] = delimiter;
    delim[1] = '\0';

    /* Tokenize the string */
    char *delimited = strtok(str, delim);
    while(delimited != NULL && index < 12){
        out[index++] = delimited;
        delimited = strtok(NULL, delim);
    }

    out[index] = NULL;
    return out;
}

/*
 * Reads a census CSV file and returns the population of a given region.
 * Filters rows based on specific category codes in the dataset.
 * Returns -1 if the region is not found or an error occurs.
 */
int getPopulation(char *file, char *region){
    FILE *fptr = fopen(file, "r");
    if (fptr == NULL){
        printf("Issue when trying to open file\n");
        return -1;
    }

    char thisline[1024];

    while(fgets(thisline, sizeof(thisline), fptr) != NULL){
        char **data = delimit(thisline, ',');

        if(strcmp(region, data[4]) == 0 &&
           atoi(data[6]) == 1 &&
           atoi(data[8]) == 1){
            int population = atoi(data[10]);
            free(data);
            fclose(fptr);
            return population;
        }
        free(data);
    }

    fclose(fptr);
    return -1;
}

/*
 * Finds the region with the highest percentage value for a given census category.
 * Returns a dynamically allocated string containing the region name.
 * The caller is responsible for freeing the returned string.
 */
char *highestPercentage(char *file){
    FILE *fptr = fopen(file, "r");
    if (fptr == NULL){
        printf("Issue when trying to open file\n");
        return NULL;
    }

    int percentage = 0;
    char *out = NULL;
    char thisline[1024];

    while(fgets(thisline, sizeof(thisline), fptr) != NULL){
        char **data = delimit(thisline, ',');

        if(atoi(data[6]) == 1 && atoi(data[8]) == 58){
            int value = atoi(data[10]);
            if(value > percentage){
                percentage = value;
                free(out);
                out = malloc(strlen(data[4]) + 1);
                if(out == NULL){
                    free(data);
                    fclose(fptr);
                    return NULL;
                }
                strcpy(out, data[4]);
            }
        }
        free(data);
    }

    fclose(fptr);
    return out;
}

/*
 * Extracts employment insurance values from the census file.
 * Returns a dynamically allocated array of floats.
 * The caller is responsible for freeing the array.
 */
float *employmentInsurance(char *file){
    FILE *fptr = fopen(file, "r");
    if (fptr == NULL){
        printf("Issue when trying to open file\n");
        return NULL;
    }

    char thisline[1024];
    float *out = malloc(sizeof(float) * 13);
    if (out == NULL){
        fclose(fptr);
        return NULL;
    }

    int index = 0;

    while(fgets(thisline, sizeof(thisline), fptr) != NULL){
        char **data = delimit(thisline, ',');

        if(atoi(data[6]) == 10 && atoi(data[8]) == 115){
            out[index++] = atof(data[10]);
        }
        free(data);
    }

    fclose(fptr);
    return out;
}

/*
 * Returns a list of regions where the number of French speakers
 * exceeds the given threshold.
 * Returns NULL if no regions meet the criteria.
 */
char **speaksFrench(char *file, int checkFrench){
    FILE *fptr = fopen(file, "r");
    if (fptr == NULL){
        printf("Issue when trying to open file\n");
        return NULL;
    }

    char thisline[1024];
    int count = 0;
    char **out = malloc(sizeof(char *) * 13);
    if (out == NULL){
        fclose(fptr);
        return NULL;
    }

    while(fgets(thisline, sizeof(thisline), fptr) != NULL){
        char **data = delimit(thisline, ',');

        if(atoi(data[8]) == 195 && atoi(data[6]) == 4){
            if(atoi(data[10]) > checkFrench){
                out[count] = malloc(strlen(data[4]) + 1);
                strcpy(out[count], data[4]);
                count++;
            }
        }
        free(data);
    }

    if(count == 0){
        free(out);
        fclose(fptr);
        return NULL;
    }

    out[count] = NULL;
    fclose(fptr);
    return out;
}

/*
 * Counts the number of non-Canadian residents in the dataset
 * based on specific category codes.
 */
int nonCanadian(char * file){
    FILE *fptr = fopen(file, "r");
    if (fptr == NULL){
        printf("Issue when trying to open file\n");
        return -1;
    }

    int count = 0;
    char thisline[1024];

    while(fgets(thisline, sizeof(thisline), fptr) != NULL){
        char **data = delimit(thisline, ',');

        if((atoi(data[6]) == 11 || atoi(data[6]) == 12) &&
            atoi(data[8]) == 289){
            count += atoi(data[10]);
        }
        free(data);
    }

    fclose(fptr);
    return count;
}

/*
 * Determines which region has the highest number of people
 * aged 45+ who are willing to work.
 * Returns the region name as a dynamically allocated string.
 */
char *over45ToWork(char *file){
    FILE *fptr = fopen(file, "r");
    if(fptr == NULL){
        printf("Issue with opening the file\n");
        return NULL;
    }

    char *out = NULL;
    int highest = -1;
    int current = 0;
    char thisline[1024];

    while(fgets(thisline, sizeof(thisline), fptr) != NULL){
        char **data = delimit(thisline, ',');

        if(atoi(data[8]) == 926 || atoi(data[8]) == 927){
            if(atoi(data[6]) == 1){
                current += atoi(data[10]);

                if(current > highest){
                    highest = current;
                    free(out);
                    out = malloc(strlen(data[4]) + 1);
                    strcpy(out, data[4]);
                }

                if(atoi(data[8]) == 927){
                    current = 0;
                }
            }
        }
        free(data);
    }

    fclose(fptr);
    return out;
}
