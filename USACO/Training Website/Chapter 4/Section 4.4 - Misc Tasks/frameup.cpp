/*
ID: sunnyky1
LANG: C++11
TASK: frameup
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 30;

int N, M, F;
int minI[MAXN], maxI[MAXN], minJ[MAXN], maxJ[MAXN];
int G[MAXN][MAXN];
bool req[MAXN][MAXN];

vector<char> ordering;
bool used[MAXN];

void genOrdering() {
    if (sz(ordering) == F) {
        for (char c : ordering) cout << c;
        cout << '\n';
        return;
    }
    // Choose next frame
    rep(k, 0, MAXN) {
        if (maxI[k] == -1 || used[k]) continue;
        bool valid = true;
        rep(l, 0, MAXN) {
            if (!used[l] && req[l][k]) {
                valid = false;
                break;
            }
        }
        if (!valid) continue;
        ordering.push_back(k + 'A');
        used[k] = true;
        genOrdering();
        ordering.pop_back();
        used[k] = false;
    }
}

void solve() {
    cin >> N >> M;
    rep(i, 0, MAXN) {
        minI[i] = MAXN;
        maxI[i] = -1;
        minJ[i] = MAXN;
        maxJ[i] = -1;
    }
    // Get frame borders
    rep(i, 0, N) {
        string str; cin >> str;
        rep(j, 0, M) {
            if (str[j] == '.') G[i][j] = -1;
            else {
                int k = str[j] - 'A';
                G[i][j] = k;
                minI[k] = min(i, minI[k]);
                maxI[k] = max(i, maxI[k]);
                minJ[k] = min(j, minJ[k]);
                maxJ[k] = max(j, maxJ[k]);
            }
        }
    }
    F = 0;
    rep(k, 0, MAXN) {
        if (maxI[k] == -1) continue;
        F++;
    }
    // Find prerequisite graph
    rep(k, 0, MAXN) {
        if (maxI[k] == -1) continue;
        rep(i, minI[k], maxI[k]+1) {
            if (G[i][minJ[k]] != k) req[k][G[i][minJ[k]]] = true;
            if (G[i][maxJ[k]] != k) req[k][G[i][maxJ[k]]] = true;
        }
        rep(j, minJ[k], maxJ[k]+1) {
            if (G[minI[k]][j] != k) req[k][G[minI[k]][j]] = true;
            if (G[maxI[k]][j] != k) req[k][G[maxI[k]][j]] = true;
        }
    }
    // Print all orderings
    genOrdering();
}

int main() {
    freopen("frameup.in", "r", stdin);
    freopen("frameup.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}