/*
https://www.facebook.com/codingcompetitions/hacker-cup/2014/qualification-round/problems/A
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

void solve() {
    int N; cin >> N;
    vector<vector<char>> grid(N, vector<char>(N));
    rep(i, 0, N) {
        string curr; cin >> curr;
        rep(j, 0, N) {
            grid[i][j] = curr[j];
        }
    }

    // Find square coordinates
    int i1 = N, j1 = N, i2 = 0, j2 = 0;
    rep(i, 0, N) rep(j, 0, N) if (grid[i][j] == '#') {
        i1 = min(i1, i), i2 = max(i2, i);
        j1 = min(j1, j), j2 = max(j2, j);
    }

    // Check for a valid square
    if (j1 - i1 != j2 - i2) {
        cout << "NO\n";
        return;
    }
    rep(i, i1, i2+1) rep(j, j1, j2+1) if (grid[i][j] != '#') {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("square_detector_input.txt", "r", stdin);
    freopen("test.out", "w", stdout);
    int T; cin >> T;
    rep(i, 1, T+1) {
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}
