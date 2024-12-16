#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include <unistd.h>

class myClass {
    public:
        int x;
        int y;
};

int gridLength(std::ifstream& fp);
int gridWidth(std::ifstream& fp);
void scanGrid(std::ifstream& fp, char** grid, int length, int width);
void moveBotFunc(std::ifstream& fp, char** grid, int length, int width, myClass& botPos);
void moveBot(char** grid, myClass& botPos, char move);
myClass botPosition(char** grid, int length, int width);
int GPScoordinateSum(char** grid, int length, int width);

int main() {
    std::ifstream fp("input.txt");
    int length = gridLength(fp);
    int width = gridWidth(fp);

    char** grid = new char*[length];
    for(int i = 0; i < length; i++) {
        grid[i] = new char[width];
    }

    scanGrid(fp, grid, length, width);

    std::string str;
    std::getline(fp, str); // eat up empty line

    myClass botPos = botPosition(grid, length, width);

    // // bot grid picture
    // for(int i = 0; i < length; i++) {
    //     for(int j = 0; j < width; j++) {
    //         std::cout<<grid[i][j];
    //     }
    //     std::cout<<std::endl;
    // }

    moveBotFunc(fp, grid, length, width, botPos);

    std::cout << "sum of coordinates are " << GPScoordinateSum(grid, length, width) << std::endl;
}   
int GPScoordinateSum(char** grid, int length, int width) {
    int sum = 0;
    for(int i = 0; i < length; i++) {
        for(int j = 0; j < width; j++) {
            if(grid[i][j] == 'O') {
                sum += ((100 * i) + j);
            }
        }
    }

    return sum;
}

myClass botPosition(char** grid, int length, int width) {
    myClass botPos;
    for(int i = 0; i < length; i++) {
        for(int j = 0; j < width; j++) {
            if(grid[i][j] == '@') {
                botPos.x = j;
                botPos.y = i;
            }
        }
    }
    return botPos;
}

void moveBotFunc(std::ifstream& fp, char** grid, int length, int width, myClass& botPos) {
    std::string str;
    while(getline(fp, str)) {
        for(int i = 0; i < str.length(); i++) {
            moveBot(grid, botPos, str[i]);


            // //////////////
            // sleep(1);
            // system("clear");
            // // bot grid picture
            // for(int i = 0; i < length; i++) {
            //     for(int j = 0; j < width; j++) {
            //         std::cout<<grid[i][j];
            //     }
            //     std::cout<<std::endl;
            // }
            // //////////
        }
    }
}

void moveBot(char** grid, myClass& botPos, char move) {
    if (move == '>') {
        int nPosX = botPos.x + 1;

        if(grid[botPos.y][nPosX] == '#') {
            return;
        }

        int tmp = 0;
        if(grid[botPos.y][nPosX] == 'O') {
            while(grid[botPos.y][nPosX + tmp] == 'O') {
                tmp++;
            }
            if(grid[botPos.y][nPosX + tmp] == '#') {
                return;
            }
        }

        for(int i = nPosX + tmp; i >= nPosX; i--) {
            grid[botPos.y][i] = grid[botPos.y][i - 1];
        }
        grid[botPos.y][botPos.x] = '.';
        botPos.x = nPosX;
    }
    else if (move == '<') {
        int nPosX = botPos.x - 1;

        if(grid[botPos.y][nPosX] == '#') {
            return;
        }

        int tmp = 0;
        if(grid[botPos.y][nPosX] == 'O') {
            while(grid[botPos.y][nPosX - tmp] == 'O') {
                tmp++;
            }
            if(grid[botPos.y][nPosX - tmp] == '#') {
                return;
            }
        }

        for(int i = nPosX - tmp; i <= nPosX; i++) {
            grid[botPos.y][i] = grid[botPos.y][i + 1];
        }
        grid[botPos.y][botPos.x] = '.';
        botPos.x = nPosX;
    }
    else if (move == 'v') {
        int nPosY = botPos.y + 1;

        if(grid[nPosY][botPos.x] == '#') {
            return;
        }

        int tmp = 0;
        if(grid[nPosY][botPos.x] == 'O') {
            while(grid[nPosY + tmp][botPos.x] == 'O') {
                tmp++;
            }
            if(grid[nPosY + tmp][botPos.x] == '#') {
                return;
            }
        }

        for(int i = nPosY + tmp; i >= nPosY; i--) {
            grid[i][botPos.x] = grid[i - 1][botPos.x];
        }
        grid[botPos.y][botPos.x] = '.';
        botPos.y = nPosY;
    }
    else {
        int nPosY = botPos.y - 1;

        if(grid[nPosY][botPos.x] == '#') {
            return;
        }

        int tmp = 0;
        if(grid[nPosY][botPos.x] == 'O') {
            while(grid[nPosY - tmp][botPos.x] == 'O') {
                tmp++;
            }
            if(grid[nPosY - tmp][botPos.x] == '#') {
                return;
            }
        }

        for(int i = nPosY - tmp; i <= nPosY; i++) {
            grid[i][botPos.x] = grid[i + 1][botPos.x];
        }
        grid[botPos.y][botPos.x] = '.';
        botPos.y = nPosY;
    }
}


void scanGrid(std::ifstream& fp, char** grid, int length, int width) {
    for(int i = 0; i < length; i++) {
        std::string str;
        std::getline(fp, str);

        for(int j = 0; j < width; j++) {
            grid[i][j] = str[j];
        }
    }
    
}

int gridLength(std::ifstream& fp) {
    int count = 0;
    std::string str;
    while(std::getline(fp, str)) {
        if(str[0] != '#') {
            break;
        }

        count++;
    }

    fp.clear();
    fp.seekg(0, std::ios::beg);

    return count;
}

int gridWidth(std::ifstream& fp) {
    std::string str;
    std::getline(fp, str);

    fp.clear();
    fp.seekg(0, std::ios::beg);

    return str.length();
}