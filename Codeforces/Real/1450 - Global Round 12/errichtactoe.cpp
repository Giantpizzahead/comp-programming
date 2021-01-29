#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 305;

int N;
int value[MAXN][MAXN];
char grid[MAXN][MAXN];

bool horRow(int i, int j) {
    if (j <= 0 || j >= N-1) return false;
    return grid[i][j] == grid[i][j-1] && grid[i][j] == grid[i][j+1];
}

bool vertRow(int i, int j) {
    if (i <= 0 || i >= N-1) return false;
    return grid[i][j] == grid[i-1][j] && grid[i][j] == grid[i+1][j];
}

void updateVal(int i, int j) {
    if (i < 0 || i > N-1 || j < 0 || j > N-1) return;
    if (grid[i][j] == '.') value[i][j] = 0;
    else {
        value[i][j] = 0;
        if (horRow(i, j-1) || horRow(i, j) || horRow(i, j+1)) value[i][j]++;
        if (vertRow(i-1, j) || vertRow(i, j) || vertRow(i+1, j)) value[i][j]++;
    }
}

void solve() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        string str;
        cin >> str;
        for (int j = 0; j < N; j++) grid[i][j] = str[j];
    }
    // Flip to minimize # of 3-in-a-rows
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            updateVal(i, j);
        }
    }
    for (int k = 6; k > 0; k--) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (value[i][j] >= k) {
                    grid[i][j] = 'O';
                    value[i][j] = 0;
                    updateVal(i-2, j);
                    updateVal(i-1, j);
                    updateVal(i+1, j);
                    updateVal(i+2, j);
                    updateVal(i, j-2);
                    updateVal(i, j-1);
                    updateVal(i, j+1);
                    updateVal(i, j+2);
                }
            }
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << grid[i][j];
        }
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        solve();
    }
    return 0;
}