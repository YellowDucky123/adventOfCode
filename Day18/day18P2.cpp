#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include <limits.h>
#include <queue>

using namespace std;

class myClass {
    public:
        int x;
        int y;
};

void byteFallSimulation(char** grid, ifstream& fp);
int* earliestCoord(char** grid, ifstream& fp);
bool bfs(char** grid);
void byteFallSimulation(char** grid, ifstream& fp);
int dijktras(char** grid);
void minDistance(int distance[71][71], bool sptV[71][71], int v[2]);

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
    while(dijktras(grid) != INT16_MAX) {
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


int dijktras(char** grid) {
    int distance[71][71];
    bool sptV[71][71];
    for(int i = 0; i < 71; i++) {
        for(int j = 0; j < 71; j++) {
            distance[i][j] = INT16_MAX;
            sptV[i][j] = false;
        }
    }

    distance[0][0] = 0;

    for(int i = 0; i < 71; i++) {
        for(int j = 0; j < 71; j++) {
            int v[2];
            minDistance(distance, sptV, v);
            sptV[v[1]][v[0]] = true;

            int direction[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
            for(int i = 0; i < 4; i++) {
                int newX = v[0] + direction[i][0];
                int newY = v[1] + direction[i][1];
                if(newX > 70 || newX < 0 || newY > 70 || newY < 0 || grid[newY][newX] == '#') continue;
                
                if(distance[newY][newX] > distance[v[1]][v[0]] + 1) {
                    distance[newY][newX] = distance[v[1]][v[0]] + 1;
                }
            }
        }
    }

    return distance[70][70];
}

void minDistance(int distance[71][71], bool sptV[71][71], int v[2]) {
    int min = INT16_MAX;
    for(int i = 0; i < 71; i++) {
        for(int j = 0; j < 71; j++) {
            if(distance[i][j] < min && !sptV[i][j]) {
                min = distance[i][j];
                v[0] = j;
                v[1] = i;
            }
        }
    }
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

    queue<myClass> q;
    myClass v;
    v.x = 0;
    v.y = 0;
    q.push(v);
    visited[0][0] = true;

    while(!q.empty()) {
        myClass ver = q.front();
        q.pop();

        if(ver.x == 70 && ver.y == 70) {
            return true;
        }

        int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        for(int i = 0; i < 4; i++) {
            int newX = ver.x + directions[i][0];
            int newY = ver.y + directions[i][1];
            if(newX > 70 || newX < 0 || newY > 70 || newY < 0 || grid[newY][newX] == '#' || visited[newY][newX]) continue;

            myClass tmp;
            tmp.x = newX;
            tmp.y = newY;
            q.push(tmp);
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




