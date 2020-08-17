#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

const int MAXRC = 205;

int R, C, actualC, K, M;
bool isMissing[MAXRC][MAXRC];
long double dp[MAXRC][MAXRC];

pair<int, long double> doDP() {
    // dp[i][j] = Chance that ball starting at (i, j) will reach target column
    for (int j = 0; j < actualC; j++) {
        dp[R-1][j] = 0;
    }
    dp[R-1][K*2+1] = 1000000L;

    for (int i = R-2; i >= 0; i--) {
        for (int j = 1; j < actualC - 1; j++) {
            if ((i+j) % 2 == 0 && !isMissing[i][j]) {
                // Peg is on this square
                dp[i][j] = 0;
            } else if ((i+j) % 2 == 0 || isMissing[i+1][j]) {
                // Ball would just go down
                dp[i][j] = dp[i+1][j];
            } else if (i % 2 == 0 && j == 1) {
                // On leftmost of wide row; ball must go right
                dp[i][j] = dp[i+1][j+1];
            } else if (i % 2 == 0 && j == actualC - 2) {
                // On rightmost of wide row; ball must go left
                dp[i][j] = dp[i+1][j-1];
            } else {
                // Ball splits here
                dp[i][j] = (dp[i+1][j-1] + dp[i+1][j+1]) / 2;
            }
            if (i % 2 == 0) {
                // Wide row
            } else {
                // Narrow row
            }
        }
    }

    // Print for debug
    // for (int i = 0; i < R; i++) {
    //     for (int j = 0; j < actualC; j++) {
    //         cout << fixed << setprecision(6) << dp[i][j] << ' ';
    //     }
    //     cout << endl;
    // }

    // Find best column to drop in
    pair<int, long double> best = {0, -1};
    for (int i = 0; i < C - 1; i++) {
        if (dp[0][i*2+1] > best.second) {
            best.first = i;
            best.second = dp[0][i*2+1];
        }
    }
    return best;
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

    pair<int, long double> best = doDP();
    
    fout << "Case #" << tn << ": " << best.first << " " << fixed << setprecision(6) << round(best.second) / 1000000 << endl;

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