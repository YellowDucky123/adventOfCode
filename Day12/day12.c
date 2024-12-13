#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
int mapWidth(FILE* fp);
int mapLength(FILE* fp);
int dfs(char** map, int width, int length);
int dfsRec(char** map, bool** visited, int vRow, int vCol, int width, int length, char plot, int* plotCount);
int neighbours(char** map, int nghbir[4][2], int vRow, int vCol, int width, int length);
void mapScan(FILE* fp, char** map, int width, int length);

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

            int plotCount = 0;
            int fenceSide = dfsRec(map, visited, i, j, width, length, map[i][j], &plotCount);
            
            cost += fenceSide * plotCount;
        }
    }

    for(int i = 0; i < length; i++) {
        free(visited[i]);
    }
    free(visited);

    return cost;
}

int dfsRec(char** map, bool** visited, int vRow, int vCol, int width, int length, char plot, int* plotCount) {
    *plotCount = *plotCount + 1;
    
    visited[vRow][vCol] = true;

    int nghbir[4][2];
    int size = neighbours(map, nghbir, vRow, vCol, width, length);
    int fenceSide = 0;
    for(int i = 0; i < size; i++) {
        if(nghbir[i][0] < 0 || nghbir[i][1] < 0 || nghbir[i][0] >= length || nghbir[i][1] >= width) {
            fenceSide++;
            continue;
        }
        else if(map[nghbir[i][0]][nghbir[i][1]] != plot) {
            fenceSide++;
            continue;
        }
        else if(visited[nghbir[i][0]][nghbir[i][1]]) {
            continue;
        }

        fenceSide += dfsRec(map, visited, nghbir[i][0], nghbir[i][1], width, length, plot, plotCount);
    }

    return fenceSide;
}

int neighbours(char** map, int nghbir[4][2], int vRow, int vCol, int width, int length) {
    int directions[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};
    
    int size = 0;
    for(int i = 0; i < 4; i++) { 
        nghbir[i][0] = vRow + directions[i][0];
        nghbir[i][1] = vCol + directions[i][1];
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