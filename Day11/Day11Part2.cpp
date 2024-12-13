// not finished

#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

typedef long long int INT;

using namespace std;

void stoneReplace(vector<INT>& stones); 
void divideStone(INT& stone, vector<INT>& stones, int i);
int numberOfDigits(INT stone);
vector<INT> scanStones(ifstream& fp);

int main() {
    ifstream fp("input.txt");

    vector<INT> stones = scanStones(fp);

    int blink;
    cout << "blink amount: " << endl;
    cin >> blink;

    for(int i = 0; i < blink; i++) {
        stoneReplace(stones);
    }

    cout << "there are " << stones.size() << " stones" << endl;
}

void stoneReplace(vector<INT>& stones) {
    for(int i = 0; i < stones.size(); i++) {
        if(stones[i] == 0) {
            stones[i] = 1;
        }
        else if(numberOfDigits(stones[i]) % 2 == 0) {
            divideStone(stones[i], stones, i);
            i++;
        }
        else {
            stones[i] = stones[i] * 2024;
        }
    }
}

void divideStone(INT& stone, vector<INT>& stones, int i) {
    string s = to_string(stone);

    int divider = 1;
    for(int i = 0; i < s.length() / 2; i++) {
        divider *= 10;
    }

    INT secondStone = stone % divider;
    INT firstStone = stone / divider;
    stone = firstStone;
    stones.emplace(stones.begin() + i + 1, secondStone);
    
    // cout<<endl<<"stone is "<<stone<<endl;
}

int numberOfDigits(INT stone) {
    string s = to_string(stone);
    return s.length();
}

vector<INT> scanStones(ifstream& fp) {
    vector<INT> v;

    string str;
    getline(fp, str);

    stringstream ss(str);
    string s;
    while(getline(ss, s, ' ')) {
        INT tmp = stoi(s);
        v.push_back(tmp);
    }

    return v;
}


