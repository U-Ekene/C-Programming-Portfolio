#include <stdio.h>
#include <stdlib.h>

char ** clearcut(char ** map, int sizeRow, int sizeCol, int cutRow, int cutCol);
int predictClearcut(char ** map, int sizeRow, int sizeCol, int cutRow, int cutCol);
int countTiles(char ** map, int sizeRow, int sizeCol, char tile);
int * countTilesRow(char ** map, int sizeRow, int sizeCol, char tile);
int floodRisk(char ** map, int sizeRow, int sizeCol);
char ** islands(char ** map, int sizeRow, int sizeCol);
char ** subMap(char ** map, int sizeRow, int sizeCol, int startRow, int startCol, int numRows, int numCols);
char ** tessellateMap(char ** map, int sizeRow, int sizeCol, int newRow, int newCol);

void printMap(char ** map, int row, int col){
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%c ", map[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char ** argv) {
    int row = 5;
    int col = 4;

    char test[5][4] = {
        {'P','R','R','W',},
        {'P','F','F','P',},
        {'R','F','W','F',},
        {'F','W','R','W',},
        {'P','R','W','W'}
    };

    char * map[5];
    for (int i = 0; i < row; i++) {
        map[i] = test[i];
    }

    printf("Original map:\n");
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%c ", map[i][j]);
        }
        printf("\n");
    }

    // clearcut tests
    char ** cut1 = clearcut(map, row, col, 3, 2);
    if(cut1 == NULL) return EXIT_FAILURE;

    printf("\nAfter clearcut (top-left 2x3 area cleared):\n");
    printMap(cut1, row, col);

    for (int i = 0; i < row; i++) free(cut1[i]);
    free(cut1);

    char ** cut2 = clearcut(map, row, col, -1, 3);
    if(cut2 == NULL) return EXIT_FAILURE;

    printf("\nAfter clearcut (row out of bounds):\n");
    printMap(cut2, row, col);

    for (int i = 0; i < row; i++) free(cut2[i]);
    free(cut2);

    // predict tests
    int predict1 = predictClearcut(map, row, col, 3, 2);
    printf("\nI predict in map (3,2): %d", predict1);

    int predict2 = predictClearcut(map, row, col, -1, 3);
    printf("\nI predict in map (row out of bounds): %d\n", predict2);

    // count tiles test
    int countTiles1 = countTiles(map, row, col, 'F');
    printf("\nThe number of F tiles in map is: %d", countTiles1);

    int countTiles2 = countTiles(map, row, col, 'W');
    printf("\nThe number of W tiles in map is: %d\n", countTiles2);

    // countTilesRow test
    int * countTilesRow1 = countTilesRow(map, row, col, 'R');
    if(countTilesRow1 == NULL) return EXIT_FAILURE;

    printf("\nThe number of R in each row of map is: ");
    for(int i = 0; i < row; i++){
        printf("%d,", countTilesRow1[i]);
    }
    free(countTilesRow1);

    int * countTilesRow2 = countTilesRow(map, row, col, 'P');
    if(countTilesRow2 == NULL) return EXIT_FAILURE;

    printf("\nThe number of P in each row of map is: ");
    for(int i = 0; i < row; i++){
        printf("%d,", countTilesRow2[i]);
    }
    printf("\n");
    free(countTilesRow2);

    // floodrisk test
    int floodRisk1 = floodRisk(map, row, col);
    printf("\nThe floodRisk of map is: %d\n", floodRisk1);

    char test2[5][4] = {
        {'P','R','R','W',},
        {'P','W','F','P',},
        {'W','F','W','F',},
        {'F','W','R','W',},
        {'P','R','W','W'}
    };

    char * map2[5];
    for (int i = 0; i < row; i++) {
        map2[i] = test2[i];
    }

    printf("\nfloodrisk map2:\n");
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%c ", map2[i][j]);
        }
        printf("\n");
    }

    int floodrisk2 = floodRisk(map2, row, col);
    printf("The floodrisk of map2 is: %d\n", floodrisk2);

    // islands test
    char ** islands1 = islands(map, row, col);
    if(islands1 == NULL) return EXIT_FAILURE;

    printf("\nThe islands in map 1:\n");
    for(int i = 0; islands1[i] != NULL; i++){
        printf("%c\n", *islands1[i]);
    }
    free(islands1);

    char ** islands2 = islands(map2, row, col);
    if(islands2 == NULL) return EXIT_FAILURE;

    printf("\nThe islands in map 2:\n");
    for(int i = 0; islands2[i] != NULL; i++){
        printf("%c\n", *islands2[i]);
    }
    free(islands2);

    // submap test
    char ** subMap1 = subMap(map, row, col, 0, 0, 2, 3);
    if(subMap1 == NULL) return EXIT_FAILURE;

    printf("\nSubmap of map (r2,c3) is: \n");
    for(int i =0; i < 2; i++){
        for(int j = 0; j<3;j++){
            printf("%c", subMap1[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < 2; i++) free(subMap1[i]);
    free(subMap1);

    char ** subMap2 = subMap(map, row, col, 3, 2, 2, 2);
    if(subMap2 == NULL) return EXIT_FAILURE;

    printf("\nSubmap of map(r2,c2) is: \n");
    for(int i =0; i < 2; i++){
        for(int j = 0; j<2;j++){
            printf("%c", subMap2[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < 2; i++) free(subMap2[i]);
    free(subMap2);

    char ** subMap3 = subMap(map, row, col, 0, 0, 8, 6);
    if(subMap3 == NULL){
        printf("\nSubmap of map (out of bounds) is: NULL");
    } else {
        return EXIT_FAILURE;
    }

    char ** subMap4 = subMap(map, row, col, 3, 2, 3, 4);
    if(subMap4 == NULL){
        printf("\nSubmap of map (out of bounds) is: NULL\n");
    } else {
        return EXIT_FAILURE;
    }

    // tessellate tests
    char ** tessellateMap1 = tessellateMap(map, row, col, 7, 10);
    if(tessellateMap1 == NULL) return EXIT_FAILURE;

    printf("\n7x10 Tessellated map is: \n");
    for(int i =0; i < 7; i++){
        for(int j = 0; j < 10;j++){
            printf("%c", tessellateMap1[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < 7; i++) free(tessellateMap1[i]);
    free(tessellateMap1);

    char ** tessellateMap2 = tessellateMap(map, row, col, 10, 8);
    if(tessellateMap2 == NULL) return EXIT_FAILURE;

    printf("\n10x8 Tessellated map is: \n");
    for(int i =0; i < 10; i++){
        for(int j = 0; j < 8;j++){
            printf("%c", tessellateMap2[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < 10; i++) free(tessellateMap2[i]);
    free(tessellateMap2);

    return EXIT_SUCCESS;
}
