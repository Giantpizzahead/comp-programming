#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 1e5+5;
const ll MOD = 1e9+7;

int N;
int A[MAXN];
ll ans;

set<vector<int>> seen;

void dfs(vector<int>& s) {
    // for (int x : s) cout << x << " ";
    // cout << endl;
    seen.insert(s);
    ans++;
    rep(j, 0, N-1) {
        if (abs(s[j] - s[j+1]) != 1) continue;
        vector<int> ns(s);
        swap(ns[j], ns[j+1]);
        if (!seen.count(ns)) dfs(ns);
    }
}

void brute() {
    ans = 0;
    seen.clear();
    vector<int> s(N);
    rep(i, 0, N) s[i] = A[i];
    dfs(s);
}

void plusMod(ll& a, ll b) {
    a = (a+b) % MOD;
}

ll powmod(ll b, ll e) {
    ll r = 1;
    while (e > 0) {
        if (e & 1) r = r*b % MOD;
        b = b*b % MOD;
        e >>= 1;
    }
    return r;
}

ll fact(ll n) {
    ll r = 1;
    rep(i, 2, n+1) r = r*i % MOD;
    return r;
}

// Track the nearest 4 values
map<vector<int>, ll> dp[MAXN];
void nearby() {
    rep(i, 0, N+1) dp[i].clear();
    int K = 4;
    vector<int> s(K);
    rep(i, 0, K) s[i] = -5;
    dp[0][s] = 1;
    rep(i, 0, N) {
        for (auto& p : dp[i]) {
            // Forward trans
            vector<int> curr(K+1), ns(K);
            rep(j, 0, K) curr[j] = p.first[j];
            curr[K] = A[i];
            // Attempt to swap
            rep(k, 0, K+1) {
                rep(j, 0, K) ns[j] = curr[j+1];
                plusMod(dp[i+1][ns], p.second);
                if (k == K || abs(curr[K-k] - curr[K-k-1]) != 1) break;
                swap(curr[K-k], curr[K-k-1]);
            }
        }
    }
    ans = 0;
    for (auto& p : dp[N]) ans = (ans + p.second) % MOD;
}

void mathy() {
    int k = 0;
    rep(i, 0, N) if (A[i] == 1) k++;
    ans = fact(N) * powmod(fact(k), MOD-2) % MOD * powmod(fact(N-k), MOD-2) % MOD;
}

void solve() {
    cin >> N;
    rep(i, 0, N) {
        cin >> A[i];
        A[i]--;
    }
    if (N <= 10) brute();
    else {
        bool allIn = true;
        rep(i, 0, N) if (A[i] > 3) allIn = false;
        if (allIn) mathy();
        else nearby();
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}