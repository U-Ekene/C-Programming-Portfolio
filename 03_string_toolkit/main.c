#include <stdio.h>
#include <stdlib.h>

char *upper(char * msg);
char *lower(char * msg);
int vowels(char * msg);
int countChar(char * msg, char search);
char *substringMatch(char * msg, char * submsg);
char *delimit(char * msg, char delim);
char *substringDelete(char * msg, char * submsg);
int flow(char * msg);

int main(int argc, char ** argv){

    char * test1 = "This is a tesT";
    char * test2 = "Kanye eaTS some eggs";

    printf("Test 1: %s\n", test1);
    printf("Test 2: %s\n\n", test2);

    char * uppertest1 = upper(test1);
    char * uppertest2 = upper(test2);

    if(uppertest1 == NULL){
        return EXIT_FAILURE;
    }
    if(uppertest2 == NULL){
        free(uppertest1);
        return EXIT_FAILURE;
    }

    printf("Uppercase: %s\n", uppertest1);
    printf("Uppercase: %s\n\n", uppertest2);
    free(uppertest1);
    free(uppertest2);

    char * lowertest1 = lower(test1);
    char * lowertest2 = lower(test2);

    if(lowertest1 == NULL){
        return EXIT_FAILURE;
    }
    if(lowertest2 == NULL){
        free(lowertest1);
        return EXIT_FAILURE;
    }

    printf("Lowercase: %s\n", lowertest1);
    printf("Lowercase: %s\n\n", lowertest2);
    free(lowertest1);
    free(lowertest2);

    int voweltest1 = vowels(test1);
    int voweltest2 = vowels(test2);
    printf("Num Vowels 1: %d\n", voweltest1);
    printf("Num Vowels 2: %d\n\n", voweltest2);

    int countChartest1 = countChar(test1, 'f');
    int countChartest2 = countChar(test2, 'e');
    printf("Num char 1: %d\n", countChartest1);
    printf("Num char 2: %d\n\n", countChartest2);

    char * match1 = "est";
    char * match2 = "bead";
    char * substringMatchtest1 = substringMatch(test1, match1);
    char * substringMatchtest2 = substringMatch(test2, match2);

    printf("Check sub: %s\n", substringMatchtest1 ? substringMatchtest1 : "NULL");
    printf("Check sub: %s\n\n", substringMatchtest2 ? substringMatchtest2 : "NULL");

    char * delimittest1 = delimit(test1, 'i');
    char * delimittest2 = delimit(test2, 'g');

    if(delimittest1 == NULL){
        return EXIT_FAILURE;
    }
    if(delimittest2 == NULL){
        free(delimittest1);
        return EXIT_FAILURE;
    }

    printf("Delimited: %s\n", delimittest1);
    printf("Delimited: %s\n\n", delimittest2);
    free(delimittest1);
    free(delimittest2);

    char * deletetest1 = substringDelete(test1, "is");
    char * deletetest2 = substringDelete(test2, "gg");

    if(deletetest1 == NULL){
        return EXIT_FAILURE;
    }
    if(deletetest2 == NULL){
        free(deletetest1);
        return EXIT_FAILURE;
    }

    printf("Deleted substring: %s\n", deletetest1);
    printf("Delete substring: %s\n\n", deletetest2);
    free(deletetest1);
    free(deletetest2);

    int flowtest1 = flow(test1);
    int flowtest2 = flow(test2);
    printf("Flow?: %d\n", flowtest1);
    printf("Flow?: %d\n\n", flowtest2);

    return EXIT_SUCCESS;
}
