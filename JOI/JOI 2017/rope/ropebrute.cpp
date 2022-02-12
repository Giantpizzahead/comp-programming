/*
Testing if the simplified problem statement is accurate.
Result: Yes, it is.
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 15;

int N, M;
int C[MAXN];
int ans[MAXN];

void brute(int i, int v, int c1, int c2) {
    int newV = v;
    if (i == 0) {
        // First segment
        rep(j, i, N) {
            if (C[j] != c1) newV++;
            brute(j+1, newV, c2, c1);
        }
    } else {
        // Try making last segment
        rep(j, i, N) if (C[j] != c1) newV++;
        ans[c1] = min(newV, ans[c1]);
        ans[c2] = min(newV, ans[c2]);
        // Make middle segment
        newV = v;
        rep(j, i, N) {
            if (C[j] != c1) newV++;
            if ((j-i) % 2 == 1) brute(j+1, newV, c2, c1);
        }
    }
}

void solve() {
    cin >> N >> M;
    rep(i, 0, N) {
        cin >> C[i];
        C[i]--;
    }
    rep(i, 0, M) ans[i] = N;
    rep(c1, 0, M) {
        rep(c2, 0, M) {
            brute(0, 0, c1, c2);
        }
    }
    rep(i, 0, M) cout << ans[i] << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}