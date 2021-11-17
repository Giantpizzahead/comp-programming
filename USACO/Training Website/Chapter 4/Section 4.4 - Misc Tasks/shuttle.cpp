/*
ID: sunnyky1
LANG: C++11
TASK: shuttle
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXH = 25;

int N, hole, goal;
unordered_set<int> vis[MAXH];

vector<int> S;

inline int hashState() {
    int H = 0;
    rep(i, 0, sz(S)) {
        H *= 2;
        H += S[i];
    }
    // for (int x : S) debug << x;
    // debug << ' ' << hole << " = " << H << '\n';
    return H;
}

stack<int> moves;

bool dfs() {
    int H = hashState();
    // Check visited
    if (vis[hole].count(H)) return false;
    vis[hole].insert(H);
    // Check goal
    if (H == goal && hole == N) return true;

    // Try all moves in lexicographical order
    if (hole > 1 && S[hole-2] != S[hole-1]) {
        // Jump right
        swap(S[hole-2], S[hole]);
        hole -= 2;
        if (dfs()) {
            moves.push(-2);
            return true;
        }
        hole += 2;
        swap(S[hole-2], S[hole]);
    }
    if (hole > 0 && !S[hole-1]) {
        // Move right
        swap(S[hole-1], S[hole]);
        hole -= 1;
        if (dfs()) {
            moves.push(-1);
            return true;
        }
        hole += 1;
        swap(S[hole-1], S[hole]);
    }
    if (hole < sz(S)-1 && S[hole+1]) {
        // Move left
        swap(S[hole+1], S[hole]);
        hole += 1;
        if (dfs()) {
            moves.push(1);
            return true;
        }
        hole -= 1;
        swap(S[hole+1], S[hole]);
    }
    if (hole < sz(S)-2 && S[hole+2] != S[hole+1]) {
        // Jump right
        swap(S[hole+2], S[hole]);
        hole += 2;
        if (dfs()) {
            moves.push(2);
            return true;
        }
        hole -= 2;
        swap(S[hole+2], S[hole]);
    }

    // Nothing found
    return false;
}

void solve() {
    cin >> N;
    S = vector<int>(2*N+1);
    // Record goal state
    rep(i, 0, N) {
        S[i] = 1;
        S[2*N-1] = 0;
    }
    goal = hashState();
    // Put starting state
    rep(i, 0, N) {
        S[i] = 0;
        S[2*N-i] = 1;
    }
    hole = N;
    dfs();

    hole = N + 1;
    for (int i = 0; !moves.empty(); i++) {
        if (i == 0);
        else if (i % 20 == 0) cout << '\n';
        else cout << ' ';
        hole += moves.top(); moves.pop();
        cout << hole;
    }
    cout << '\n';
}

int main() {
    freopen("shuttle.in", "r", stdin);
    freopen("shuttle.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}