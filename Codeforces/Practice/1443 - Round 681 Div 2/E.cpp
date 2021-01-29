#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5, MAXM = 15;

int N, M, Q;
ll K;

int P[MAXM];
ll fact[MAXM], pre[MAXN];

void genKth(ll K, int i = 0) {
    if (i == M-1) {
        P[i] = 1;
        return;
    }
    int cnt = K / fact[M-1-i];
    P[i] = cnt + 1;
    genKth(K - cnt*fact[M-1-i], i+1);
    rep(j, i+1, M) {
        if (P[j] >= P[i]) P[j]++;
    }
}

void solve() {
    fact[0] = 1;
    rep(i, 1, MAXM) fact[i] = fact[i-1] * i;
    cin >> N >> Q;
    pre[0] = 1;
    rep(i, 1, N) pre[i] = pre[i-1] + i + 1;
    M = min(N, 14);
    int t, a, b;
    rep(i, 0, Q) {
        cin >> t;
        if (t == 1) {
            // Sum
            cin >> a >> b;
            a--;
            b--;
            ll answer = 0;
            if (b < N-M) {
                // Only prefix
                answer = pre[b] - (a == 0 ? 0 : pre[a-1]);
            } else {
                // Goes into permutation
                int c = max(a, N-M);
                // cout << a << " " << b << " " << c << endl;
                if (c != a) {
                    answer += pre[c-1] - (a == 0 ? 0 : pre[a-1]);
                }
                genKth(K);
                a = c - (N-M);
                b = b - (N-M);
                rep(j, a, b+1) answer += P[j] + (N-M);
            }
            cout << answer << endl;
        } else {
            // Next perm
            cin >> a;
            K += a;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}