#include <iostream>
#include <cmath>
using namespace std;

int A[5][4];
double ratios[4][4];

int main() {
    string str;
    for (int i = 0; i < 5; i++) {
        cin >> str;
        if (str == "_") A[i][0] = 0;
        else A[i][0] = stoi(str);
        cin >> str;
        if (str == "_") A[i][1] = 0;
        else A[i][1] = stoi(str);
    }
    for (int i = 0; i < 5; i++) {
        cin >> str;
        if (str == "_") A[i][2] = 0;
        else A[i][2] = stoi(str);
        cin >> str;
        if (str == "_") A[i][3] = 0;
        else A[i][3] = stoi(str);
    }
    // Determine ratios
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                if (A[i][j] != 0 && A[i][k] != 0) {
                    ratios[j][k] = (double) A[i][k] / A[i][j];
                }
            }
        }
    }
    // Fill all ratios
    for (int k = 0; k < 4; k++) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (ratios[i][k] != 0 && ratios[k][j] != 0) {
                    ratios[i][j] = ratios[i][k] * ratios[k][j];
                }
            }
        }
    }
    // for (int i = 0; i < 4; i++) {
    //     for (int j = 0; j < 4; j++) cout << ratios[i][j] << ' ';
    //     cout << endl;
    // }
    // Fill plates
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                if (A[i][k] != 0) {
                    A[i][j] = round(A[i][k] * ratios[k][j]);
                }
            }
        }
    }
    // Print out plates
    for (int i = 0; i < 5; i++) {
        if (i != 0) cout << ' ';
        cout << A[i][0] << ' ' << A[i][1];
    }
    cout << endl;
    for (int i = 0; i < 5; i++) {
        if (i != 0) cout << ' ';
        cout << A[i][2] << ' ' << A[i][3];
    }
    cout << endl;
    return 0;
}