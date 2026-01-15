#include <stdio.h>
#include <stdlib.h>

int strlen(char * msg){
    int len = 0;

    while(*msg != '\0'){
        len++;
        msg++;
    }

    return len;
}