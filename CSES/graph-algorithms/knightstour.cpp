#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int N = 8;
const int ci[] = {2, 2, 1, -1, -2, -2, -1, 1};
const int cj[] = {1, -1, -2, -2, -1, 1, 2, 2};

int I, J;
int vis[N][N];

inline bool inBounds(int i, int j) {
    return i >= 0 && i < N && j >= 0 && j < N;
}

int bestC = 0;
struct Loc {
    int i, j;
    Loc(int i, int j) : i(i), j(j) {}
    bool operator<(const Loc& o) const;
};
vector<Loc> adj[N][N];

int getNeighbors(int i, int j) {
    int cnt = 0;
    for (Loc& l : adj[i][j]) {
        if (!vis[l.i][l.j]) cnt++;
    }
    return cnt;
}

bool Loc::operator<(const Loc& o) const {
    return getNeighbors(i, j) < getNeighbors(o.i, o.j);
}

void search(int i, int j, int c) {
    vis[i][j] = c;
    // Found tour?
    if (c == N*N) {
        rep(a, 0, N) rep(b, 0, N) cout << vis[a][b] << (b == N-1 ? '\n' : ' ');
        exit(0);
    }

    // New best?
    if (c > bestC) {
        bestC = c;
        // cout << "new best: " << c << endl;
        // rep(a, 0, N) rep(b, 0, N) cout << vis[a][b] << (b == N-1 ? '\n' : '\t');
        // cout << endl;
    }
    
    // Try all locations using heuristic
    sort(all(adj[i][j]));
    for (Loc& l : adj[i][j]) if(!vis[l.i][l.j]) search(l.i, l.j, c+1);

    // Backtrack
    vis[i][j] = 0;
}

void solve() {
    rep(i, 0, N) {
        rep(j, 0, N) {
            rep(d, 0, 8) {
                int ni = i+ci[d], nj = j+cj[d];
                if (inBounds(ni, nj)) adj[i][j].emplace_back(ni, nj);
            }
        }
    }
    cin >> J >> I;
    I--, J--;
    search(I, J, 1);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}