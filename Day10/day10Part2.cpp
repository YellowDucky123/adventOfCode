#include <iostream>
#include <queue>
#include <vector>
#include <fstream>

using namespace std;
class myClass {
    public:
        int row;
        int col;
};

int gridWidth(ifstream& fp);
int gridLength(ifstream &fp);
void gridScan(int** grid, ifstream& fp);
void DFSRec(int** grid, myClass src, int length, int width, int *count);
vector<myClass> neighbours(myClass v, int length, int width);

int main() {
    ifstream fp("input.txt");

    int length = gridLength(fp);
    int width = gridWidth(fp);
    
    int** grid = new int*[length];
    for(int i = 0; i < length; i++) {
        grid[i] = new int[width];
    }

    gridScan(grid, fp);
    for(int i = 0; i < length; i++) {
        for(int j = 0; j < width; j++) {
            if(grid[i][j] == -2) {
                cout << ". "; 
            }
            else cout << grid[i][j] << " ";
        }
        cout << endl;
    }

    int sum = 0;
    
    for(int i = 0; i < length; i++) {
        for(int j = 0; j < width; j++) {
            if(grid[i][j] == 0) {
                int count = 0;
                DFSRec(grid, {i, j}, length, width, &count);
                sum += count;
            }
        }
    }

    cout << endl << "sum of hike rating is " << sum << endl << endl;

    for (int i = 0; i < length; ++i)
        delete [] grid[i];
    delete [] grid;
}

void gridScan(int** grid, ifstream& fp) {
    string str;
    int level = 0;
    while(getline(fp, str)) {
        for(int i = 0; i < str.length(); i++) {
            grid[level][i] = str[i] - '0';
        }
        level++;
    }
}

void DFSRec(int** grid, myClass src, int length, int width, int *count){
    if(grid[src.row][src.col] == 9) {
        *count = *count + 1;;
        return;
    }
    // Recursively visit all adjacent vertices
    // that are not visited yet
    vector<myClass> nghbir = neighbours(src, length, width);
    for(const myClass& it : nghbir) {
        if((grid[it.row][it.col] - grid[src.row][src.col]) > 1 ||
            (grid[it.row][it.col] - grid[src.row][src.col]) == 0 || 
            (grid[it.row][it.col] - grid[src.row][src.col]) < 0
        ) {
            continue;
        }
        DFSRec(grid, it, length, width, count);
    }
}

vector<myClass> neighbours(myClass v, int length, int width) {
    vector<myClass> n;

    myClass n1;
    n1.row = v.row - 1;
    n1.col = v.col;
    if(n1.row >= 0) n.push_back(n1);

    myClass n2;
    n2.row = v.row;
    n2.col = v.col - 1;
    if(n2.col >= 0) n.push_back(n2);

    myClass n3;
    n3.row = v.row + 1;
    n3.col = v.col;
    if(n3.row < length) n.push_back(n3);

    myClass n4;
    n4.row = v.row;
    n4.col = v.col + 1;
    if(n4.col < width) n.push_back(n4);

    return n;
}

int gridWidth(ifstream& fp) {
    string str;
    getline(fp, str);
    int width = str.length();
    fp.clear();
    fp.seekg(0, ios::beg); // Restore position
    return width;
}

int gridLength(ifstream &fp) {
    string str;
    int count = 0;
    while(getline(fp, str)) {
        count++;
    }
    fp.clear();
    fp.seekg(0, ios::beg); // Restore position
    return count;
}