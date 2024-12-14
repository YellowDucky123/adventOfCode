#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define H -5
#define V -4

int mapWidth(FILE* fp);
int mapLength(FILE* fp);
int dfs(char** map, int width, int length);
void dfsRec(char** map, bool** visited, int** fenceMapHorizontal, int** fenceMapVertical, int vRow, int vCol, int width, int length, char plot, int* plotCount);
int neighbours(char** map, int nghbir[4][3], int vRow, int vCol, int width, int length);
void mapScan(FILE* fp, char** map, int width, int length);
int fenceSides(int** fenceMapHorizontal, int** fenceMapVertical, int width, int length);

int main(int argc, char *argv[]) {

    FILE* fp = stdin;

    int width = mapWidth(fp);
    int length = mapLength(fp);

    char** map = malloc(length * sizeof(char*));
    for(int i = 0; i < length; i++) {
        map[i] = malloc(width * sizeof(char));
    }

    mapScan(fp, map, width, length);

    int cost = dfs(map, width, length);

    printf("\nfence costs %d\n\n", cost);

    for(int i = 0; i < length; i++) {
        free(map[i]);
    }
    free(map);

    return 0;
}

int dfs(char** map, int width, int length) {
    bool** visited = malloc(length * sizeof(bool*));
    for(int i = 0; i < length; i++) {
        visited[i] = calloc(width, sizeof(bool));
    }

    int cost = 0;

    for(int i = 0; i < length; i++) {
        for(int j = 0; j < width; j++) {
            if(visited[i][j]) continue;

            int** fenceMapHorizontal = malloc((length + 2) * sizeof(int*)); // make horizontal map
            for(int i = 0; i < length + 2; i++) {
                fenceMapHorizontal[i] = calloc((width + 2), sizeof(int));
            }

            int** fenceMapVertical = malloc((length + 2) * sizeof(int*));   // make vertical map
            for(int i = 0; i < length + 2; i++) {
                fenceMapVertical[i] = calloc((width + 2), sizeof(int));
            }

            int plotCount = 0;
            dfsRec(map, visited, fenceMapHorizontal, fenceMapVertical, i, j, width, length, map[i][j], &plotCount);

            // for(int i = 0; i < length + 2; i++) {
            //     for(int j = 0; j < width + 2; j++) {
            //         if(fenceMapHorizontal[i][j] > 0) printf("%d ", fenceMapHorizontal[i][j]);
            //         if(fenceMapVertical[i][j] > 0) printf("%d ", fenceMapVertical[i][j]);
            //         else printf(". ");
            //     }
            //     printf("i  is %d", i);
            //     printf("\n");
            // }
            // printf("\n\n\n");
    
            
            int fenceSide = fenceSides(fenceMapHorizontal, fenceMapVertical, width + 2, length + 2);
            printf("\nfence sides: %d\nplot count: %d\n", fenceSide, plotCount);

            for(int i = 0; i < length + 2; i++) {   //free memory
                free(fenceMapHorizontal[i]);
            }
            free(fenceMapHorizontal);

            for(int i = 0; i < length + 2; i++) {   //free memory
                free(fenceMapVertical[i]);
            }
            free(fenceMapVertical);

            cost += fenceSide * plotCount;
        }
    }

    for(int i = 0; i < length; i++) {
        free(visited[i]);
    }
    free(visited);

    return cost;
}

int fenceSides(int** fenceMapHorizontal, int** fenceMapVertical, int width, int length) {
    int sides = 0;

    for(int i = 0; i < length; i++) {
        for(int j = 0; j < width; j++) {
            bool moreThanOne = false;
            if(fenceMapHorizontal[i][j] > 0) {
                sides++;
                // printf("plus side\n");
                while(j < width && fenceMapHorizontal[i][j] > 0) {
                    if(fenceMapHorizontal[i][j] > 1) {
                        moreThanOne = true;
                    }
                    fenceMapHorizontal[i][j]--;
                    j++;
                }
                
                if(moreThanOne) {
                    i--;
                }
            }
        }
    }

    for(int i = 0; i < width; i++) {
        for(int j = 0; j < length; j++) {
            bool moreThanOne = false;
            if(fenceMapVertical[j][i] > 0) {
                sides++;
                // printf("plus side\n");
                while(j < length && fenceMapVertical[j][i] > 0) {
                    if(fenceMapVertical[j][i] > 1) {
                        moreThanOne = true;
                    }
                    fenceMapVertical[j][i]--;
                    j++;
                }

                if(moreThanOne) {
                    i--;
                }
            }
        }
    }

    return sides;
}

void dfsRec(char** map, bool** visited, int** fenceMapHorizontal, int** fenceMapVertical, int vRow, int vCol, int width, int length, char plot, int* plotCount) {
    *plotCount = *plotCount + 1;
    
    visited[vRow][vCol] = true;

    int nghbir[4][3];
    int size = neighbours(map, nghbir, vRow, vCol, width, length);

    for(int i = 0; i < size; i++) {
        if(nghbir[i][0] < 0 || nghbir[i][1] < 0 || nghbir[i][0] >= length || nghbir[i][1] >= width) {
            if(nghbir[i][2] == H) {
                ++fenceMapHorizontal[nghbir[i][0] + 1][nghbir[i][1] + 1];
            }
            else {
                ++fenceMapVertical[nghbir[i][0] + 1][nghbir[i][1] + 1];
            }

            continue;
        }
        else if(map[nghbir[i][0]][nghbir[i][1]] != plot) {
            if(nghbir[i][2] == H) {
                ++fenceMapHorizontal[nghbir[i][0] + 1][nghbir[i][1] + 1];
            }
            else {
                ++fenceMapVertical[nghbir[i][0] + 1][nghbir[i][1] + 1];
            }

            continue;
        }
        else if(visited[nghbir[i][0]][nghbir[i][1]]) {
            continue;
        }

        dfsRec(map, visited, fenceMapHorizontal, fenceMapVertical, nghbir[i][0], nghbir[i][1], width, length, plot, plotCount);
    }
}

int neighbours(char** map, int nghbir[4][3], int vRow, int vCol, int width, int length) {
    int directions[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};
    
    int size = 0;
    for(int i = 0; i < 4; i++) { 
        nghbir[i][0] = vRow + directions[i][0];
        nghbir[i][1] = vCol + directions[i][1];

        if(i >= 2) {
            nghbir[i][2] = V;
        }
        else {
            nghbir[i][2] = H;
        }
                
        size++;
    }

    return size;
}

void mapScan(FILE* fp, char** map, int width, int length) {
    char *str = malloc((width + 3) * sizeof(char));
    int level = 0;
    while(fgets(str, width + 3, fp)) {
        for(int i = 0; i < width; i++) {
            map[level][i] = str[i];
        }
        level++;
    }
    free(str);
}

int mapWidth(FILE* fp) {
    char str[1000];
    fgets(str, 1000, fp);
    fseek(fp, 0, SEEK_SET);

    return strlen(str) - 1;
}

int mapLength(FILE* fp) {
    char str[500];
    int count = 0;
    while(fgets(str, 500, fp)) {
        count++;
    }
    fseek(fp, 0, SEEK_SET);

    return count;
}