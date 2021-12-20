#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

const int MAXRC = 205;

int R, C, actualC, K, M;
bool isMissing[MAXRC][MAXRC];
long double dp[MAXRC][MAXRC];

long double tryColumn(int c) {
    // dp[i][j] = Chance of ball going through column j in the ith row
    for (int j = 0; j < actualC; j++) dp[0][j] = 0;
    dp[0][c*2+1] = 1;

    for (int i = 0; i < R-1; i++) {
        for (int j = 0; j < actualC; j++) {
            if (dp[i][j] == 0) continue;
            // Just transfer down if no peg is below
            else if ((i+j+1) % 2 == 1 || isMissing[i+1][j]) {
                dp[i+1][j] += dp[i][j];
            }
            // If on edge, must go right / left accordingly
            else if (j == 1) {
                dp[i+1][j+1] += dp[i][j];
            }
            else if (j == actualC-2) {
                dp[i+1][j-1] += dp[i][j];
            }
            // Split probability into half for each side
            else {
                dp[i+1][j+1] += dp[i][j] / 2;
                dp[i+1][j-1] += dp[i][j] / 2;
            }
        }
    }

    // for (int i = 0; i < R; i++) {
    //     for (int j = 0; j < actualC; j++) {
    //         cout << fixed << setprecision(6) << dp[i][j] << ' ';
    //     }
    //     cout << endl;
    // }
    // cout << "-----" << endl;

    double toReturn = dp[R-1][K*2+1];

    // Reset DP
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < actualC; j++) {
            dp[i][j] = 0;
        }
    }

    return toReturn;
}

void solve(int tn) {
    // cout << "Case " << tn << endl;
    fin >> R >> C >> K >> M;
    actualC = C * 2 - 1;
    int r, c;
    for (int i = 0; i < M; i++) {
        fin >> r >> c;
        if (r % 2 == 0) {
            isMissing[r][c*2] = true;
        } else {
            isMissing[r][c*2+1] = true;
        }
    }

    int bestLoc = 0;
    long double bestChance = 0;
    for (int i = 0; i < C - 1; i++) {
        long double chance = tryColumn(i);
        if (chance > bestChance) {
            bestChance = chance;
            bestLoc = i;
        }
    }
    
    fout << "Case #" << tn << ": " << bestLoc << " " << fixed << setprecision(6) << bestChance << endl;

    // Reset isMissing
    for (int i = 0; i < MAXRC; i++) {
        for (int j = 0; j < MAXRC; j++) {
            isMissing[i][j] = false;
        }
    }
}

int main() {
    int T;
    fin >> T;
    for (int i = 1; i <= T; i++) solve(i);
    return 0;
}