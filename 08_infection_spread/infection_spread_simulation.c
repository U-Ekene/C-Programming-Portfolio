#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * Allocates and initializes a 2D integer array of size row x col.
 * Returns NULL if allocation fails.
 */
int **create2DArray(int row, int col) {
    int **arr2D = calloc(row, sizeof(int *));
    if (arr2D == NULL) {
        return NULL;
    }

    for (int i = 0; i < row; i++) {
        arr2D[i] = calloc(col, sizeof(int));
        if (arr2D[i] == NULL) {
            return NULL;
        }
    }

    return arr2D;
}

/* Frees a dynamically allocated 2D array */
void freeArray(int **arr, int rows){
    for (int i = 0; i < rows; i++){
        free(arr[i]);
    }
    free(arr);
}

/*
 * Recursively writes a 2D array to a file in CSV format.
 * Rows are written line by line.
 */
void writeTo2DArray(FILE *outfile, int **arr, int row, int col,
                    int maxRow, int maxCol){
    if (row == maxRow) {
        return;
    }

    if (col == maxCol) {
        fprintf(outfile, "\n");
        writeTo2DArray(outfile, arr, row + 1, 0, maxRow, maxCol);
        return;
    }

    fprintf(outfile, "%d", arr[row][col]);
    if (col < maxCol - 1) {
        fprintf(outfile, ",");
    }

    writeTo2DArray(outfile, arr, row, col + 1, maxRow, maxCol);
}

/*
 * Reads a fixed number of lines from a file into a string array.
 * Used to read header/map configuration information.
 */
void readFileLines(FILE *file, char **arr, int count, int num){
    if(count >= num){
        return;
    }

    char thisline[256];
    if (fgets(thisline, sizeof(thisline), file) == NULL) {
        return;
    }
    
    arr[count] = malloc(strlen(thisline) + 1);
    strcpy(arr[count], thisline);

    readFileLines(file, arr, count + 1, num);
}

/*
 * Recursively parses a single CSV row into a 2D array row.
 */
void readFileRow(int **arr, char *token, int row, int col){
    if(token == NULL){
        return;
    }

    arr[row][col] = atoi(token);
    token = strtok(NULL, ",");
    readFileRow(arr, token, row, col + 1);
}

/*
 * Recursively reads a population or infection map from file
 * into a 2D integer array.
 */
void readFilePopulationMap(FILE *file, int **arr,
                           int count, int rows, int cols){
    if(count == rows){
        return;
    }

    char thisline[256];
    if (fgets(thisline, sizeof(thisline), file) == NULL) {
        return;
    }

    char *token = strtok(thisline, ",");
    readFileRow(arr, token, count, 0);
    readFilePopulationMap(file, arr, count + 1, rows, cols);
}

/*
 * Initializes the new infection map by setting all cells to -1.
 * This allows detection of unvisited cells during recursion.
 */
void resetNewInfectionMap(int **arr, int row, int col,
                          int maxRow, int maxCol){
    if(row == maxRow){
        return;
    }

    if(col == maxCol){
       resetNewInfectionMap(arr, row + 1, 0, maxRow, maxCol);
       return; 
    }

    arr[row][col] = -1;
    resetNewInfectionMap(arr, row, col + 1, maxRow, maxCol);
}

/*
 * Computes a proximity (risk) map using recursive flood traversal.
 * Cells closer to the outbreak location receive higher proximity values.
 */
void computeProximityMap(int **proximity, int **population,
                         int radius, int distance,
                         int row, int col,
                         int maxRow, int maxCol){
    
    // Bounds and stopping conditions
    if (row < 0 || row >= maxRow || col < 0 || col >= maxCol) return;
    if (distance > radius) return;
    if (population[row][col] == 0) return;

    int val = radius - distance + 1;

    // Do not overwrite stronger proximity values
    if(proximity[row][col] >= val && proximity[row][col] != -1) return;

    proximity[row][col] = val;

    // Recurse in four directions
    computeProximityMap(proximity, population, radius, distance + 1,
                        row + 1, col, maxRow, maxCol); // down
    computeProximityMap(proximity, population, radius, distance + 1,
                        row - 1, col, maxRow, maxCol); // up
    computeProximityMap(proximity, population, radius, distance + 1,
                        row, col + 1, maxRow, maxCol); // right
    computeProximityMap(proximity, population, radius, distance + 1,
                        row, col - 1, maxRow, maxCol); // left
}

/*
 * Computes the number of new infections per cell based on:
 * proximity, remaining population, and seasonal multiplier.
 */
