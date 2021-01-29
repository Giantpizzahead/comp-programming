#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const ll MOD = 1e9+7;
const int MAXN = 3e5+5, MAXM = 6e5+10;

int N, Q, M;
struct Compressed {
    int n, c;
};
Compressed P[MAXN];
ll answer = 0;
ll pow2[MAXN], pow2inv[MAXN];
pair<int, Compressed> queries[MAXN];

struct SegmentTree {
    ll V[MAXM*4+1], D[MAXM*4+1];

    SegmentTree() {
        rep(i, 0, MAXM*4+1) {
            V[i] = 0;
            D[i] = 1;
        }
    }

    void prop(int n) {
        if (D[n] == 1) return;
        V[n*2] = D[n] * V[n*2] % MOD;
        V[n*2+1] = D[n] * V[n*2+1] % MOD;
        D[n*2] = D[n] * D[n*2] % MOD;
        D[n*2+1] = D[n] * D[n*2+1] % MOD;
        D[n] = 1;
    }

    void merge(int n) {
        V[n] = (V[n*2] + V[n*2+1]) % MOD;
    }

    void mult(int l, int r, int v, int n = 1, int lb = 0, int ub = M-1) {
        if (l > ub || r < lb) return;
        else if (lb >= l && ub <= r) {
            V[n] = V[n] * v % MOD;
            D[n] = D[n] * v % MOD;
            return;
        }
        prop(n);
        mult(l, r, v, n*2, lb, (lb+ub)/2);
        mult(l, r, v, n*2+1, (lb+ub)/2+1, ub);
        merge(n);
    }

    void set(int i, int v, int n = 1, int lb = 0, int ub = M-1) {
        if (lb == ub) {
            V[n] = v;
            return;
        }
        prop(n);
        if (i > (lb+ub)/2) set(i, v, n*2+1, (lb+ub)/2+1, ub);
        else set(i, v, n*2, lb, (lb+ub)/2);
        merge(n);
    }

    ll query(int l, int r, int n = 1, int lb = 0, int ub = M-1) {
        if (l > ub || r < lb) return 0;
        else if (lb >= l && ub <= r) return V[n];
        prop(n);
        return (query(l, r, n*2, lb, (lb+ub)/2) + query(l, r, n*2+1, (lb+ub)/2+1, ub)) % MOD;
    }
};
SegmentTree segPos, segNeg, segCnt;

ll powmod(ll b, ll e) {
    ll r = 1;
    while (e > 0) {
        if (e % 2 == 1) r = r * b % MOD;
        b = b * b % MOD;
        e /= 2;
    }
    return r;
}

vector<pair<int, int>> coordComp, initialVals;

void solve() {
    pow2[0] = 1;
    pow2inv[0] = 1;
    rep(i, 1, MAXN) {
        pow2[i] = pow2[i-1] * 2 % MOD;
        pow2inv[i] = powmod(pow2[i], MOD-2);
        // cout << pow2[i] << " " << pow2inv[i] << endl;
    }
    cin >> N;
    rep(i, 0, N) {
        cin >> P[i].n;
        coordComp.emplace_back(P[i].n, i);
        initialVals.emplace_back(P[i].n, i);
    }
    sort(all(initialVals));
    cin >> Q;
    rep(i, 0, Q) {
        cin >> queries[i].first >> queries[i].second.n;
        queries[i].first--;
        coordComp.emplace_back(queries[i].second.n, -i-1);
    }
    sort(all(coordComp));
    for (int i = 0; i < sz(coordComp); i++) {
        auto& p = coordComp[i];
        if (p.second < 0) {
            int j = -p.second-1;
            queries[j].second.c = i;
        } else {
            P[p.second].c = i;
        }
    }
    M = N+Q;

    // rep(i, 0, N) cout << P[i].c << ' ';
    // cout << endl;
    // rep(i, 0, Q) cout << queries[i].first << ' ' << queries[i].second.c << endl;

    // Fill initial values
    rep(i, 0, N) {
        int j = initialVals[i].second;
        // cout << "set " << P[j].c << endl;
        segCnt.set(P[j].c, 1);
        segPos.set(P[j].c, pow2[i] * P[j].n % MOD);
        segNeg.set(P[j].c, pow2inv[i] * P[j].n % MOD);
        // cout << pow2inv[i] << " * " << P[j].n << " * " << segPos.query(0, P[j].c-1) << endl;
        answer += pow2inv[i] * P[j].n % MOD * segPos.query(0, P[j].c-1) % MOD;
        answer %= MOD;
    }
    cout << answer * pow2inv[1] % MOD << '\n';

    // Queries
    rep(q, 0, Q) {
        int i = queries[q].first, n = queries[q].second.n, c = queries[q].second.c;
        // rep(j, 0, M) cout << segCnt.query(j, j) << ' ';
        // cout << endl;
        // rep(j, 0, M) cout << segPos.query(j, j) << ' ';
        // cout << endl;
        // rep(j, 0, M) cout << segNeg.query(j, j) << ' ';
        // cout << endl;
        // Remove old position
        int on = P[i].n, oc = P[i].c;
        int loc = segCnt.query(0, oc-1);
        ll seg1 = segPos.query(0, oc-1);
        ll seg2 = segNeg.query(oc+1, M-1);
        // Remove sumB(k)
        answer -= pow2inv[loc] * on % MOD * seg1 % MOD;
        // Remove influence of k on sumB(k+1...)
        answer -= seg2 * pow2[loc] % MOD * on % MOD;
        // Adjust powers of 2 for sumB(k+1...)
        answer += seg2 * seg1 % MOD;
        // cout << "remove " << pow2inv[loc] * on % MOD * segPos.query(0, oc-1) % MOD << endl;
        // cout << "remove " << segNeg.query(oc+1, M-1) * pow2[loc] % MOD * on % MOD << endl;
        // cout << "add " << segNeg.query(oc+1, M-1) * segPos.query(0, oc-1) % MOD << endl;
        // Update segment trees
        segCnt.set(oc, 0);
        segPos.set(oc, 0);
        segPos.mult(oc+1, M-1, pow2inv[1]);
        segNeg.set(oc, 0);
        segNeg.mult(oc+1, M-1, pow2[1]);

        // Add new position
        P[i].n = n;
        P[i].c = c;
        loc = segCnt.query(0, c-1);
        seg1 = segPos.query(0, c-1);
        seg2 = segNeg.query(c+1, M-1);
        // Add sumB(k)
        answer += pow2inv[loc] * n % MOD * seg1 % MOD;
        // Add influence of k on sumB(k+1...)
        answer += seg2 * pow2[loc] % MOD * n % MOD * pow2inv[1] % MOD;
        // Adjust powers of 2 for sumB(k+1...)
        answer -= seg2 * seg1 % MOD * pow2inv[1] % MOD;
        // cout << "add " << pow2inv[loc] * n % MOD * segPos.query(0, c-1) % MOD << endl;
        // cout << "add " << segNeg.query(c+1, M-1) * pow2[loc] % MOD * n % MOD * pow2inv[1] % MOD<< endl;
        // cout << "remove " << segNeg.query(c+1, M-1) * segPos.query(0, c-1) % MOD * pow2inv[1] % MOD << endl;
        // Update segment trees
        segCnt.set(c, 1);
        segPos.set(c, pow2[loc] * n % MOD);
        segPos.mult(c+1, M-1, pow2[1]);
        segNeg.set(c, pow2inv[loc] * n % MOD);
        segNeg.mult(c+1, M-1, pow2inv[1]);
        answer = (answer % MOD + MOD) % MOD;

        cout << answer * pow2inv[1] % MOD << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}