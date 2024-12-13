#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
bool isIncreasing(int first, int second) {
    return (first - second < 0) ? true : false;
}

bool isValid(int *inputLine) {
    bool increasing = isIncreasing(inputLine[0], inputLine[1]);
    int nextIndex = 1;
    int previous = inputLine[nextIndex - 1];
    int next = inputLine[nextIndex];
    while(inputLine[nextIndex] != 0){
        next = inputLine[nextIndex];
        
        if(abs(next - previous) > 3 || abs(next - previous) == 0) return false;
        if(isIncreasing(previous,next) != increasing) return false;
        previous = next;
        nextIndex++;
        next = inputLine[nextIndex];
    }
    return true;
}
void importList(char *lineptr, int **list, FILE *fptr){
    int line = 0;
    int validCount = 0;
    while(fgets(lineptr, 30, fptr) > 0) {
        char *copy = (char*)malloc(sizeof(char)*30);
        int *listElement = calloc(sizeof(int),30);
        strcpy(copy, lineptr);
        char * token;
        token = strtok(copy, " ");
        int top = -1;
        while( token != NULL )
        {
            top++;
            listElement[top] = atoi(token);

            token = strtok(NULL, " ");
        }
        list[line] = listElement;
        //strtok(copy, " ");
        //list[line][2] = atoi(strtok(NULL, " "));
        for(int i=0;i<=top;i++)
        {
            printf("%d ",listElement[i]);
        }
        validCount += isValid(listElement);
        printf("%d, %d", isValid(listElement), validCount);
        printf("\n");
        //printf("%d %d\n", *(list[line]), *(list[line] + 1));
        line++;
        free(copy);
    }
}


void main(void){
    char *file = "input";
    FILE *fptr = fopen(file, "r");
    if (fptr == NULL) {
        printf("File not found!\n");
    }

    char *lineptr = malloc(sizeof(char)*30);

    //list of arrays of ints to hold elements

    int ** list = calloc(1000,sizeof(int *));

    importList(lineptr,list,fptr);
    printf("---------------------------------------------------------------\n\n");
    int countValid = 0;
    for(int i = 0; i <1000; i++) {
        countValid += (isValid(list[i]) == true ? 1 : 0);
    }
    printf("%d\n", countValid);
}
 