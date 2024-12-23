#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include <limits.h>

using namespace std;

void byteFallSimulation(char** grid, ifstream& fp);
int shortestPath(char** grid);
int dijktras(char** grid);
void minDistance(int distance[7][7], bool sptV[7][7], int *v);
void byteFallSimulation(char** grid, ifstream& fp);

int main() {
    ifstream fp("input.txt");
    char** grid = new char*[7];
    for(int i = 0; i < 7; i++) {
        grid[i] = new char[7];
    }
    for(int i = 0; i < 7; i++) {
        for(int j = 0; j < 7; j++) {
            grid[i][j] = '.';
        }
    }
    for(int i = 0; i < 7; i++) {
        for(int j = 0; j < 7; j++) {
            cout << grid[i][j];
        }
        cout <<endl;
    }
    cout <<endl;
    byteFallSimulation(grid, fp);
    for(int i = 0; i < 7; i++) {
        for(int j = 0; j < 7; j++) {
            cout << grid[i][j];
        }
        cout <<endl;
    }

    int shortest = shortestPath(grid);
    cout << "shortest path is " << shortest << endl;

    for(int i = 0; i < 7; i++) {
        delete grid[i];
    }
    delete grid;
}

int shortestPath(char** grid) {
    int** visited = new int*[7];
    for(int i = 0; i < 7; i++) {
        visited[i] = new int[7];
    }
    for(int j = 0; j < 7; j++) {
        for(int i = 0; i < 7; i++) {
            visited[j][i] = 0;
        }
    }

    int shortest = dijktras(grid);
    cout << "out\n";
    for(int i = 0; i < 7; i++) {
        delete visited[i];
    }
    delete visited;

    return shortest;
}

int dijktras(char** grid) {
    int distance[7][7];
    bool sptV[7][7];
    for(int i = 0; i < 7; i++) {
        for(int j = 0; j < 7; j++) {
            distance[i][j] = INT16_MAX;
            sptV[i][j] = false;
        }
    }

    distance[0][0] = 0;

    for(int i = 0; i < 7; i++) {
        for(int j = 0; j < 7; j++) {
            int v[2];
            minDistance(distance, sptV, v);
            sptV[v[1]][v[0]] = true;

            int direction[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
            for(int i = 0; i < 4; i++) {
                int newX = v[0] + direction[i][0];
                int newY = v[1] + direction[i][1];
                if(newX > 6 || newX < 0 || newY > 6 || newY < 0 || grid[newY][newX] == '#') continue;
                
                if(distance[newY][newX] > distance[v[1]][v[0]] + 1) {
                    distance[newY][newX] = distance[v[1]][v[0]] + 1;
                }
            }
        }
    }

    return distance[6][6];
}

void minDistance(int distance[7][7], bool sptV[7][7], int v[2]) {
    int min = INT16_MAX;
    for(int i = 0; i < 7; i++) {
        for(int j = 0; j < 7; j++) {
            if(distance[i][j] < min && !sptV[i][j]) {
                min = distance[i][j];
                v[0] = j;
                v[1] = i;
            }
        }
    }
}

void byteFallSimulation(char** grid, ifstream& fp) {
    for(int i = 0; i < 12; i++) {
        string str;
        getline(fp, str);
        stringstream ss(str);
        int x, y;
        ss >> x;
        ss.ignore(1, ',');
        ss >> y;

        grid[y][x] = '#';
    }
}




