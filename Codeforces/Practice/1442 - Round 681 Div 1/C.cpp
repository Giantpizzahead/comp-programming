#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+1, MAXT = 20, MOD = 998244353, INF = 1e9;

int N, M;
int bestDist[MAXN][MAXT+2];
int bestT[MAXN][2];
vi adj[MAXN], revAdj[MAXN];
struct State {
    int n, c, t;
    State(int nn, int cc, int tt) : n(nn), c(cc), t(tt) {}
    bool operator>(const State& o) const {
        if (t != o.t) return t > o.t;
        else return c > o.c;
    }
};
priority_queue<State, vector<State>, greater<State>> pq;

void solve() {
    cin >> N >> M;
    rep(i, 0, M) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        revAdj[b].push_back(a);
    }
    rep(i, 0, N) {
        rep(j, 0, MAXT+2) {
            bestDist[i][j] = INF;
        }
        bestT[i][0] = INF;
        bestT[i][1] = INF;
    }
    pq.emplace(0, 0, 0);
    bestDist[0][0] = 0;
    while (!pq.empty()) {
        State s = pq.top();
        pq.pop();
        int t = s.t;
        if (t >= MAXT) {
            t %= 2;
            t += MAXT;
        }
        if (bestDist[s.n][t] < s.c) continue;
        if (s.t >= MAXT && bestT[s.n][s.t%2] < s.t) continue;
        // cout << s.n << " " << s.c << " " << s.t << endl;
        vi& adjN = s.t % 2 == 0 ? adj[s.n] : revAdj[s.n];
        // Movement
        for (int e : adjN) {
            if (bestDist[e][t] > s.c + 1) {
                bestT[e][s.t%2] = s.t;
                bestDist[e][t] = s.c + 1;
                pq.emplace(e, s.c + 1, s.t);
            }
        }
        // Transpose
        int nt = s.t + 1;
        t = nt;
        if (t >= MAXT) {
            t %= 2;
            t += MAXT;
        }
        if (nt >= MAXT) {
            if (bestT[s.n][nt%2] > nt) {
                bestT[s.n][nt%2] = nt;
                bestDist[s.n][t] = s.c;
                pq.emplace(s.n, s.c, nt);
            } else if (bestT[s.n][nt%2] == nt && bestDist[s.n][t] > s.c) {
                bestDist[s.n][t] = s.c;
                pq.emplace(s.n, s.c, nt);
            }
        } else if (bestDist[s.n][nt] > s.c) {
            bestDist[s.n][nt] = s.c;
            pq.emplace(s.n, s.c, nt);
        }
    }
    int answer = INF;
    rep(j, 0, MAXT) {
        if (bestDist[N-1][j] != INF) {
            answer = min(bestDist[N-1][j] + (1 << j) - 1, answer);
        }
    }
    if (answer == INF) {
        // Use all transposes
        int t = min(bestT[N-1][0], bestT[N-1][1]);
        // cout << t << endl;
        answer = 1;
        rep(i, 0, t) {
            answer = answer * 2 % MOD;
        }
        answer--;
        if (answer < 0) answer += MOD;
        int newDist;
        if (t % 2 == 0) newDist = bestDist[N-1][MAXT];
        else newDist = bestDist[N-1][MAXT+1];
        answer = (answer + newDist) % MOD;
    }
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}