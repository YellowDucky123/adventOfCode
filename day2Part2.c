#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

int mainFunction(FILE *fp);
bool isSafe(int* array, int amount, bool firstWrong);
int inputRead(int* array, char *str);
bool isIncreasing(int *array, int amount, bool firstWrong);
bool isDecreasing(int *array, int amount, bool firstWrong);
void arrayDeleteItem(int *array, int index, int size);

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

        int array2[50];
        int index = 1;
        for(int i = 0; i < amount - 1; i++) {
            array2[i] = array[index];
            index++;
        }
        
        if(isSafe(array, amount, false)) {
            count++;
            continue;
        }

        if(isSafe(array2, amount - 1, true)) {
            count++;
        }  
    }

    return count;
}

bool isSafe(int* array, int amount, bool firstWrong) {
    if(!isIncreasing(array, amount, firstWrong) && !isDecreasing(array, amount, firstWrong)) {
        return false;
    } 
    return true;
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

bool isIncreasing(int *array, int amount, bool firstWrong) {
    bool first = true;
    bool ret = true;
    if(firstWrong) {
        first = false;
    }

    int index = -1;
    int prev = array[0] - 1;
    for(int i = 0; i < amount; i++) {
        if((array[i] - prev) <= 0 || (array[i] - prev) > 3) {
            if(first) {
                first = false;
                index = i;
                continue;
            }
            ret = false;
            break;
        }
        else {
            prev = array[i];
        }
    }

    return ret;
}

bool isDecreasing(int *array, int amount, bool firstWrong) {
    bool first = true;
    bool ret = true;
    if(firstWrong) {
        first = false;
    }

    int index = -1;
    int prev = array[0] + 1;
    for(int i = 0; i < amount; i++) {
        if((array[i] - prev) >= 0 || abs(array[i] - prev) > 3) {
            if(first) {
                first = false;
                index = i;
                continue;
            }
            ret = false;
            break;
        }
        else {
            prev = array[i];
        }
    }
    
    return ret;
}

void arrayDeleteItem(int *array, int index, int size) {
    for(int i = index; i < size - 1 ; i++) {
        array[i] = array[i + 1];
    }
    array[size] = -1505050;
}