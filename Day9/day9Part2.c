#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define FILE_MAX 20000

int scanDisk(FILE* fp, char *disk);
int numberedDisk(char* disk, int size, int* numDisk);
long long int checksum(int *numDisk, int size);
void compactDisk(int *numDisk, int size);
void moveFile(int *numDisk, int size, int index);
void movingFileBlock(int *numDisk, int size, int fileIndex, int fileBlock);
int leftMostEmpty(int *numDisk, int size, int fileIndex, int fileSize);

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
    // for(int i = 0; i < amount; i++) {
    //     if(numDisk[i] == -1) {
    //         printf(".");
    //     }
    //     else {
    //         printf("%d",numDisk[i]);
    //     }
    // }
    // printf("\n");
    compactDisk(numDisk, amount);
    // for(int i = 0; i < amount; i++) {
    //     if(numDisk[i] == -1) {
    //         printf(".");
    //     }
    //     else {
    //         printf("%d",numDisk[i]);
    //     }
    // }
    // printf("\n");
    printf("\nchecksum is %lld\n\n", checksum(numDisk, amount));

    free(numDisk);
    return 0;
}

long long int checksum(int *numDisk, int size) {
    int numInc = 0;
    long long int sum = 0;
    for(int i = 0; i < size; i++) {
        if(numDisk[i] != -1) {
            sum += numInc * numDisk[i];
        }
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

void compactDisk(int *numDisk, int size) {
    int endIndex = size - 1;
    for(int i = endIndex; i >= 0; i--) {
        if(numDisk[i] != -1) {
            int fileId = numDisk[i];
            while(numDisk[i] == fileId) {
                i--;
                if(i < 0) break;
            }
            i++;
            moveFile(numDisk, size, i);
        }
    }
}

void moveFile(int *numDisk, int size, int index) {
    int fileBlock = 0;
    int fileId = numDisk[index];
    for(int i = index; numDisk[i] == fileId; i++) {
        fileBlock++;
    }
    movingFileBlock(numDisk, size, index, fileBlock);
} 

void movingFileBlock(int *numDisk, int size, int fileIndex, int fileBlock) {
    int emptySpot = leftMostEmpty(numDisk, size, fileIndex, fileBlock);
    if(emptySpot == -1) {
        return;
    }

    int fileId = numDisk[fileIndex];
    for(int it = 0; it < fileBlock; it++) {
        if(numDisk[fileIndex] != fileId) {
            printf("went over the file\n");
            return;
        }
        if(numDisk[emptySpot] != -1) {
            printf("went over empty slot\n");
            return;
        }

        numDisk[emptySpot] = numDisk[fileIndex];
        numDisk[fileIndex] = -1;
        emptySpot++;
        fileIndex++;
    }
}

int leftMostEmpty(int *numDisk, int size, int fileIndex, int fileSize) {
    int i = 0;
    while(i < fileIndex) {
        if(numDisk[i] == -1) {
            int indexSave = i;
            int count = 0;
            while(numDisk[i] == -1) {
                count++;
                i++;
            }
            if(count >= fileSize) {
                return indexSave;
            }
        }
        else {
            i++;
        }
    }
    return -1;
}