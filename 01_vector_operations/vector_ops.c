#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float magnitude(float * vec, int size){
    float sum = 0;
    
    for(int i = 0; i < size; i++){
        float square = (*(vec + i)) * (*(vec + i));
        sum = sum + square;
    }
    return sqrt(sum);
}

void unit(float * vec, int size, float * unitVector){
    float unit = 0;
    float val = 0;

    for(int i = 0; i < size; i++){
       val = *(vec + i);
       unit = val/(magnitude(vec, size));
       *(unitVector + i) = unit;
    }
}


void add(float * vec1, float * vec2, int size, float * sol){
    float val1 = 0;
    float val2 = 0;
    float sum = 0;

    for(int i = 0; i < size; i++){
        val1 = *(vec1 + i);
        val2 = *(vec2 + i);
        sum = val1 + val2;
        *(sol + i) = sum;
    }
}

void scale(float * vec, int size, float scalar, float * sol){
    float val = 0;
    float scale = 0;

    for(int i = 0; i <size; i++){
        val = *(vec + i);
        scale = scalar * val;
        *(sol + i) = scale;
    }
}

float dot(float * vec1, float * vec2, int size){
    float mult = 0;
    float val1 = 0;
    float val2 = 0;
    float sum = 0;

    for(int i = 0; i<size; i++){
        val1 = *(vec1 + i);
        val2 = *(vec2 + i);
        mult = val1 * val2;
        sum = sum + mult;
    }
    return sum;
}

void project(float * vec1, float * vec2, int size, float * sol){
    float project = 0;

    for(int i = 0; i<size; i++){
        float dotS = dot(vec1, vec2, 3); 
        float magS = magnitude(vec1, 3);
        project = dotS/(magS * magS);
        *(sol + i) = project * (*(vec1 + i));
    }
}


int main(char ** argv, int argc){
    void printArray(float *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%f ", *(arr + i));  
    }
    printf("\n");
    }

    float arr1[] = {1,2,3};
    float arr2[] = {4,5,6};

    //Test1
    printf ("Magnitude is: %f\n", magnitude(arr1, 3));
    printf ("Magnitude is: %f\n", magnitude(arr2, 3));
    printf("\n");

    //Test2
    float unitVec1[3];
    unit(arr1, 3, unitVec1);
    printf("Unit Vector is: ");
    printArray(unitVec1, 3);

    float unitVec2[3];
    unit(arr2, 3, unitVec2);
    printf("Unit Vector is: "); 
    printArray(unitVec2, 3);
    printf("\n");

    //Test3
    float sol1[3];
    add(arr1, arr2, 3, sol1);
    printf("Sum is: "); 
    printArray(sol1, 3);
    printf("\n");

    //Test4
    float sol2[3];
    scale(arr1, 3, 4, sol2);
    printf("Scale is: ");
    printArray(sol2, 3);
    printf("\n");

    //Test5
    printf("dot is: %f\n", dot(arr1, arr2, 3));

    //Test6
    float sol3[3];
    project(arr1, arr2, 3, sol3);
    printf("Projection is: ");
    printArray(sol3, 3);
    
    return EXIT_SUCCESS;
}