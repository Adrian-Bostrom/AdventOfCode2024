#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdbool.h>

int multiply(char *input){
    char copy[15];
    strcpy(copy,input);
    strtok(copy, "(");
    int number1 = atoi(strtok(NULL, ","));
    int number2 = atoi(strtok(NULL, ")"));
    printf("%s: %d x %d = %d\n", input, number1, number2, number1 * number2);
    return (number1 * number2);
}

void importList(char *lineptr, char **list, FILE *fptr){
    int line = 0;
    int validCount = 0;
    const char *pattern = "mul\\([0-9]+,[0-9]+\\)|do\\(\\)|don't\\(\\)"; // Regex to match one or more digits
    //const char *text = "The numbers are 42 and 100.";
    regex_t regex;
    regmatch_t matches[100]; // Array to store match information
    int reti;
    int matchNum = 0;
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }
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
    printf("%s\n", list[0]);
    int len = 0,sum = 0;
    bool doo = true;
    while(list[len] != 0){
        printf("%s\n",list[len]);
        if(strcmp(list[len],"do()\0") == 0) doo = true;
        else if(strcmp(list[len],"don't()\0") == 0) doo = false;
        else if(doo) sum += multiply(list[len]);
        len++;
        printf("sum: %d\n", sum);
    }
    printf("\nfinal sum: %d\n",sum );
}