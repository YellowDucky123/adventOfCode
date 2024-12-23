#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <cmath>

using namespace std;

void scanFile(ifstream& fp, int& A, int& B, int& C, string& program);
void programFn(int& A, int& B, int& C, string program, vector<int>& out);
void initialise(int& A, int& B, int& C, int opcode, int operand, int& i, vector<int>& out);
int operandValue(int A, int B, int C, int operand);

int main() {
    ifstream fp("input.txt");
    int A, B, C;
    string program;
    vector<int> out;

    scanFile(fp, A, B, C, program);
    programFn(A, B, C, program, out);
    bool first = true;
    for(int i: out) {
        if(first) {
            cout << i;
            first = false;
        }
        else cout << ',' << i; 
    }
    cout << endl;
}

void programFn(int& A, int& B, int& C, string program, vector<int>& out) {
    int i = 0;
    while(i < program.length()) {
        int opcode, operand;
        for(int j = 0; j < 2; j++) {
            if(j == 0) {
                opcode = program[i] - '0';
                i += 2;
            }
            else {
                operand = program[i] - '0';
            }
        }
        
        initialise(A, B, C, opcode, operand, i, out);
    }
}

void initialise(int& A, int& B, int& C, int opcode, int operand, int& i, vector<int>& out) {
    // cout << opcode <<endl;
    if(opcode == 0) {
        A = A / pow(2,operandValue(A, B, C, operand));
    }
    else if(opcode == 1) {
        B = B ^ operand;
    }
    else if(opcode == 2) {
        B = operandValue(A, B, C, operand) % 8;
    }
    else if(opcode == 3) {
        if(A == 0) return;
        i = operand;
        return;
    }
    else if(opcode == 4) {
        B = B ^ C;
    }
    else if(opcode == 5) {
        // cout << "5\n";
        out.push_back(operandValue(A, B, C, operand) % 8);
        // cout << operandValue(A, B, C, operand) % 8;
    }
    else if(opcode == 6) {
        B = A / pow(2,operandValue(A, B, C, operand));
    }
    else if(opcode == 7) {
        C = A / pow(2,operandValue(A, B, C, operand));
    }
    i += 2;
}

int operandValue(int A, int B, int C, int operand) {
    if(operand == 4) {
        return A;
    }
    else if(operand == 5) {
        return B;
    }
    else if(operand == 6) {
        return C;
    }
    else {
        return operand;
    }
}

void scanFile(ifstream& fp, int& A, int& B, int& C, string& program) {
    string tmp1, tmp2;
    
    string strA;
    getline(fp, strA);
    stringstream ssA(strA);
    ssA >> tmp1; 
    ssA.ignore(1, ' ');
    ssA >> tmp2; 
    ssA.ignore(1, ' ');
    ssA >> A;

    string strB;
    getline(fp, strB);
    stringstream ssB(strB);
    ssB >> tmp1; 
    ssB.ignore(1, ' ');
    ssB >> tmp2; 
    ssB.ignore(1, ' ');
    ssB >> B;

    string strC;
    getline(fp, strC);
    stringstream ssC(strC);
    ssC >> tmp1; 
    ssC.ignore(1, ' ');
    ssC >> tmp2; 
    ssC.ignore(1, ' ');
    ssC >> C;

    string str;
    getline(fp, str); //eat empty line;
    getline(fp, str);
    stringstream ss(str);
    ss >> tmp1;
    ss >> program;
}