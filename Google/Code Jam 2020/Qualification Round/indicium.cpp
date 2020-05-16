#include <iostream>

#define MAXN 55

using namespace std;

int N, K;
int arr[MAXN][MAXN];
int numOpenInCol[MAXN][MAXN];
bool numInCol[MAXN][MAXN];
bool numUsedInRow[MAXN][MAXN];

bool fillArr() {
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j < N; j++) {
            numInCol[i][j] = false;
            numUsedInRow[i][j] = false;
            numOpenInCol[i][j] = N-2;
            if (i != j && i != N) arr[i][j] = 0;
        }
    }

    for (int i = 0; i < N; i++) {
        numInCol[arr[i][i]][i] = true;
        numUsedInRow[arr[i][i]][i] = true;
        numOpenInCol[arr[i][i]][i] = 0;
    }

    // Fill each number one at a time
    for (int n = 1; n <= N; n++) {
        for (int i = 0; i < N; i++) {
            if (numUsedInRow[n][i]) continue;  // Already filled
            int pl = -1, minOpen = 9999999;
            for (int j = 0; j < N; j++) {
                if (numInCol[n][j]) continue;  // Column already used
                if (arr[i][j] == 0) {
                    // Can put here
                    if (numOpenInCol[n][j] < minOpen) {
                        // Better to place here
                        pl = j;
                        minOpen = numOpenInCol[n][j];
                    }
                }
            }
            // Place number in given location
            if (pl == -1) return false;  // Impossible to fill
            else {
                numUsedInRow[n][i] = true;
                numInCol[n][pl] = true;
                arr[i][pl] = n;
            }

            // Update numOpenInCol (remove current row)
            for (int j = 0; j < N; j++) {
                if (arr[i][j] == 0 || arr[i][j] == n) numOpenInCol[n][j]--;
                for (int k = 1; k <= N; k++) {
                    if (k != n && arr[i][j] == n && !numUsedInRow[k][i] && !numInCol[k][j]) {
                        numOpenInCol[k][j]--;
                        cout << "num open " << k << " " << j << " = " << numOpenInCol[k][j] << endl;
                    }
                }
            }
        }
    }
    return true;
}

void solve(int tn) {
    cout << "Case #" << tn << ": ";
    cin >> N >> K;
    for (int i = 0; i < N; i++) arr[i][i] = i+1;
    bool possible = fillArr();

    cout << "HELLO" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (j != 0) cout << ' ';
            cout << arr[i][j];
        }
        cout << endl;
    }
}

int main() {
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) solve(i);
}
