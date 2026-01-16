#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getPopulation(char * file, char * region);
char *highestPercentage(char *file);
float *employmentInsurance(char *file);
char **speaksFrench(char *file, int checkFrench);
int nonCanadian(char * file);
char *over45ToWork(char *file);

void printIntArray(float *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%.2f, ", arr[i]);
    }
    printf("\n");
}

void printCharArray(char **arr) {
    for (int i = 0; arr[i] != NULL; i++) {
        printf("%s,", arr[i]);
    }
    printf("\n");
}





int main(int argc, char ** argv){

    char *file = "Census.csv";
    
    //population test
    char *reg1= "Saint John";
    int testPopulation = getPopulation(file, reg1);
    if(testPopulation != -1){
        printf("Population of %s: %d\n", reg1, testPopulation);
    }
    else{
        printf("Population of %s: Region not found \n", reg1);
    }

    char *reg2 = "Lagos";
    int testPopulation2 = getPopulation(file, reg2);
    if(testPopulation2 != -1){
        printf("Population of Lagos: %d\n", reg2, testPopulation2);
    }
    else{
        printf("Population of %s: Region not found \n", reg2);
    }

    //percentage test
    char *testPercentage = highestPercentage(file);
    if (testPercentage == NULL)
    {
        return EXIT_FAILURE;
    }
    printf("\nThe region with the highest percentage of people making over $150K is: %s\n", testPercentage);
    free(testPercentage);

    //employment insurance test
    float *testInsurance = employmentInsurance(file);
    if (testInsurance == NULL)
    {
        return EXIT_FAILURE;
    }
    printf("\nThe percentage of peoples income (aged 25-34) comes from employment insurance in each region is: \n");
    printIntArray(testInsurance, 13);
    free(testInsurance);

    //mother tongue
    int check1 = 10000;
    char **testfrench1 = speaksFrench(file, check1);
    if(testfrench1 == NULL){
        printf("There is no region");
    }
    else{
        printf("\nRegions that have more than than %d number of people with the mother tongue of French (18 and above) is:\n", check1);
        printCharArray(testfrench1);

        for (int i = 0; testfrench1[i] != NULL; i++) {
            free(testfrench1[i]);
        }
    free(testfrench1);
    }

    int check2 = 5000000;
    char **testfrench2 = speaksFrench(file, check2);
    if(testfrench2 == NULL){
        printf("\nRegions that have more than than %d number of people with the mother tongue of French (18 and above) is: ", check2);
        printf("There is no region\n");
    }
    else{
        printf("Regions that have more than than %d number of people with the mother tongue of French (18 and above) is:\n", check2);
        printCharArray(testfrench2); 

        for (int i = 0; testfrench2[i] != NULL; i++) {
            free(testfrench1[i]);
        }
    free(testfrench2);
    }

    //non canadian test
    int testNonCanadian = nonCanadian(file);
    printf("\nThe total number of non Canadian Citizens in the range of 35-54 living in New Brunswick is %d\n", testNonCanadian);

    //over 45 mins
    char *testOver45 = over45ToWork(file);
    if (testOver45 == NULL)
    {
        return EXIT_FAILURE;
    }
    printf("\nThe region with the highest number of people travelling 45 minutes or more to work is: %s\n", testOver45);
    free(testOver45);


    return EXIT_SUCCESS;
}

