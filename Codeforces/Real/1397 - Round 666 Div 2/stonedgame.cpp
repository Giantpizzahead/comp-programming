#include <iostream>

using namespace std;

const int MAXN = 101;

bool winner[MAXN][MAXN][MAXN][3];

int main() {
    winner[0][0][0][0] = false;
    winner[0][0][0][1] = false;
    winner[0][0][0][2] = false;
    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < MAXN; j++) {
            for (int k = 0; k < MAXN; k++) {
                for (int l = 0; l < 3; l++) {
                    if (i != 0 && l != 0) {
                        winner[i][j][k][l] |= !winner[i-1][j][k][0];
                    }
                    if (j != 0 && l != 1) {
                        winner[i][j][k][l] |= !winner[i][j-1][k][1];
                    }
                    if (k != 0 && l != 2) {
                        winner[i][j][k][l] |= !winner[i][j][k-1][2];
                    }
                }
            }
        }
    }

    int i = 5;
    for (int j = 0; j < 30; j++) {
        for (int k = 0; k < 30; k++) {
            if (i > j || j > k) cout << "- ";
            else {
                bool canWin = winner[i][j][k][0] | winner[i][j][k][1] | winner[i][j][k][2];
                cout << (canWin ? 1 : 0) << ' ';
            }
        }
        cout << endl;
    }
    return 0;
}