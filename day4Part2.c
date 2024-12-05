#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void gridScan(char** array, FILE* fp);
int gridWidth(FILE *fp);
int gridLength(FILE *fp);

int xmasAppearTime(char** array, int length, int width);
int xmas(char** array, int length, int width, int indexI, int indexJ);
bool diagonalRight(char** array, int length, int width, int indexI, int indexJ); 
bool diagonalLeft(char** array, int length, int width, int indexI, int indexJ);


int main(int argc, char* argv[]) {
    FILE* fp = stdin;
    int width = gridWidth(fp);
    int length = gridLength(fp);

    char** array = malloc(length * sizeof(char*));
    for(int i = 0; i < length; i++) {
        array[i] = malloc(width * sizeof(char));
    }

    gridScan(array, fp);


    int amount = xmasAppearTime(array, length, width);
    printf("\napears = %d times\n\n", amount);
    
    for(int i = 0; i < length; i++) {
        free(array[i]);
    }
    free(array);
    return 0;
}

int xmasAppearTime(char** array, int length, int width) {
    int count = 0;
    for(int i = 0; i < length; i++) {
        for(int j = 0; j < width; j++) {
            // printf("\n");
            if(array[i][j] != 'A') continue;

            count += xmas(array, length, width, i, j);
        }
    }

    return count;
}

int xmas(char** array, int length, int width, int indexI, int indexJ) {
    if(diagonalRight(array, length, width, indexI, indexJ) &&
       diagonalLeft(array, length, width, indexI, indexJ)) {
        return 1;
    }

    return 0;
}

bool diagonalRight(char** array, int length, int width, int indexI, int indexJ) {
    int tmpI = indexI - 1;
    int tmpJ = indexJ + 1;
    if(tmpI < 0) return false;
    if(tmpJ >= width) return false;

    char str[4] = {'\0'};
    for(int i = 0; i < 3; i++) {
        if(tmpI >= length) return false;
        if(tmpJ < 0) return false;
        str[i] = array[tmpI][tmpJ];
        tmpI++;
        tmpJ--;
    }

    // printf("%s\n", str);
    if(strcmp(str, "MAS") == 0 || strcmp(str, "SAM") == 0) {
        return true;
    }
    return false;
}

bool diagonalLeft(char** array, int length, int width, int indexI, int indexJ) {
    int tmpI = indexI - 1;
    int tmpJ = indexJ - 1;
    if(tmpI < 0) return false;
    if(tmpJ >= width) return false;

    char str[4] = {'\0'};
    for(int i = 0; i < 3; i++) {
        if(tmpI >= length) return false;
        if(tmpJ >= width) return false;
        str[i] = array[tmpI][tmpJ];
        tmpI++;
        tmpJ++;
    }
    // printf("%s\n", str);
    if(strcmp(str, "MAS") == 0 || strcmp(str, "SAM") == 0) {
        return true;
    }
    return false;
}

void gridScan(char** array, FILE* fp) {
    fseek(fp, 0, SEEK_SET);
    char str[500];
    int level = 0;
    while(fgets(str, 500, fp)) {
        for(int i = 0; str[i] != '\0'; i++) {
            array[level][i] = str[i];
        }
        level++;
    }
}

int gridWidth(FILE *fp) {
    fseek(fp, 0, SEEK_SET);
    char str[500];
    fscanf(fp, "%s", str);
    return strlen(str);
}

int gridLength(FILE *fp) {
    fseek(fp, 0, SEEK_SET);
    char str[500];
    int length = 0;
    while(fgets(str, 500, fp)) {
        length++;
    }
    return length;
}





