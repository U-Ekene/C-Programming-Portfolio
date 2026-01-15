#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv){
    char * input = argv[1];
    char * temp = input;
    char copy[50];
    char * copyptr = copy;
    

    while(*temp != '\0'){
        *copyptr = *temp;
        temp++;
        copyptr++;
    }
    *copyptr = '\0';

    //Print the string if all the characters were uppercase
    copyptr = copy;
    while(*copyptr != '\0'){
        if(*copyptr >= 'a' && *copyptr <= 'z'){
            *copyptr -= 32;
        }
        copyptr++;
    }
    printf("Uppercase: %s\n\n", copy);

    //////reset
    temp = input;
    copyptr = copy;
    while(*temp != '\0'){
        *copyptr = *temp;
        temp++;
        copyptr++;
    }
    *copyptr = '\0';
    ///////////

    //Print the string if all the characters were lowercase
    copyptr = copy;
    while(*copyptr != '\0'){
        if(*copyptr >= 'A' && *copyptr <= 'Z'){
            *copyptr += 32;
        }
        copyptr++;
    }
    printf("Lowercase: %s\n\n", copy);

    //////reset
    temp = input;
    copyptr = copy;
    while(*temp != '\0'){
        *copyptr = *temp;
        temp++;
        copyptr++;
    }
    *copyptr = '\0';
    ///////////

    /*Print the number of vowels in the string 
    uppercase or lowercase and including 'Y'.*/
    copyptr = copy;
    int count = 0;
    while(*copyptr != '\0'){
        if (*copyptr == 'a' || *copyptr == 'e' || *copyptr == 'i' || *copyptr == 'o' || *copyptr == 'u' ||
    *copyptr == 'A' || *copyptr == 'E' || *copyptr == 'I' || *copyptr == 'O' || *copyptr == 'U' ||
    *copyptr == 'Y' || *copyptr == 'y') {
            count++;
            copyptr++;
        }
        else{
            count = count;
            copyptr++;
        }
    }
    printf("Num Vowels: %d\n\n", count);

    //////reset
    temp = input;
    copyptr = copy;
    while(*temp != '\0'){
        *copyptr = *temp;
        temp++;
        copyptr++;
    }
    *copyptr = '\0';
    ///////////

    /*Ask the user to input a single character and print the number of times that
    character appears in the given string.*/
    copyptr = copy;
    printf("Pleas input a character to count: ");
    char toCount;
    int charCount = 0;
    scanf(" %c", &toCount);

    while(*copyptr != '\0'){
        if(*copyptr == toCount){
            charCount++;
            copyptr++;
        }
        else{
            copyptr++;
        }
    }
    printf("Count: %d\n\n",charCount);

    //////reset
    temp = input;
    copyptr = copy;
    while(*temp != '\0'){
        *copyptr = *temp;
        temp++;
        copyptr++;
    }
    *copyptr = '\0';
    ///////////

    /*Ask the user to input a substring and print “TRUE” if the substring is in the string or
    “FALSE” if not.
    a. Note: You may assume that the substring will always be shorter than the
    original string.*/
    copyptr = copy;
    printf("Please input a substring to search for: ");
    char toSearch[50];
    scanf("%s", toSearch);

    char * ptr = NULL;
    char * substring = toSearch;

    while(*copyptr != '\0' && ptr == NULL){
        if(*copyptr == *substring){
            char * comp1 = copyptr;
            char * comp2 = substring;
            
            while(*comp1 == *comp2){
                comp1++;
                comp2++;
                if(*comp2 == '\0'){
                    ptr = copyptr;
                    break;
                }
            }
        }
        copyptr++;
    }
    if(ptr == NULL){
        printf("FALSE\n\n");
    }
    else{
        printf("TRUE\n\n");
    }

    //////reset
    temp = input;
    copyptr = copy;
    while(*temp != '\0'){
        *copyptr = *temp;
        temp++;
        copyptr++;
    }
    *copyptr = '\0';
    ///////////

    /*Ask the user to input a single character delimiter and 
    print each string tokenized using the delimiter.
    a. Note: You may need to scan a character in twice to get 
    rid of the extra new line character that was read in during step 3.*/
    copyptr = copy;
    printf("Please input a single character delimeter: ");
    char toDelimit;
    scanf(" %c", &toDelimit);

    while(*copyptr != '\0'){
        if(*copyptr != toDelimit){
            copyptr++;
        }
        else{
            *copyptr = '\n';
            copyptr++;
        }
    }
    printf("%s\n\n", copy);

    //////reset
    temp = input;
    copyptr = copy;
    while(*temp != '\0'){
        *copyptr = *temp;
        temp++;
        copyptr++;
    }
    *copyptr = '\0';
    ///////////

    /*Ask the user to input a substring and print the original string if 
    all instances of that substring were deleted.
    a. Note: You may assume that the substring will always be shorter than the
    original string */
    copyptr = copy;
    printf("Please input a substring to delete: ");
    char toDelete[50];
    scanf("%s", toDelete);

    char * sub = toDelete;
    char * remove;
    char * reset = sub;

    while(*copyptr != '\0'){
        if(*copyptr == *sub){
            char * comp1 = copyptr;
            char * comp2 = sub;
            remove = comp1;

            while(*comp1 == *comp2){
                comp1++;
                comp2++;  

                if(*comp2 == '\0'){
                    while(*sub != '\0'){
                        *remove = ' ';
                        remove++;
                        sub++;
                    }
                }
            }
            sub = reset;
        }
        copyptr++;
    }
    printf("%s\n\n", copy);

    //////reset
    temp = input;
    copyptr = copy;
    while(*temp != '\0'){
        *copyptr = *temp;
        temp++;
        copyptr++;
    }
    *copyptr = '\0';
    ///////////

    /*Print “FLOW” if the string has flow between all spaces and “NO FLOW” otherwise.
    a. A word flows into another word, if the last letter of one word matches the
    first letter of the next word (ignoring cases). You can treat any
    punctuation as though it is a normal letter. If no spaces appear, you can
    say the string has flow.*/
    copyptr = copy;
    char * checkptr = NULL;

    while(*copyptr != '\0'){
        if(*copyptr == ' '){
            char pre = *(copyptr - 1);
            char post = *(copyptr + 1);

            if(pre>='A' && pre<= 'Z'){
                pre += 32;
            }

            if(post>='A' && post<= 'Z'){
                post += 32;
            }

            if(pre == post){
                checkptr = copyptr;
            }
            else{
                checkptr = NULL;
                break;
            }
        }
        copyptr++;
    }
    if(checkptr == NULL){
        printf("NOT FLOW");
    }
    else{
        printf("FLOW");
    }
}