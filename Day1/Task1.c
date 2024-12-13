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

void merge(int *org, int *aux, int lo, int mid, int hi) {
    // copy all items from lo to hi from org to aux
    for (int i = lo; i <= hi; i++) aux[i] = org[i];
    // let's do the merging
    int i = lo; // the index in the first part
    int j = mid+1; // the index in the second part
    // for all indices from lo to hi
    for ( int k = lo; k <= hi; k++) {
        // if i is greater than mid then
        if(i > mid){
            org[k] = aux[j];
            j++;
        }
        else if(j > hi){
            org[k] = aux[i];
            i++;
        }
        else if(aux[i] <= aux[j]){
            org[k] = aux[i];
            i++;
        }
        else{
            org[k] = aux[j];
            j++;
        }
        // move the j'th item to the org array, update j
        // else if j is greate than hi then
        // move the i'th item to the org array, update i
        // else if the i'th item is smaller than the j'th item,
        // move the i'th item to the org array, update i
        // else
        // move the j'th item to the org array, update j
    }
}

void merge_sort(int *org, int *aux, int lo, int hi) {
    if (lo != hi) {
        int mid = (lo + hi)/2;
        // sort the items from lo to mid
        merge_sort(org, aux, lo, mid);
        // sort the items from mid+1 to hi
        merge_sort(org, aux, mid+1, hi);
        // merge the two sections using the additional array
        merge(org, aux, lo, mid, hi);
    }
}

void merge_init(int *org, int n) {
    if (n == 0) return;
    int *aux = (int*)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++) aux[i] = org[i];
    merge_sort(org, aux, 0, n);
    free(aux);
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
    int distance = 0;
    for(int i = 0; i < 1000; i++){
        printf("%d %d\n",list1[i],list2[i]);
        distance += abs(list1[i] - list2[i]);
    } 
    printf("Distance: %d\n", distance);

}