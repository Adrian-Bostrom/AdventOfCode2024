#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void select_sort(int *array, int size) {
    for (int i = 0; i < size -1; i++) {
        int candidate = i;
        for (int j = i; j < size; j++) {
            if (array[j] < array[candidate]) {
                candidate = j;
            }
        }
        int placeholder = array[candidate];
        array[candidate] = array[i];
        array[i] = placeholder;
    }
}

int count(int num, int *array, int size) {
    int count = 0;
    for(int i = 0; i < size; i++){
        if(array[i] == num)count++;
        if(array[i] > num) break;
    }
    return count;
}

void main() {
    //handling setting up reader
    char *file = "input";
    FILE *fptr = fopen(file, "r");
    if (fptr == NULL) {
        printf("File not found!\n");
    }
    char *lineptr = malloc(sizeof(char)*20);

    //arrays of ints for input
    int list1[1000];
    int list2[1000];
    int line = 0;

    //takes every line and parses it so both ints go into arrays
    while(fgets(lineptr, 20, fptr) > 0) {
        char *copy = (char*)malloc(sizeof(char)*20);
        strcpy(copy, lineptr);

        list1[line] = atoi(copy);
        strtok(copy, " ");
        list2[line] = atoi(strtok(NULL, " "));

        //printf("%d %d\n",list1[line],list2[line]);
        line++;
    }
    select_sort(list1, 1000);
    select_sort(list2, 1000);
    int total = 0;
    for(int i = 0; i < 1000; i++){
        total += list1[i]*count(list1[i], list2, 1000);
    } 
    printf("Distance: %d\n", total);

}