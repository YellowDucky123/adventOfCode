#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define FILE_MAX 20000

int scanDisk(FILE* fp, char *disk);
int numberedDisk(char* disk, int size, int* numDisk);
void compactDisk(int* numDisk, int size);
void moveToLeftmostGap(int* numDisk, int index, int lastGap);
int leftMostGap(int* numDisk, int currIndex);
long long int checksum(int *numDisk);
bool fullyCompacted(int *numDisk, int size);

int main() {
    FILE* fp = stdin;

    char disk[FILE_MAX];

    int size = scanDisk(fp, disk);
    if(size == -1) {
        perror("scan failed");
        return 0;
    }

    int *numDisk = malloc((size * 10) * sizeof(int));

    int amount = numberedDisk(disk, size, numDisk);

    compactDisk(numDisk, amount);

    printf("checksum is %lld\n", checksum(numDisk));

    free(numDisk);
    return 0;
}

long long int checksum(int *numDisk) {
    int numInc = 0;
    long long int sum = 0;
    for(int i = 0; numDisk[i] != -1; i++) {
        sum += numInc * numDisk[i];

        numInc++;
    }
    return sum;
}

int scanDisk(FILE* fp, char *disk) {
    if(!fscanf(fp, " %s", disk)) {
        return -1;
    }

    return strlen(disk);
}

int numberedDisk(char* disk, int size, int* numDisk) {
    int id = 0;
    int index = 0;
    bool file = true;
    for(int i = 0; i < size; i++) {
        int di = disk[i] - '0';
        for(int j = 0; j < di; j++) {
            
            if(file) {
                numDisk[index] = id;
            }
            else {
                numDisk[index] = -1;
            }
            index++;
        }

        if(file) {
            id++;
            file = false;
        }
        else {
            file = true;
        }
    }

    return index; 
}

void compactDisk(int* numDisk, int size) {
    int endIndex = size - 1;
    int lastGap = leftMostGap(numDisk, 0);

    for(int i = endIndex; !fullyCompacted(numDisk, size); i--) {
        if(numDisk[i] == -1) continue;

        moveToLeftmostGap(numDisk, i, lastGap);
        lastGap = leftMostGap(numDisk, lastGap);
    }
}

void moveToLeftmostGap(int* numDisk, int index, int lastGap) {
    if(numDisk[index] == -1) {
        perror("int is a '.' error");
        return;
    }

    numDisk[lastGap] = numDisk[index];
    numDisk[index] = -1;
}

int leftMostGap(int* numDisk, int currIndex) {
    int i = currIndex;
    for(; numDisk[i] != -1; i++) {} 

    return i;
}

bool fullyCompacted(int *numDisk, int size) {
    bool gap = false;
    for(int i = 0; i < size; i++) {
        if(numDisk[i] == -1) {
            gap = true;
        }
        if(gap && numDisk[i] != -1) {
            return false;
        }
    }

    return true;
}

