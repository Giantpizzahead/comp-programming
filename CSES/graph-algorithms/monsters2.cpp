#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1005;
const int ci[] = {1, 0, -1, 0}, cj[] = {0, 1, 0, -1};
const char cc[] = {'D', 'R', 'U', 'L'};
int N, M, si, sj;
bool G[MAXN][MAXN];
char F[MAXN][MAXN];
struct Loc {
    int i, j;
    bool m;
};
queue<Loc> locs;

inline bool inBounds(int i, int j) {
    return i >= 0 && i < N && j >= 0 && j < M;
}

inline bool onEdge(int i, int j) {
    return i == 0 || i == N-1 || j == 0 || j == M-1;
}

void solve() {
    cin >> N >> M;
    rep(i, 0, N) rep(j, 0, M) F[i][j] = -1;
    rep(i, 0, N) {
        string S; cin >> S;
        rep(j, 0, M) {
            G[i][j] = (S[j] != '.');
            if (S[j] == 'A') {
                si = i, sj = j;
                if (onEdge(si, sj)) {
                    cout << "YES\n0\n";
                    return;
                }
            } else if (S[j] == 'M') {
                locs.push({i, j, true});
            }
        }
    }
    locs.push({si, sj, false});
    F[si][sj] = -1;
    int currLeft = sz(locs), nextLeft = 0, currLen = 0;
    while (!locs.empty()) {
        Loc l = locs.front(); locs.pop();
        // cout << l.i << " " << l.j << " " << l.m << endl;
        if (currLeft == 0) {
            currLeft = nextLeft;
            nextLeft = 0;
            currLen++;
        }
        currLeft--;
        rep(d, 0, 4) {
            int ni = l.i + ci[d], nj = l.j + cj[d];
            if (!inBounds(ni, nj) || G[ni][nj]) continue;
            if (onEdge(ni, nj) && !l.m) {
                // Path found
                cout << "YES\n" << currLen+1 << "\n";
                stack<char> path;
                F[ni][nj] = d;
                while (F[ni][nj] != -1) {
                    int d = F[ni][nj];
                    path.push(cc[d]);
                    ni -= ci[d], nj -= cj[d];
                }
                while (!path.empty()) {
                    cout << path.top(); path.pop();
                }
                cout << "\n";
                return;
            } else {
                F[ni][nj] = d;
                G[ni][nj] = true;
                locs.push({ni, nj, l.m});
                nextLeft++;
            }
        }
    }
    cout << "NO\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}