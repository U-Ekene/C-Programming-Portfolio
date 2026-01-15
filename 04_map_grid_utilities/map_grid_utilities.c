#include <stdio.h>
#include <stdlib.h>

/*
 * create2dArray
 * Dynamically allocates a 2D char array (row x col) using a char**.
 * Initializes every tile to 0.
 * Returns the allocated array, or NULL if allocation fails.
 */
char ** create2dArray(int row, int col){
    char **arr2d = NULL;

    /* allocate array of row pointers */
    arr2d = malloc(sizeof(char*) * row);
    if (arr2d == NULL) {
        return NULL;
    }

    /* allocate each row */
    for (int k = 0; k < row; k++) {
        arr2d[k] = malloc(sizeof(char) * col);
        if (arr2d[k] == NULL) {
            return NULL;
        }
    }

    /* initialize to 0 */
    for(int x = 0; x < row; x++){
        for(int y = 0; y < col; y++){
            arr2d[x][y] = 0;
        }
    }

    return arr2d;
}

/*
 * clearcut
 * Creates a copy of the map, then replaces 'F' with 'P' in the top-left
 * cutRow x cutCol region (after bounds adjustment).
 * Returns the newly allocated modified map.
 */
char ** clearcut(char ** map, int sizeRow, int sizeCol, int cutRow, int cutCol){
    /* copy map into a newly allocated array */
    char ** copy = create2dArray(sizeRow, sizeCol);
    for(int m = 0; m < sizeRow; m++){
        for(int j = 0; j < sizeCol; j++){
            copy[m][j] = map[m][j];
        }
    }

    char ** result = copy;

    /* clamp cut sizes if out of range */
    if(cutRow <= 0 || cutRow > sizeRow){
        cutRow = sizeRow;
    }
    if(cutCol <= 0 || cutCol > sizeCol){
        cutCol = sizeCol;
    }

    /* replace forest tiles in the cut region */
    for(int row = 0; row < cutRow; row++){
        for(int col = 0; col < cutCol; col++){
            if(copy[row][col] == 'F'){
                copy[row][col] = 'P';
            }
        }
    }

    return result;
}

/*
 * predictClearcut
 * Counts how many 'F' tiles are within the top-left cutRow x cutCol region
 * (after bounds adjustment). Does not modify the map.
 * Returns the count.
 */
int predictClearcut(char ** map, int sizeRow, int sizeCol, int cutRow, int cutCol){
    int count = 0;

    /* clamp cut sizes if out of range */
    if(cutRow <= 0 || cutRow > sizeRow){
        cutRow = sizeRow;
    }
    if(cutCol <= 0 || cutCol > sizeCol){
        cutCol = sizeCol;
    }

    /* count forest tiles in the cut region */
    for(int row = 0; row < cutRow; row++){
        for(int col = 0; col < cutCol; col++){
            if(map[row][col] == 'F'){
                count++;
            }
        }
    }

    return count;
}

/*
 * countTiles
 * Counts how many times a given tile character appears in the full map.
 * Returns the count.
 */
int countTiles(char ** map, int sizeRow, int sizeCol, char tile){
    int count = 0;

    for(int row = 0; row < sizeRow; row++){
        for(int col = 0; col < sizeCol; col++){
            if(map[row][col] == tile){
                count++;
            }
            else{
                count = count; /* no-op (kept as your original style) */
            }
        }
    }

    return count;
}

/*
 * countTilesRow
 * Returns an int array of length sizeRow where each element is the count of
 * the given tile in that row.
 * The returned array is dynamically allocated and must be freed by the caller.
 * Returns NULL if allocation fails.
 */
int * countTilesRow(char ** map, int sizeRow, int sizeCol, char tile){
    int * result = malloc(sizeof(int) * sizeRow);
    if(result == NULL){
        return NULL;
    }

    int count = 0;

    for(int row = 0; row < sizeRow; row++){
        count = 0;
        for(int col = 0; col < sizeCol; col++){
            if(map[row][col] == tile){
                count++;
            }
            else{
                count = count; /* no-op (kept as your original style) */
            }
            result[row] = count;
        }
    }

    return result;
}

/*
 * floodRisk
 * Counts how many 'R' tiles have at least one adjacent 'W' tile
 * (up/down/left/right). Each 'R' can contribute at most 1 to the count
 * because of the else-if chain.
 * Returns the flood risk count.
 */
int floodRisk(char ** map, int sizeRow, int sizeCol){
    int floodcount = 0;

    for(int row = 0; row < sizeRow; row++){
        for(int col = 0; col < sizeCol; col++){
            if(map[row][col] == 'R'){
                if(row > 0 && map[row-1][col] == 'W'){
                    floodcount++;
                }
                else if(row < sizeRow - 1 && map[row+1][col] == 'W'){
                    floodcount++;
                }
                else if(col > 0 && map[row][col-1] == 'W'){
                    floodcount++;
                }
                else if(col < sizeCol - 1 && map[row][col+1] == 'W'){
                    floodcount++;
                }
            }
        }
    }

    return floodcount;
}

/*
 * islands
 * Returns a NULL-terminated array of pointers to tiles that are "single-tile islands":
 * a non-'W' tile whose four neighbors (up/down/left/right) are all 'W'.
 * The returned list is dynamically allocated and must be freed by the caller.
 * NOTE: The pointers inside the list point into the original map (not copies).
 */
char ** islands(char ** map, int sizeRow, int sizeCol){
    int maxSize = (sizeRow * sizeCol) + 1;

    /* allocate output list of pointers */
    char ** out = malloc(sizeof(char*) * maxSize);
    if(out == NULL){
        return NULL;
    }

    int i = 0;

    /* only check interior cells to avoid out-of-bounds neighbor access */
    for(int row = 1; row < sizeRow - 1; row++){
        for(int col = 1; col < sizeCol - 1; col++){
            if(map[row][col] != 'W'){
                if(map[row+1][col] == 'W' && map[row-1][col] == 'W' &&
                   map[row][col+1] == 'W' && map[row][col-1] == 'W'){
                    out[i] = &(map[row][col]);
                    i++;
                }
            }
        }
    }

    /* terminate list */
    out[i] = NULL;
    return out;
}

/*
 * subMap
 * Extracts a rectangular region from the map starting at (startRow, startCol)
 * with dimensions numRows x numCols.
 * Returns a newly allocated map containing the copied region, or NULL if the
 * region is out of bounds.
 */
char ** subMap(char ** map, int sizeRow, int sizeCol,
               int startRow, int startCol, int numRows, int numCols){

    /* bounds check */
    if (numRows > sizeRow || numCols > sizeCol ||
        (numRows + startRow) > sizeRow || (numCols + startCol) > sizeCol){
        return NULL;
    }

    /* allocate output region */
    char ** out = create2dArray(numRows, numCols);

    /* copy tiles */
    for(int row = 0; row < numRows; row++){
        for(int col = 0; col < numCols; col++){
            out[row][col] = map[row + startRow][col + startCol];
        }
    }

    return out;
}

/*
 * tessellateMap
 * Creates a new map of size newRow x newCol by repeating (tiling) the original map
 * pattern using modulo indexing.
 * Returns the newly allocated tessellated map.
 */
char ** tessellateMap(char ** map, int sizeRow, int sizeCol, int newRow, int newCol){
    char ** tesMap = create2dArray(newRow, newCol);

    for(int row = 0; row < newRow; row++){
        for(int col = 0; col < newCol; col++){
            tesMap[row][col] = map[row % sizeRow][col % sizeCol];
        }
    }

    return tesMap;
}
