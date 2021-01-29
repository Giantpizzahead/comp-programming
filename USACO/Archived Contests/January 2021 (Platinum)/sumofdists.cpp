#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
using namespace std;
using ll = long long;

const int MAXK = 50005, MAXN = 1e5+5;
const ll MOD = 1e9+7;

ll powmod(ll b, ll e) {
    ll r = 1;
    while (e > 0) {
        if (e % 2 == 1) r = r * b % MOD;
        b = b * b % MOD;
        e /= 2;
    }
    return r;
}

int K;
int N[MAXK], M[MAXK];
vector<int> adj[MAXN], visEven[MAXK], visOdd[MAXK], seen[MAXK];

int currK;
queue<pair<int, int>> q;
void bfsVis(int n, int d) {
    for (int e : adj[n]) {
        int nd = d+1;
        if (nd % 2 == 0 && visEven[currK][e] == -1) {
            visEven[currK][e] = nd;
            q.push({e, nd});
        } else if (nd % 2 == 1 && visOdd[currK][e] == -1) {
            visOdd[currK][e] = nd;
            q.push({e, nd});
        }
    }
}

struct Loc {
    int v, i, j;
};
vector<Loc> locs;

ll evenMult, oddMult, bothMult, answer;
int even0, odd0, both0;
int evenNum[MAXK], oddNum[MAXK], bothNum[MAXK];

void solve() {
    cin >> K;
    rep(i, 0, K) {
        cin >> N[i] >> M[i];
        visEven[i].resize(N[i]);
        visOdd[i].resize(N[i]);
        seen[i].resize(N[i]);
        rep(j, 0, N[i]) {
            adj[j].clear();
            visEven[i][j] = -1;
            visOdd[i][j] = -1;
            seen[i][j] = 0;
        }
        rep(j, 0, M[i]) {
            int a, b;
            cin >> a >> b;
            a--, b--;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        q.push({0, 0});
        visEven[i][0] = 0;
        currK = i;
        while (!q.empty()) {
            auto p = q.front();
            q.pop();
            bfsVis(p.first, p.second);
        }

        rep(j, 0, N[i]) {
            if (visEven[i][j] != -1) locs.push_back({visEven[i][j], i, j});
            if (visOdd[i][j] != -1) locs.push_back({visOdd[i][j], i, j});
        }
    }
    locs.push_back({MOD, 0, 0});
    sort(all(locs), [](const Loc& a, const Loc& b) {
        return a.v < b.v;
    });

    // rep(i, 0, K) {
    //     cout << i << ":\n";
    //     rep(j, 0, N[i]) cout << visEven[i][j] << ' ';
    //     cout << endl;
    //     rep(j, 0, N[i]) cout << visOdd[i][j] << ' ';
    //     cout << endl;
    // }

    evenMult = 0;
    oddMult = 0;
    bothMult = 0;
    answer = 0;
    even0 = K;
    odd0 = K;
    both0 = K;
    rep(i, 0, K) {
        evenNum[i] = 0;
        oddNum[i] = 0;
    }

    ll lastEven = 0, lastOdd = 0, lastBoth = 0;
    int lastV = -1;
    for (auto& p : locs) {
        // cout << "eval " << p.first << " " << p.second << endl;
        if (p.v != lastV) {
            // Add to answer now
            if (lastV % 2 == 0) {
                ll toAdd = ((evenMult - lastEven) - (bothMult - lastBoth)) * lastV;
                toAdd = (toAdd % MOD + MOD) % MOD;
                // cout << "even added " << toAdd << endl;
                answer = (answer + toAdd) % MOD;
                lastV = p.v;
                lastEven = evenMult;
            } else {
                ll toAdd = ((oddMult - lastOdd) - (bothMult - lastBoth)) * lastV;
                toAdd = (toAdd % MOD + MOD) % MOD;
                // cout << "odd added " << toAdd << endl;
                answer = (answer + toAdd) % MOD;
                lastV = p.v;
                lastOdd = oddMult;
            }
            lastBoth = bothMult;
        }

        if (++seen[p.i][p.j] == 2) {
            // Both needs to update
            ll excludeMult = bothMult * powmod(bothNum[p.i], MOD-2) % MOD;
            bothMult = (bothMult + excludeMult) % MOD;
            if (bothNum[p.i]++ == 0) {
                if (--both0 == 0) {
                    // Multiply
                    bothMult = 1;
                    rep(i, 0, K) bothMult = bothMult * bothNum[i] % MOD;
                }
            }
        }

        // Update mult
        if (p.v % 2 == 0) {
            ll excludeMult = evenMult * powmod(evenNum[p.i], MOD-2) % MOD;
            evenMult = (evenMult + excludeMult) % MOD;
            if (evenNum[p.i]++ == 0) {
                if (--even0 == 0) {
                    // Multiply
                    evenMult = 1;
                    rep(i, 0, K) evenMult = evenMult * evenNum[i] % MOD;
                }
            }
        } else {
            ll excludeMult = oddMult * powmod(oddNum[p.i], MOD-2) % MOD;
            oddMult = (oddMult + excludeMult) % MOD;
            if (oddNum[p.i]++ == 0) {
                if (--odd0 == 0) {
                    // Multiply
                    oddMult = 1;
                    rep(i, 0, K) oddMult = oddMult * oddNum[i] % MOD;
                }
            }
        }
    }

    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}