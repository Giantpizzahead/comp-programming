#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 31, MAXP = 1000;

int P, D, N;
int I[MAXP], J[MAXP];
int dead[MAXP];
int grid[MAXN][MAXN];
int ci[] = {1, 0, -1, 0}, cj[] = {0, 1, 0, -1};

void solve() {
    cin >> P >> D >> N;
    for (int i = 0; i < P; i++) {
        cin >> I[i] >> J[i];
        grid[I[i]][J[i]]++;
    }
    for (int i = 1; i <= D; i++) {
        for (int j = 0; j < P; j++) {
            if (dead[j]) continue;
            for (int k = 0; k < 4; k++) {
                int ni = I[j] + ci[k] * i, nj = J[j] + cj[k] * i;
                if (ni < 0 || ni >= N || nj < 0 || nj >= N) {
                    dead[j] = i;
                    continue;
                }
                grid[ni][nj]++;
            }
        }
        for (int j = 0; j < P; j++) {
            if (dead[j]) continue;
            for (int k = 0; k < 4; k++) {
                int ni = I[j] + ci[k] * i, nj = J[j] + cj[k] * i;
                if (grid[ni][nj] > 1) dead[j] = i;
            }
        }
        // for (int j = 0; j < N; j++) {
        //     for (int k = 0; k < N; k++) {
        //         cout << grid[j][k] << ' ';
        //     }
        //     cout << endl;
        // }
    }
    for (int i = 0; i < P; i++) {
        cout << (dead[i] == 0 ? "ALIVE" : to_string(dead[i])) << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    // cin >> T;
    for (int i = 1; i <= T; i++) {
        solve();
    }
    return 0;
}