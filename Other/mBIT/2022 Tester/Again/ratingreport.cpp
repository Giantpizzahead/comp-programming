/*
https://codeforces.com/gym/383128/problem/H

Solution: Binary search + DFS to combine answers from subtrees.
Each dfs calls returns the min # of ratings >= R needed for the entire subtree to rate
the park as >= R (infinity if impossible).
Runtime: O(NlogN)
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

const int MAXN = 2e5+5;
const int INF = MAXN;

int N, K, R;
vi adj[MAXN];
int A[MAXN];

int dfs(int n) {
    if (A[n] >= 0) {
        if (A[n] == 0) return 1;
        else if (A[n] < R) return INF;
        else return 0;
    } else if (A[n] == -1) {
        // Min
        int res = 0;
        for (int e : adj[n]) {
            res += dfs(e);
            if (res > INF) res = INF;
        }
        return res;
    } else {
        // Max
        int res = INF;
        for (int e : adj[n]) {
            res = min(dfs(e), res);
        }
        return res;
    }
}

void solve() {
    cin >> N >> K;
    int p;
    rep(i, 1, N) {
        cin >> p; p--;
        adj[p].push_back(i);
    }
    string a;
    rep(i, 0, N) {
        cin >> a;
        if (a == "min") A[i] = -1;
        else if (a == "max") A[i] = -2;
        else A[i] = stoi(a);
    }
    // Binary search
    int low = 1, high = K;
    while (low < high) {
        R = (low+high+1)/2;
        int canUse = K-R+1;
        rep(i, 0, N) if (A[i] >= R) canUse--;
        if (dfs(0) <= canUse) low = R;
        else high = R-1;
    }
    cout << low << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    solve();
    return 0;
}