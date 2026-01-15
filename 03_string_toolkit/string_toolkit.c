#include <stdio.h>
#include <stdlib.h>

/* 
 * Custom string length function.
 * Counts the number of characters in a null-terminated string.
 * Implemented in helpers.c.
 */
int my_strlen(char * msg);

/*
 * Converts all lowercase letters in the string to uppercase.
 * Returns a newly allocated string that must be freed by the caller.
 */
char * upper(char * msg){
    char * copy;
    int length = my_strlen(msg);

    copy = malloc(sizeof(char) * (length + 1));
    if(copy == NULL){
        return NULL;
    }

    char * result = copy;

    while(*msg != '\0'){
        if(*msg >= 'a' && *msg <= 'z'){
            *copy = *msg - 32;
        }
        else{
            *copy = *msg;
        }
        msg++;
        copy++;
    }
    *copy = '\0';

    return result;
}

/*
 * Converts all uppercase letters in the string to lowercase.
 * Returns a newly allocated string that must be freed by the caller.
 */
char * lower(char * msg){
    char * copy;
    int length = my_strlen(msg);

    copy = malloc(sizeof(char) * (length + 1));
    if(copy == NULL){
        return NULL;
    }

    char * result = copy;

    while(*msg != '\0'){
        if(*msg >= 'A' && *msg <= 'Z'){
            *copy = *msg + 32;
        }
        else{
            *copy = *msg;
        }
        msg++;
        copy++;
    }
    *copy = '\0';

    return result;
}

/*
 * Counts the number of times a given character appears in the string.
 */
int countChar(char * msg, char search){
    int charCount = 0;

    while(*msg != '\0'){
        if(*msg == search){
            charCount++;
        }
        msg++;
    }
    return charCount;
}

/*
 * Counts the number of vowels in the string.
 * Vowels include both uppercase and lowercase letters and 'Y/y'.
 */
int vowels(char * msg){
    int count = 0;

    while(*msg != '\0'){
        if (*msg == 'a' || *msg == 'e' || *msg == 'i' || *msg == 'o' || *msg == 'u' ||
            *msg == 'A' || *msg == 'E' || *msg == 'I' || *msg == 'O' || *msg == 'U' ||
            *msg == 'Y' || *msg == 'y') {
            count++;
        }
        msg++;
    }
    return count;
}

/*
 * Searches for a substring within a string.
 * Returns a pointer to the first occurrence of the substring,
 * or NULL if the substring is not found.
 */
char * substringMatch(char * msg, char * submsg){
    char * ptr = NULL;
    char * temp = msg;

    while(*temp != '\0' && ptr == NULL){
        if(*temp == *submsg){
            char * comp1 = temp;
            char * comp2 = submsg;

            while(*comp1 == *comp2){
                comp1++;
                comp2++;

                if(*comp2 == '\0'){
                    ptr = temp;
                    break;
                }
                if(*comp1 == '\0'){
                    break;
                }
            }
        }
        temp++;
    }
    return ptr;
}

/*
 * Copies characters from the string up to the first occurrence
 * of the specified delimiter.
 * Returns a newly allocated string that must be freed by the caller.
 */
char * delimit(char * msg, char delim){
    char * copy;
    int length = my_strlen(msg);

    copy = malloc(sizeof(char) * (length + 1));
    if(copy == NULL){
        return NULL;
    }

    char * result = copy;

    while(*msg != '\0' && *msg != delim){
        *copy = *msg;
        copy++;
        msg++;
    }
    *copy = '\0';
    return result;
}

/*
 * Removes all occurrences of a substring from the string.
 * Returns a newly allocated string with the substring deleted.
 * The caller is responsible for freeing the returned string.
 */
char * substringDelete(char * msg, char * submsg){
    char * copy;
    int length = my_strlen(msg);

    copy = malloc(sizeof(char) * (length + 1));
    if(copy == NULL){
        return NULL;
    }

    char * result = copy;

    while(*msg != '\0'){
        char * comp1 = msg;
        char * comp2 = submsg;

        while(*comp1 == *comp2){
            comp1++;
            comp2++;
            if(*comp1 == '\0'){
                break;
            }
        }

        if(*comp2 == '\0'){
            msg = comp1;
        }
        else{
            *copy = *msg;
            copy++;
            msg++;
        }
    }
    *copy = '\0';
    return result;
}

/*
 * Checks whether the string has "flow".
 * Flow exists if, for every space, the character before the space
 * matches the character after the space (case-insensitive).
 * Returns 1 if flow exists, 0 otherwise.
 */
int flow(char * msg){
    int check = 0;

    while(*msg != '\0'){
        if(*msg == ' '){
            char pre = *(msg - 1);
            char post = *(msg + 1);

            if(pre >= 'A' && pre <= 'Z'){
                pre += 32;
            }

            if(post >= 'A' && post <= 'Z'){
                post += 32;
            }

            if(pre == post){
                check = 1;
            }
            else{
                check = 0;
                break;
            }
        }
        msg++;
    }
    return check;
}
