/*
https://codeforces.com/contest/1607/problem/F
*/

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

void solve() {
    int N = 2000;
    int M = 2000;
    srand(time(NULL));
    cout << N << " " << M << endl;
    rep(i, 0, N) {
        rep(j, 0, M) cout << (rand() % 12 == 0 ? '.' : '*');
        cout << endl;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    solve();
    return 0;
}