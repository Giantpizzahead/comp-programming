#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 3001;
const ll MOD = 1e9+7;

int N;
ll open[MAXN][MAXN], cowsConnect[MAXN][MAXN];
int S[MAXN], T[MAXN];

void plusMod(ll& a, ll b) {
    a = (a+b) % MOD;
}

void solve() {
    cin >> N;
    for (int i = 0; i < N; i++) cin >> S[i];
    for (int i = 0; i < N; i++) cin >> T[i];
    sort(S, S+N);
    sort(T, T+N);

    // open[# barns][# unused cows]
    // locked[# barns][# must use cows][# might use cows]
    open[0][0] = 1;
    for (int i = 0; i < N; i++) {
        // How many cows gained by this barn?
        int lastBarn = (i == 0 ? 0 : T[i-1]), cowsGained = 0;
        for (int j = 0; j < N; j++) {
            if (S[j] > lastBarn && S[j] <= T[i]) cowsGained++;
        }
        // cout << "barn " << i << " gained " << cowsGained << endl;
        // Update open
        for (int j = 0; j <= N; j++) {
            if (!open[i][j]) continue;
            int nj = j + cowsGained;
            // Use this barn
            if (nj != 0) plusMod(open[i+1][nj-1], open[i][j] * nj);
            // Don't use this barn
            plusMod(open[i+1][nj], open[i][j]);
            // Don't use a cow / lock from now on
            for (int k = 0; k < cowsGained; k++) {
                if (j+k-1 >= 0) plusMod(locked[i+1][j+k-1][cowsGained-1-k], open[i][j] * (j+k));
                if (cowsGained-2-k >= 0) plusMod(locked[i+1][j+k][cowsGained-2-k], open[i][j] * (cowsGained-1-k));
            }
        }
    }

    // cout << "open:\n";
    // for (int i = 0; i <= N; i++) {
    //     for (int j = 0; j <= N; j++) {
    //         cout << open[i][j] << ' ';
    //     }
    //     cout << endl;
    // }

    // cout << "locked:\n";
    // for (int i = 0; i <= N; i++) {
    //     cout << "i = " << i << endl;
    //     for (int j = 0; j <= N; j++) {
    //         for (int k = 0; k <= N; k++) cout << locked[i][j][k] << ' ';
    //         cout << endl;
    //     }
    //     cout << endl;
    // }

    // open works if cows left is 0 (all cows used)
    ll answer = open[N][0];

    // locked works if must use is 0
    for (int k = 0; k <= N; k++) plusMod(answer, locked[N][0][k]);
    cout << answer << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}