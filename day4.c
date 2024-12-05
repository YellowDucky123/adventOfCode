#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void gridScan(char** array, FILE* fp);
int gridWidth(FILE *fp);
int gridLength(FILE *fp);

int xmasAppearTime(char** array, int length, int width);
int xmas(char** array, int length, int width, int indexI, int indexJ);
bool xmasStraight(char** array, int length, int width, int indexI, int indexJ);
bool xmasDown(char** array, int length, int width, int indexI, int indexJ);
bool xmasBackwards(char** array, int length, int width, int indexI, int indexJ);
bool xmasUp(char** array, int length, int width, int indexI, int indexJ);
bool xmasDiagonalRightDown(char** array, int length, int width, int indexI, int indexJ);
bool xmasDiagonalLeftDown(char** array, int length, int width, int indexI, int indexJ);
bool xmasDiagonalLeftUp(char** array, int length, int width, int indexI, int indexJ);
bool xmasDiagonalRightUp(char** array, int length, int width, int indexI, int indexJ);

int main(int argc, char* argv[]) {
    FILE* fp = stdin;
    int width = gridWidth(fp);
    int length = gridLength(fp);

    char** array = malloc(length * sizeof(char*));
    for(int i = 0; i < length; i++) {
        array[i] = malloc(width * sizeof(char));
    }

    gridScan(array, fp);

    // for(int i = 0; i < length; i++) {
    //     for(int j = 0; j < width; j++) {
    //         printf("%c ", array[i][j]);
    //     }
    //     printf("\n");
    // }

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
            if(array[i][j] != 'X') continue;

            count += xmas(array, length, width, i, j);
        }
    }

    return count;
}

int xmas(char** array, int length, int width, int indexI, int indexJ) {
    int count = 0;

    if(xmasStraight(array, length, width, indexI, indexJ)) count++;
    if(xmasDown(array, length, width, indexI, indexJ)) count++;
    if(xmasBackwards(array, length, width, indexI, indexJ)) count++;
    if(xmasUp(array, length, width, indexI, indexJ)) count++;
    if(xmasDiagonalRightDown(array, length, width, indexI, indexJ)) count++;
    if(xmasDiagonalRightUp(array, length, width, indexI, indexJ)) count++;
    if(xmasDiagonalLeftDown(array, length, width, indexI, indexJ)) count++;
    if(xmasDiagonalLeftUp(array, length, width, indexI, indexJ)) count++;

    return count;
}

bool xmasStraight(char** array, int length, int width, int indexI, int indexJ) {
    char str[5] = {'\0'};
    int xmasIndex = 0;
    for(int k = 0; k < 4; k++) {
        if(indexJ >= width) {
            return false;
        }
        str[xmasIndex] = array[indexI][indexJ];
        xmasIndex++;
        indexJ++;
    }
    if(strcmp("XMAS", str) == 0) return true;
    return false;
}

bool xmasDown(char** array, int length, int width, int indexI, int indexJ) {
    char str[5] = {'\0'};
    int xmasIndex = 0;
    for(int k = 0; k < 4; k++) {
        if(indexI >= length) return false;

        str[xmasIndex] = array[indexI][indexJ];
        xmasIndex++;
        indexI++;
    }
    if(strcmp("XMAS", str) == 0) return true;
    return false;
}

bool xmasBackwards(char** array, int length, int width, int indexI, int indexJ) {
    char str[5] = {'\0'};
    int xmasIndex = 0;
    for(int k = 0; k < 4; k++) {
        if(indexJ < 0) return false;

        str[xmasIndex] = array[indexI][indexJ];
        xmasIndex++;
        indexJ--;
    }
    if(strcmp("XMAS", str) == 0) return true;
    return false;
}

bool xmasUp(char** array, int length, int width, int indexI, int indexJ) {
    char str[5] = {'\0'};
    int xmasIndex = 0;
    for(int k = 0; k < 4; k++) {
        if(indexI < 0) return false;

        str[xmasIndex] = array[indexI][indexJ];
        xmasIndex++;
        indexI--;
    }
    if(strcmp("XMAS", str) == 0) return true;
    return false;
}

bool xmasDiagonalRightDown(char** array, int length, int width, int indexI, int indexJ) {
    char str[5] = {'\0'};
    int xmasIndex = 0;
    for(int k = 0; k < 4; k++) {
        if(indexJ >= width) return false;
        if(indexI >= length) return false;

        str[xmasIndex] = array[indexI][indexJ];
        xmasIndex++;
        indexJ++;
        indexI++;
    }
    if(strcmp("XMAS", str) == 0) return true;
    return false;
}

bool xmasDiagonalLeftDown(char** array, int length, int width, int indexI, int indexJ) {
    char str[5] = {'\0'};
    int xmasIndex = 0;
    for(int k = 0; k < 4; k++) {
        if(indexJ < 0) return false;
        if(indexI >= length) return false;

        str[xmasIndex] = array[indexI][indexJ];
        xmasIndex++;
        indexJ--;
        indexI++;
    }
    if(strcmp("XMAS", str) == 0) return true;
    return false;
}

bool xmasDiagonalLeftUp(char** array, int length, int width, int indexI, int indexJ) {
    char str[5] = {'\0'};
    int xmasIndex = 0;
    for(int k = 0; k < 4; k++) {
        if(indexJ < 0) return false;
        if(indexI < 0) return false;

        str[xmasIndex] = array[indexI][indexJ];
        xmasIndex++;
        indexJ--;
        indexI--;
    }
    if(strcmp("XMAS", str) == 0) return true;
    return false;
}

bool xmasDiagonalRightUp(char** array, int length, int width, int indexI, int indexJ) {
    char str[5] = {'\0'};
    int xmasIndex = 0;
    for(int k = 0; k < 4; k++) {
        if(indexJ >= width) return false;
        if(indexI < 0) return false;

        str[xmasIndex] = array[indexI][indexJ];
        xmasIndex++;
        indexJ++;
        indexI--;
    }
    if(strcmp("XMAS", str) == 0) return true;
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





