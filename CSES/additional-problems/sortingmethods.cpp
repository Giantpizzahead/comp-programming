#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5;

int N;
int A[MAXN], pos[MAXN];

struct BIT {
    int V[MAXN];

    void upd(int i, int v) {
        for (; i < MAXN; i+=i&-i) V[i] += v;
    }

    int query(int i) {
        int r = 0;
        for (; i > 0; i-=i&-i) r += V[i];
        return r;
    }
};

BIT bit;
bool vis[MAXN];
set<pair<int, int>> dp;

void solve() {
    cin >> N;
    rep(i, 1, N+1) {
        cin >> A[i];
        pos[A[i]] = i;
    }
    // 1) Count inversions
    ll inv = 0;
    for (int i = N; i >= 1; i--) {
        inv += bit.query(A[i]);
        bit.upd(A[i], 1);
    }
    // 2) N - Count # components
    int comps = 0;
    rep(i, 1, N+1) {
        if (!vis[i]) {
            int n = i;
            while (!vis[n]) {
                vis[n] = true;
                n = A[n];
            }
            comps++;
        }
    }
    // 3) N - LIS
    dp.emplace(-1, 0);
    rep(i, 1, N+1) {
        auto ptr = dp.lower_bound({A[i], -1});
        int lisVal = prev(ptr)->second + 1;
        if (ptr != dp.end()) dp.erase(ptr);
        dp.emplace(A[i], lisVal);
    }
    int lis = prev(dp.end())->second;
    // 4) N - Max sorted "suffix"
    int suff = 1;
    for (int i = N-1; i >= 1; i--) {
        if (pos[i] >= pos[i+1]) break;
        suff++;
    }
    // Answers
    cout << inv << ' ' << N-comps << ' ' << N-lis << ' ' << N-suff << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}