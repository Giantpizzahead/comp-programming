#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

const int INF = 1e9+7;
int N, M;
vector<ll> mana, maskManaSum;
vector<vector<int>> adj;
struct State {
    ll cost;
    int time;
    bool operator<(const State& o) const {
        return make_tuple(time, cost) < make_tuple(o.time, o.cost);
    }
};
vector<vector<vector<State>>> dp;
struct Answer {
    ll manaSum, cost;
    int time;
};
vector<vector<Answer>> answers;

vector<State> makeMonotone(vector<State>& rawStates) {
    sort(all(rawStates));
    vector<State> toEval;
    ll bestCost = rawStates[0].cost + 1;
    for (State s : rawStates) {
        if (s.cost < bestCost) {
            bestCost = s.cost;
            toEval.push_back(s);
        }
    }
    return toEval;
}

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
    dp.resize(N, vector<vector<State>>(1 << N));
    answers.resize(N);
    rep(e, 0, N) dp[e][1 << e].push_back({0, 0});
    
    rep(mask, 0, (1 << N)) {
        rep(e, 0, N) {
            if (!(mask & (1 << e))) continue;
            // Purge all useless states (greater time must mean less cost)
            vector<State>& rawStates = dp[e][mask];
            if (rawStates.empty()) continue;
            vector<State> toEval = makeMonotone(rawStates);

            // Evaluate each state
            for (State s : toEval) {
                // cout << "dp " << e << " " << bitset<2>(mask) << " = (" << s.cost << ", " << s.time << ")\n";
                // Try taking each edge
                rep(newE, 0, N) {
                    if (mask & (1 << newE)) continue;
                    int newT = s.time + adj[e][newE];
                    if (newT >= INF) continue;
                    int newMask = mask | (1 << newE);
                    ll newCost = s.cost + maskManaSum[mask] * adj[e][newE];
                    dp[newE][newMask].push_back({newCost, newT});
                }
                // Update answer
                answers[e].push_back({maskManaSum[mask], s.cost, s.time});
            }
        }
    }

    // Answer queries
    int Q; cin >> Q;
    rep(q, 0, Q) {
        int S, E; cin >> S >> E;
        E--;

        // Get the best answer
        ll best = 0;
        for (Answer& a : answers[E]) {
            if (a.time > S) continue;
            best = max(a.manaSum * S - a.cost, best);
        }
        cout << best << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
