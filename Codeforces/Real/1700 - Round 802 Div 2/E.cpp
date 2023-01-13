#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using namespace std;

int N, M;
vector<vector<int>> A;
vector<vector<bool>> toTry;

struct State {
    int i, j, v;
    bool operator<(const State& o) const {
        return v > o.v;
    }
};
priority_queue<State> pq;
int ci[] = {1, 0, -1, 0}, cj[] = {0, 1, 0, -1};

int works() {
    vector<vector<bool>> vis(N, vector<bool>(M));
    rep(i, 0, N) rep(j, 0, M) {
        if (A[i][j] == 1) {
            vis[i][j] = true;
            pq.push({i, j, 1});
        }
    } 
    int numVis = 0;
    while (!pq.empty()) {
        State s = pq.top(); pq.pop();
        if (s.v != numVis+1) break;
        numVis++;
        rep(d, 0, 4) {
            int ni = s.i + ci[d];
            int nj = s.j + cj[d];
            if (ni < 0 || nj < 0 || ni >= N || nj >= M || vis[ni][nj]) continue;
            vis[ni][nj] = true;
            pq.push({ni, nj, A[ni][nj]});
        }
    }
    while (!pq.empty()) pq.pop();
    return numVis;
}

void solve() {
    cin >> N >> M;
    A.resize(N, vector<int>(M));
    rep(i, 0, N) {
        rep(j, 0, M) {
            cin >> A[i][j];
        }
    }
    int res = works();
    if (res == N*M) {
        cout << "0\n";
    } else {
        toTry.resize(N, vector<bool>(M));
        int i1, j1, ib, jb;
        // Try swapping stuff near 1 or the blocked number
        int numWays = 0;
        rep(i, 0, N) rep(j, 0, N) {
            if (A[i][j] == 1) {
                i1 = i;
                j1 = j;
            } else if (A[i][j] == res+1) {
                ib = i;
                jb = j;
            }
        }
        rep(k, 0, 2) {
            rep(i, -2, 2+1) {
                rep(j, -2, 2+1) {
                    int ni, nj;
                    if (k == 0) {
                        ni = i1 + i;
                        nj = j1 + j;
                    } else {
                        ni = ib + i;
                        nj = jb + j;
                    }
                    if (ni < 0 || nj < 0 || ni >= N || nj >= M) continue;
                    toTry[ni][nj] = true;
                }
            }
        }
        rep(i, 0, N) rep(j, 0, M) rep(d, 0, 2) {
            int ni = i + ci[d];
            int nj = j + cj[d];
            if (ni < 0 || nj < 0 || ni >= N || nj >= M) continue;
            swap(A[i][j], A[ni][nj]);
            cout << "swap " << i << " " << j << " " << ni << " " << nj << " = " << works() << '\n';
            if (works() == N*M) numWays++;
            swap(A[i][j], A[ni][nj]);
        }
        if (numWays == 0) cout << "2\n";
        else cout << "1 " << numWays << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}