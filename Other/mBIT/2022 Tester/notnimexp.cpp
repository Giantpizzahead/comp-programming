#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using namespace std;

int A, B;

int findWinner(int p1, int p2, int t) {
    if (t == 0) {
        int res = 1;
        if (p1 >= A) res = min(findWinner(p1-A, p2, 1-t), res);
        if (p2 >= A) res = min(findWinner(p1, p2-A, 1-t), res);
        return res;
    } else {
        int res = 0;
        if (p1 >= B) res = max(findWinner(p1-B, p2, 1-t), res);
        if (p2 >= B) res = max(findWinner(p1, p2-B, 1-t), res);
        return res;
    }
}

void solve() {
    cin >> A >> B;
    rep(i, 0, 15) {
        rep(j, 0, 15) {
            cout << findWinner(i, j, 0) << " \n"[j==14];
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}