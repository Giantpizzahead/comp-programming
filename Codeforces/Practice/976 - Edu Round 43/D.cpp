/*
https://codeforces.com/contest/976/problem/D

Solution: Very neat recursion, involving completely connecting 1 node to reduce the problem to an equivalent subproblem.
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

int N;
vi D;
vector<pii> ans;

void solve(vi& d, int sn) {
    int n = d.back()+1;
    // Create a fully connected node to satisfy d_n
    rep(i, 1, n) ans.emplace_back(sn, sn+i);
    rep(i, 0, sz(d)) d[i]--;
    if (d[0] == 0) {
        // Lowest degree node is satisfied
        if (sz(d) <= 2) return;
        d.erase(d.begin());
        d.erase(prev(d.end()));
    }
    // Recurse on next node
    solve(d, sn+1);
}

void solve() {
    cin >> N;
    rep(i, 0, N) {
        int x; cin >> x;
        D.push_back(x);
    }
    solve(D, 0);
    cout << sz(ans) << '\n';
    for (pii& p : ans) cout << p.first+1 << ' ' << p.second+1 << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    solve();
    return 0;
}