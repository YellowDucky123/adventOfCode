#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

int mainFunction(FILE *fp);
int inputRead(int* array, char *str);
bool isIncreasing(int *array, int amount);
bool isDecreasing(int *array, int amount);

int main(int argc, char *argv[]) {
    int res = mainFunction(stdin);
    printf("\ncount is = %d\n\n", res);

    return 0;
}

int mainFunction(FILE *fp) {
    int count = 0;
    char str[100];
     
    while(fgets(str, 100, fp)) {
        int array[50];
        int amount = inputRead(array, str);

        if(!isIncreasing(array, amount) && !isDecreasing(array, amount)) {
            continue;
        } 

        bool flag = true;
        for(int i = 0; i < amount - 1; i++) {
            if(abs(array[i] - array[i + 1]) > 3) {
                flag = false;
                break;
            }
        }
        if(flag) {
            count++;
        }
    }

    return count;
}

int inputRead(int* array, char* str) {
    int index = 0;
    int value;
    char *res = strtok(str, " ");
   
    while(res != NULL) {
        sscanf(res, "%d", &value);
        array[index] = value;
        index++;
        res = strtok(NULL, " ");
    }

    return index;
}

bool isIncreasing(int *array, int amount) {
    for(int i = 0; i < amount - 1; i++) {
        if(array[i] >= array[i + 1]) {
            return false;
        }
    }
    return true;
}

bool isDecreasing(int *array, int amount) {
    for(int i = 0; i < amount - 1; i++) {
        if(array[i] <= array[i + 1]) {
            return false;
        }
    }
    return true;
}