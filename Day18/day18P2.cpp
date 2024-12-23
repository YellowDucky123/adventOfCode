#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include <limits.h>
#include <queue>

using namespace std;

void byteFallSimulation(char** grid, ifstream& fp);
int* earliestCoord(char** grid, ifstream& fp);
bool bfs(char** grid);
void byteFallSimulation(char** grid, ifstream& fp);


int main() {
    ifstream fp("input.txt");
    char** grid = new char*[71];
    for(int i = 0; i < 71; i++) {
        grid[i] = new char[71];
    }
    for(int i = 0; i < 71; i++) {
        for(int j = 0; j < 71; j++) {
            grid[i][j] = '.';
        }
    }
    for(int i = 0; i < 71; i++) {
        for(int j = 0; j < 71; j++) {
            cout << grid[i][j];
        }
        cout <<endl;
    }
    cout <<endl;
    byteFallSimulation(grid, fp);
    for(int i = 0; i < 71; i++) {
        for(int j = 0; j < 71; j++) {
            cout << grid[i][j];
        }
        cout <<endl;
    }

    int* coord = earliestCoord(grid, fp);

    cout << "earliest coordinate is: " << coord[0] << ',' << coord[1] << endl;

    for(int i = 0; i < 71; i++) {
        delete grid[i];
    }
    delete grid;
}

int* earliestCoord(char** grid, ifstream& fp) {
    int x, y;
    while(bfs(grid)) {
        for(int i = 0; i < 71; i++) {
            for(int j = 0; j < 71; j++) {
                cout << grid[i][j];
            }
            cout <<endl;
        }
        string str;
        getline(fp, str);
        stringstream ss(str);
        ss >> x;
        ss.ignore(1, ',');
        ss >> y;
        grid[y][x] = '#';
    }
    int* ret = new int[2];
    ret[0] = x;
    ret[1] = y;
    return ret;
}

bool bfs(char** grid) {
    bool** visited = new bool*[71];
    for(int i = 0; i < 71; i++) {
        visited[i] = new bool[71];
    }

    for(int i = 0; i < 71; i++) {
        for(int j = 0; j < 71; j++) {
            visited[i][j] = false;
        }
    }

    queue<pair<int, int>> q;
    q.push({0, 0});
    visited[0][0] = true;

    while(!q.empty()) {
        pair<int, int> ver = q.front();
        q.pop();
        int verX = ver.first, verY = ver.second;

        if(verX == 70 && verY == 70) {
            return true;
        }

        int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        for(int i = 0; i < 4; i++) {
            int newX = verX + directions[i][0];
            int newY = verY + directions[i][1];
            if(newX > 70 || newX < 0 || newY > 70 || newY < 0 || grid[newY][newX] == '#' || visited[newY][newX]) continue;

            q.push({newX, newY});
            visited[newY][newX] = true;
        }
    }

    return false;
}

void byteFallSimulation(char** grid, ifstream& fp) {
    for(int i = 0; i < 1024; i++) {
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




