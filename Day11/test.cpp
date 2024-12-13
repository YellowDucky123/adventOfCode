#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> v = {1, 2 , 3, 4};

    for(int i = 0; i < v.size(); i++) {
        if(v[i] == 1) {
            v[i] = 10;
        }
        else if(v[i] == 2) {
            v[i] = 9;
            v.emplace(v.begin() + i + 1, 8);
        }
    }

    for(int i : v) {
        cout << i << endl;
    }
}