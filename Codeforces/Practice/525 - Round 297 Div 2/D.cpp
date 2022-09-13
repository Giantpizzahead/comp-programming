/*
https://codeforces.com/contest/525/problem/D

Solution: A room configuration is valid iff there are no 2x2 squares with 3 room cells and 1 wall cell.
So, repeatedly turn wall cells into room cells until this condition is satisfied.
Runtime: O(NM)
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

const int MAXN = 2e3+5;

int N, M;
char A[MAXN][MAXN];
bool vis[MAXN][MAXN];
struct Loc {
    int i, j;
    int oi, oj;
};
queue<Loc> q;

void tryToAdd(int i, int j) {
    if (i < 0 || i >= N-1 || j < 0 || j >= M-1 || vis[i][j]) return;
    bool a = (A[i][j] == '.');
    bool b = (A[i+1][j] == '.');
    bool c = (A[i][j+1] == '.');
    bool d = (A[i+1][j+1] == '.');
    if (a+b+c+d == 3) {
        int oi = (!a || !c) ? i : i+1;
        int oj = (!a || !b) ? j : j+1;
        q.push({i, j, oi, oj});
        vis[i][j] = true;
    }
}

void solve() {
    cin >> N >> M;
    string S;
    rep(i, 0, N) {
        cin >> S;
        rep(j, 0, M) A[i][j] = S[j];
    }
    rep(i, 0, N-1) rep(j, 0, M-1) tryToAdd(i, j);
    while (!q.empty()) {
        Loc l = q.front(); q.pop();
        A[l.oi][l.oj] = '.';
        tryToAdd(l.oi, l.oj);
        tryToAdd(l.oi-1, l.oj);
        tryToAdd(l.oi, l.oj-1);
        tryToAdd(l.oi-1, l.oj-1);
    }
    rep(i, 0, N) {
        rep(j, 0, M) cout << A[i][j];
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    solve();
    return 0;
}