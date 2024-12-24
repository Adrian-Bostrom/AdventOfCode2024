#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void importList(char *lineptr, char **list, FILE *fptr){
    int line = 0;
    while(fgets(lineptr, 3500, fptr) > 0) {
        char *text = malloc(sizeof(char)*3500);
        strcpy(text, lineptr);
        char *ptr = text; 
        while((reti = regexec(&regex, ptr, 1, matches, 0)) == 0){
            int start = matches[0].rm_so;
            int end = matches[0].rm_eo;
            char *match = malloc(sizeof(char) *(end - start + 1));
            strncpy(match, ptr + start, end - start);
            match[end - start] = '\0';
            ptr += start + 1;
            list[matchNum++] = match;
        }
        line++;
        free(text);
    }
    regfree(&regex);
}

int main(){
    char *file = "input";
    FILE *fptr = fopen(file, "r");
    if (fptr == NULL) {
        printf("File not found!\n");
    }
    char *lineptr = calloc(3500,sizeof(char));
    char **list = calloc(2000, sizeof(char *));
    importList(lineptr, list, fptr);
}