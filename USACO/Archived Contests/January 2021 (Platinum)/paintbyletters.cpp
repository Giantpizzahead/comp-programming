#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
using namespace std;
using ll = long long;

const int MAXN = 1005, MAXC = 1000005;

int ci[] = {1, 0, -1, 0}, cj[] = {0, 1, 0, -1};

int N, M, Q, compN, BOUND;
int compli[MAXC], complj[MAXC], compri[MAXC], comprj[MAXC], compsize[MAXC];
char grid[MAXN][MAXN];
int leftVals[MAXN][MAXN];
int compID[MAXN][MAXN];
int entrances[MAXN][MAXN][4];

inline bool inBounds(int i, int j) {
    return i >= 0 && i < N && j >= 0 && j < M;
}

int li, ri, lj, rj;
void dfs(int i, int j) {
    if (i < li) {
        li = i;
        lj = j;
    } else if (i == li && j < lj) {
        lj = j;
    }
    compID[i][j] = compN;
    compsize[compN]++;
    rep(d, 0, 4) {
        int ni = i + ci[d];
        int nj = j + cj[d];
        if (inBounds(ni, nj) && compID[ni][nj] == -1 && grid[i][j] == grid[ni][nj]) {
            dfs(ni, nj);
        }
    }
}

bool vis[MAXN][MAXN];
bool compVis[MAXC];
stack<pair<int, int>> visRem;
stack<int> compVisRem;

inline bool inStrictBounds(int i, int j) {
    return i >= li && i <= ri && j >= lj && j <= rj;
}

void dfsBounds(int i, int j) {
    vis[i][j] = true;
    visRem.emplace(i, j);
    rep(d, 0, 4) {
        int ni = i + ci[d];
        int nj = j + cj[d];
        if (inStrictBounds(ni, nj) && !vis[ni][nj] && compID[ni][nj] == compID[i][j]) {
            dfsBounds(ni, nj);
        }
    }
}

void solve() {
    cin >> N >> M >> Q;
    // Heuristic
    BOUND = (N*M <= 10000 ? 1e9 : sqrt(N*M)*50);
    rep(i, 0, N) {
        string S; cin >> S;
        rep(j, 0, M) {
            grid[i][j] = S[j];
            compID[i][j] = -1;
        }
    }
    
    rep(i, 0, N) {
        rep(j, 0, M) {
            if (compID[i][j] == -1) {
                li = N+1, ri = -1;
                lj = N+1, rj = -1;
                dfs(i, j);
                leftVals[li][lj]++;
                compli[compN] = li;
                compri[compN] = ri;
                complj[compN] = lj;
                comprj[compN] = rj;
                compN++;
            }
            // cout << compID[i][j] << ' ';
        }
        // cout << endl;
    }

    // Prefix sums for leftVals
    rep(i, 0, N) {
        rep(j, 0, M) {
            if (i != 0) leftVals[i][j] += leftVals[i-1][j];
            if (j != 0) leftVals[i][j] += leftVals[i][j-1];
            if (i != 0 && j != 0) leftVals[i][j] -= leftVals[i-1][j-1];
        }
    }

    // Handle each query
    rep(q, 0, Q) {
        cin >> li >> lj >> ri >> rj;
        li--, lj--, ri--, rj--;
        int answer = 0;
        // Start with prefix sum value
        answer += leftVals[ri][rj];
        if (li != 0) answer -= leftVals[li-1][rj];
        if (lj != 0) answer -= leftVals[ri][lj-1];
        if (li != 0 && lj != 0) answer += leftVals[li-1][lj-1];
        rep(i, li, ri+1) {
            rep(k, 0, 2) {
                int j = lj;
                if (k == 1) j = rj;
                if (!vis[i][j]) {
                    int comp = compID[i][j];
                    if (compsize[comp] >= BOUND && compVis[comp]) continue;  // Probably connects
                    if (!compVis[comp]) {
                        compVis[comp] = true;
                        compVisRem.push(comp);
                        if (compli[comp] >= li && compli[comp] <= ri && complj[comp] >= lj && complj[comp] <= rj) {
                            answer--;
                        }
                    }
                    if (compsize[comp] < BOUND) dfsBounds(i, j);
                    answer++;
                }
            }
        }
        rep(j, lj+1, rj) {
            rep(k, 0, 2) {
                int i = li;
                if (k == 1) i = ri;
                if (!vis[i][j]) {
                    int comp = compID[i][j];
                    if (compsize[comp] >= BOUND && compVis[comp]) continue;  // Probably connects
                    if (!compVis[comp]) {
                        compVis[comp] = true;
                        compVisRem.push(comp);
                        if (compli[comp] >= li && compli[comp] <= ri && complj[comp] >= lj && complj[comp] <= rj) {
                            answer--;
                        }
                    }
                    if (compsize[comp] < BOUND) dfsBounds(i, j);
                    answer++;
                }
            }
        }
        cout << answer << '\n';

        // Backtrack
        while (!visRem.empty()) {
            auto& p = visRem.top();
            vis[p.first][p.second] = false;
            visRem.pop();
        }
        while (!compVisRem.empty()) {
            compVis[compVisRem.top()] = false;
            compVisRem.pop();
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}