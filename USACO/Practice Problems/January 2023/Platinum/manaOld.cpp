#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

const int INF = 1e9+7;
int N, M;
vector<ll> mana, maskManaSum, bestMana;
vector<vector<int>> adj;
vector<vector<ll>> dpCost;
vector<vector<int>> dpTime;

void solve() {
    cin >> N >> M;
    mana.resize(N);
    adj.resize(N, vector<int>(N, INF));
    rep(i, 0, N) cin >> mana[i];
    rep(j, 0, M) {
        int a, b, t; cin >> a >> b >> t;
        a--, b--;
        adj[a][b] = t;
    }
    rep(k, 0, N) rep(i, 0, N) rep(j, 0, N) {
        adj[i][j] = min(adj[i][k] + adj[k][j], adj[i][j]);
    }

    // Generate info
    maskManaSum.resize(1 << N, 0);
    rep(mask, 0, (1 << N)) {
        rep(e, 0, N) if (mask & (1 << e)) maskManaSum[mask] += mana[e];
    }
    
    // Bitmask DP
    dpCost.resize(N, vector<ll>(1 << N));
    dpTime.resize(N, vector<int>(1 << N));
    bestMana.resize(N);

    int Q; cin >> Q;
    rep(q, 0, Q) {
        int S, E; cin >> S >> E;
        E--;

        int LIMIT = S;
        rep(e, 0, N) {
            bestMana[e] = mana[e] * LIMIT;
            rep(mask, 0, (1 << N)) dpTime[e][mask] = INF;
        }
        rep(e, 0, N) {
            dpCost[e][1 << e] = 0;
            dpTime[e][1 << e] = 0;
        }
        
        rep(mask, 0, (1 << N)) {
            rep(e, 0, N) {
                // cout << "dp " << e << " " << bitset<3>(mask) << " = " << dpCost[e][mask] << " " << dpTime[e][mask] << "\n";
                if (!(mask & (1 << e)) || dpTime[e][mask] > LIMIT) continue;
                // Try taking each edge
                rep(newE, 0, N) {
                    if (mask & (1 << newE)) continue;
                    int newT = dpTime[e][mask] + adj[e][newE];
                    if (newT > LIMIT) continue;
                    int newMask = mask | (1 << newE);
                    ll newCost = dpCost[e][mask] + maskManaSum[mask] * adj[e][newE];
                    if (dpTime[newE][newMask] == INF) dpCost[newE][newMask] = newCost + 1;
                    bool costLess = (newCost < dpCost[newE][newMask]);
                    bool timeLess = (newT < dpTime[newE][newMask]);
                    if (costLess) {
                        dpTime[newE][newMask] = newT;
                        dpCost[newE][newMask] = newCost;
                    }
                }
                // Update answer
                bestMana[e] = max(maskManaSum[mask] * LIMIT - dpCost[e][mask], bestMana[e]);
            }
        }

        cout << bestMana[E] << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