void computeNewInfectionMap(int **newInfection, int **oldInfection,
                            int **population, int **proximity,
                            float multiplier,
                            int row, int col,
                            int maxRow, int maxCol){
    if (row < 0 || row >= maxRow || col < 0 || col >= maxCol) return;
    if(newInfection[row][col] != -1) return;

    newInfection[row][col] =
        (proximity[row][col] / 10.0) *
        (population[row][col] - oldInfection[row][col]) *
        multiplier;

    // Recurse across grid
    computeNewInfectionMap(newInfection, oldInfection, population,
                           proximity, multiplier,
                           row + 1, col, maxRow, maxCol);
    computeNewInfectionMap(newInfection, oldInfection, population,
                           proximity, multiplier,
                           row - 1, col, maxRow, maxCol);
    computeNewInfectionMap(newInfection, oldInfection, population,
                           proximity, multiplier,
                           row, col + 1, maxRow, maxCol);
    computeNewInfectionMap(newInfection, oldInfection, population,
                           proximity, multiplier,
                           row, col - 1, maxRow, maxCol);
}

/* Removes trailing newline and carriage return characters */
void trimNewline(char *str){
    int len = strlen(str);

    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
        len--;
    }
    if (len > 0 && str[len - 1] == '\r') {
        str[len - 1] = '\0';
    }
}

/* Returns seasonal infection multiplier */
float getMultiplier(char *season){
    if (strcmp(season, "Spring") == 0) return 0.25;
    if (strcmp(season, "Summer") == 0) return 0.1;
    if (strcmp(season, "Autumn") == 0) return 0.5;
    if (strcmp(season, "Winter") == 0) return 0.75;
    return 0;
}

/*
 * Merges new infections into the existing infection map,
 * ensuring values never exceed population.
 */
void mergeMaps(int **oldInfection, int **newInfection,
               int **population,
               int row, int col,
               int maxRow, int maxCol){
    if (row == maxRow) return;
    if (col == maxCol) {
        mergeMaps(oldInfection, newInfection, population,
                  row + 1, 0, maxRow, maxCol);
        return;
    }

    int sum = oldInfection[row][col] + newInfection[row][col];
    if (sum > population[row][col]) {
        sum = population[row][col];
    }
    oldInfection[row][col] = sum;

    mergeMaps(oldInfection, newInfection, population,
              row, col + 1, maxRow, maxCol);
}

int main(int argc, char **argv){
    // Expect input and output file paths
    if (argc != 3) {
        return EXIT_FAILURE;
    }

    FILE *input = fopen(argv[1], "r");
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    // Read header / configuration data
    char **mapInfo = malloc(sizeof(char *) * 7);
    readFileLines(input, mapInfo, 0, 7);

    int rows = atoi(mapInfo[1]);
    int cols = atoi(mapInfo[2]);
    int outbreakRow = atoi(mapInfo[3]);
    int outbreakCol = atoi(mapInfo[4]);
    int initialInfect = atoi(mapInfo[5]);
    char *season = mapInfo[6];
    trimNewline(season);

    float multiplier = getMultiplier(season);

    // Allocate maps
    int **population   = create2DArray(rows, cols);
    int **oldInfection = create2DArray(rows, cols);
    int **proximity    = create2DArray(rows, cols);
    int **newInfection = create2DArray(rows, cols);

    // Read population and infection maps
    readFilePopulationMap(input, population,   0, rows, cols);
    readFilePopulationMap(input, oldInfection, 0, rows, cols);

    int radius = (initialInfect / 10) + 1;

    // Compute proximity and infection spread
    computeProximityMap(proximity, population, radius, 0,
                        outbreakRow, outbreakCol, rows, cols);

    resetNewInfectionMap(newInfection, 0, 0, rows, cols);
    computeNewInfectionMap(newInfection, oldInfection, population,
                           proximity, multiplier,
                           outbreakRow, outbreakCol, rows, cols);
    newInfection[outbreakRow][outbreakCol] = initialInfect;

    mergeMaps(oldInfection, newInfection, population,
              0, 0, rows, cols);

    // Write updated infection map
    FILE *output = fopen(argv[2], "w");
    writeTo2DArray(output, oldInfection, 0, 0, rows, cols);

    fclose(input);
    fclose(output);

    // Cleanup
    freeArray(population, rows);
    freeArray(oldInfection, rows);
    freeArray(proximity, rows);
    freeArray(newInfection, rows);
    for (int i = 0; i < 7; i++) free(mapInfo[i]);
    free(mapInfo);

    printf("Done.\n");
    return EXIT_SUCCESS;
}
