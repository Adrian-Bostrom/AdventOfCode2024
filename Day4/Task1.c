#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int EastCount = 0;
bool XMAScompare(char *comparing){
    if(strcmp(comparing,"XMAS") == 0)return true;
    else return false;
}
//returns the amount of XMAS are connected to that X
//0,0 is on top left, like in sudoku
//Function assumes its a 140x140 box
int XMASchecker(char **lines, int x, int y){
    char PotentialXmas[5];
    PotentialXmas[0] = 'X';
    PotentialXmas[4] = '\0';
    int ret = 0;
    //North West
    if(x > 2 && y > 2) {
        for(int i = 1; i < 4; i++){
            PotentialXmas[i] = lines[y - i][x - i];
        }
        ret += XMAScompare(PotentialXmas);
    }
    //North
    if(y > 2) {
        for(int i = 1; i < 4; i++){
            PotentialXmas[i] = lines[y - i][x];
        }
        ret += XMAScompare(PotentialXmas);
    }
    //North East
    if(x < 137 && y > 2) {
        for(int i = 1; i < 4; i++){
            PotentialXmas[i] = lines[y - i][x + i];
        }
        ret += XMAScompare(PotentialXmas);
    }
    //East  
    if(x < 137) {
        for(int i = 1; i < 4; i++){
            PotentialXmas[i] = lines[y][x + i];
        }
        ret += XMAScompare(PotentialXmas);
        if(XMAScompare(PotentialXmas))EastCount++;
    }
    //South East
    if(x < 137 && y < 137) {
        for(int i = 1; i < 4; i++){
            PotentialXmas[i] = lines[y + i][x + i];
        }
        ret += XMAScompare(PotentialXmas);
    }
    //South
    if(y < 137) {
        for(int i = 1; i < 4; i++){
            PotentialXmas[i] = lines[y + i][x];
        }
        ret += XMAScompare(PotentialXmas);
    }
    //South West
    if(x > 2 && y < 137) {
        for(int i = 1; i < 4; i++){
            PotentialXmas[i] = lines[y + i][x - i];
        }
        ret += XMAScompare(PotentialXmas);
    }
    //West
    if(x > 2) {
        for(int i = 1; i < 4; i++){
            PotentialXmas[i] = lines[y][x - i];
        }
        ret += XMAScompare(PotentialXmas);
    }
    return ret;
}

void importList(char *lineptr, char **list, FILE *fptr){
    int line = 0;
    while(fgets(lineptr, 3500, fptr) > 0) {
        char *text = malloc(sizeof(char)*150);
        strcpy(text, lineptr);
        list[line] = text;
        line++;
    }
}

int main(){
    char *file = "input";
    FILE *fptr = fopen(file, "r");
    if (fptr == NULL) {
        printf("File not found!\n");
    }
    char *lineptr = calloc(150,sizeof(char));
    char **list = calloc(150, sizeof(char *));
    importList(lineptr, list, fptr);
    int sum = 0;
    for(int y = 0; y < 140; y++){
        for(int x = 0; x < 140; x++){
            if(list[y][x] == 'X')sum += XMASchecker(list,x,y);
        }
        printf("sum: %d\n",sum);
    }
    printf("East Count: %d", EastCount);
    free(lineptr);
}