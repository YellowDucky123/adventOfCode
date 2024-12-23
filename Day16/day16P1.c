#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

int mapLength(FILE* fp);
int mapWidth(FILE* fp);
void dfs(char** map, int* src, int dest[2], char orient, int sumPoint, int* points, int** visited, int length, int width);
void neighbours(int xV, int yV, int nghbir[4][2]);
void scanMap(FILE* fp, char** map, int start[2], int dest[2]);

int main(int argc, char* argv[]) {
    FILE* fp = stdin;

    int length = mapLength(fp);
    int width = mapWidth(fp);

    char** map = malloc(length * sizeof(char*));
    for(int i = 0; i < length; i++) {
        map[i] = malloc(width * sizeof(char));
    }

    int start[2];
    int dest[2];
    scanMap(fp, map, start, dest);

    int** visited = malloc(length * sizeof(int*));
    for(int i = 0; i < length; i++) {
        visited[i] = calloc(width, sizeof(int));
    }
    int points = INT_MAX;
    dfs(map, start, dest, 'S', 0, &points, visited, length, width);

    printf("least points is %d\n", points);

    for(int i = 0; i < length; i++) {
        free(visited[i]);
    }
    free(visited);

    for(int i = 0; i < length; i++) {
        free(map[i]);
    }
    free(map);

    return 0;
}
void dfs(char** map, int* src, int dest[2], char orient, int sumPoint, int* points, int** visited, int length, int width) {
    
    
    // Check boundaries and visited status
    if (src[0] < 0 || src[1] < 0 || src[0] >= length || src[1] >= width || visited[src[0]][src[1]]) {
        return;
    }

    // Mark the position as visited
    visited[src[0]][src[1]] = 1;

    // Destination reached
    if (map[src[0]][src[1]] == 'E') {
        if (sumPoint < *points) {
            // printf("sumPoinsts %d, %d\n", sumPoint, *points);

            *points = sumPoint;
        }
        visited[src[0]][src[1]] = 0; // Unmark before returning
        return;
    }

    int nghbir[4][2];
    neighbours(src[0], src[1], nghbir);

    for (int i = 0; i < 4; i++) {
        int nextSrc[2] = {nghbir[i][0], nghbir[i][1]};

        if (map[nextSrc[0]][nextSrc[1]] == '#') {
            continue; // Skip walls
        }

        int tmpPoint = sumPoint + 1;
        char nextOrient = orient;
        // printf("orient %c|| %d, %d\n", orient, src[0],src[1]);
        // printf("nextSrc %d,%d\n", nextSrc[0],nextSrc[1]);
        if (i == 0) {
            if (orient != '>') tmpPoint += 1000;
            nextOrient = '>';
        } else if (i == 1) {
            if (orient != '<') tmpPoint += 1000;
            nextOrient = '<';
        } else if (i == 2) {
            if (orient != 'v') tmpPoint += 1000;
            nextOrient = 'v';
        } else {
            if (orient != '^') tmpPoint += 1000;
            nextOrient = '^';
        }

        dfs(map, nextSrc, dest, nextOrient, tmpPoint, points, visited, length, width);
    }

    // Unmark the position before backtracking
    visited[src[0]][src[1]] = 0;
}


void neighbours(int xV, int yV, int nghbir[4][2]) {
    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    for(int i = 0; i < 4; i++) {
        int newY = yV + directions[i][1];
        int newX = xV + directions[i][0];

        nghbir[i][1] = newY;
        nghbir[i][0] = newX;
    }
}

void scanMap(FILE* fp, char** map, int start[2], int dest[2]) {
    char str[200];
    for(int i = 0; fgets(str, 200, fp); i++) {
        for(int j = 0; j < strlen(str); j++) {
            map[i][j] = str[j];
            if(map[i][j] == 'S') {
                start[0] = i;
                start[1] = j;
            }
            else if(map[i][j] == 'E') {
                dest[0] = i;
                dest[1] = j;
            }
        }
    }
} 

int mapLength(FILE* fp) {
    int length = 0;
    char str[200];
    while(fgets(str, 200, fp)) {
        length++;
    }
    fseek(fp, 0, SEEK_SET);

    return length;
}

int mapWidth(FILE* fp) {
    char str[200];
    fgets(str, 200, fp);
    fseek(fp, 0, SEEK_SET);

    return strlen(str);
}