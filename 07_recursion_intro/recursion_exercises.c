#include <stdio.h>
#include <stdlib.h>

/* Utility function to print an integer array */
void printArr(int arr[], int size){
    for (int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/* ===== Exercise 1 =====
 * Recursively finds the first occurrence of two adjacent letters in a string.
 * Letters are case-insensitive. Returns a pointer into the original string,
 * or NULL if no such pair exists.
 */
char *adjacentLetters(char *str){
    if (*str == '\0' || *(str + 1) == '\0'){
        return NULL;
    }

    char current = *str;
    char next = *(str + 1);

    if (current >= 'A' && current <= 'Z'){
        current += 32;
    }
    if (next >= 'A' && next <= 'Z'){
        next += 32;
    }

    if ((current >= 'a' && current <= 'z') &&
        (next >= 'a' && next <= 'z')){
        return str;
    }

    // Recurse on the next character
    return adjacentLetters(str + 1);
}

/* ===== Exercise 2 =====
 * Recursive helper that processes each row of a 2D array.
 * Computes (greatest * lowest) - middle for each row.
 */
void compress2DRec(int **arr2d, int row, int numRows, int *out){
    if (row == numRows){
        return;
    }

    int a = arr2d[row][0];
    int b = arr2d[row][1];
    int c = arr2d[row][2];

    int greatest = a;
    if (b > greatest) greatest = b;
    if (c > greatest) greatest = c;

    int lowest = a;
    if (b < lowest) lowest = b;
    if (c < lowest) lowest = c;

    int middle;
    if (a != greatest && a != lowest) middle = a;
    else if (b != greatest && b != lowest) middle = b;
    else middle = c;

    out[row] = (greatest * lowest) - middle;

    compress2DRec(arr2d, row + 1, numRows, out);
}

/* Allocates and returns a compressed 1D array derived from a 2D array */
int *compress2D(int **arr2d, int numRows){
    int *out = malloc(sizeof(int) * numRows);
    if (out == NULL){
        return NULL;
    }
    compress2DRec(arr2d, 0, numRows, out);
    return out;
}

/* ===== Exercise 3 =====
 * Recursive insertion sort.
 * mode = 0 → ascending
 * mode = 1 → descending
 */
void insertionSort(int *arr, int size, int sorted, int mode){
    if (sorted == size){
        return;
    }

    int current = arr[sorted];
    int check = sorted - 1;

    if (mode == 0){
        while (check >= 0 && arr[check] > current){
            arr[check + 1] = arr[check];
            check--;
        }
    } else {
        while (check >= 0 && arr[check] < current){
            arr[check + 1] = arr[check];
            check--;
        }
    }

    arr[check + 1] = current;
    insertionSort(arr, size, sorted + 1, mode);
}

int main(int argc, char **argv){

    /* Test adjacentLetters */
    char *string = "A65d46xCy11";
    char *result1 = adjacentLetters(string);
    if (result1 == NULL){
        printf("There are no adjacent letters.\n");
    } else {
        printf("Adjacent letters found: %c%c\n", *result1, *(result1 + 1));
    }

    char *string2 = "4567";
    char *result2 = adjacentLetters(string2);
    if (result2 == NULL){
        printf("There are no adjacent letters.\n");
    }

    /* Test compress2D */
    int data[2][3] = {
        {5, 8, 11},
        {4, 1, 12}
    };

    int *arr[2];
    for (int i = 0; i < 2; i++){
        arr[i] = data[i];
    }

    int *result3 = compress2D(arr, 2);
    printf("\nCompressed Array: [ ");
    for (int i = 0; i < 2; i++){
        printf("%d ", result3[i]);
    }
    printf("]\n\n");
    free(result3);

    /* Test insertionSort */
    int testArr[] = {7, 4, 11, 5, 6, 10};

    insertionSort(testArr, 6, 1, 0);
    printf("Ascending: ");
    printArr(testArr, 6);

    insertionSort(testArr, 6, 1, 1);
    printf("Descending: ");
    printArr(testArr, 6);

    return 0;
}
