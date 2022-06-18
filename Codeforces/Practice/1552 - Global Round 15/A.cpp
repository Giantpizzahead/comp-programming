/*
https://codeforces.com/problemset/problem/1552/A
*/

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using namespace std;

int N;
string S, T;

void solve() {
    cin >> N >> S;
    T = S;
    sort(all(T));
    int ans = 0;
    rep(i, 0, N) if (S[i] != T[i]) ans++;
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}