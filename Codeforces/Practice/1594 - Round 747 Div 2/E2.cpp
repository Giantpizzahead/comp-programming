/*
Solution: 
Runtime: 
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const ll MOD = 1e9+7;
const int MAXK = 62;

int K, N;
ll defaultWays[MAXK];

ll powmod(ll b, ll e) {
    ll r = 1;
    while (e > 0) {
        if (e & 1) r = r*b % MOD;
        b = b*b % MOD;
        e >>= 1;
    }
    return r;
}

struct State {
    ll a, b, c;
};
unordered_map<ll, State> states[MAXK];
unordered_map<ll, int> toAdd[MAXK];

State getInitialState(int k) {
    State s = {defaultWays[k], defaultWays[k], defaultWays[k]};
    return s;
}

void solve() {
    cin >> K;
    defaultWays[1] = 1;
    rep(i, 2, K+1) {
        defaultWays[i] = (defaultWays[i-1]*2) * (defaultWays[i-1]*2) % MOD;
    }
    cin >> N;
    rep(i, 0, N) {
        ll v; cin >> v;
        string s; cin >> s;
        int t;
        if (s == "white" || s == "yellow") t = 0;
        else if (s == "green" || s == "blue") t = 1;
        else t = 2;
        for (int k = K-1; k >= 0; k--) {
            if (v & (1LL << k)) {
                // Process at this level
                toAdd[k][v] = t;
                break;
            }
        }
    }

    // Start processing manually
    for (int k = K-1; k >= 0; k--) {
        // Merge previous states
        while (!states[k+1].empty()) {
            auto ptr1 = states[k+1].begin();
            ll v = ptr1->first;
            State s1 = ptr1->second;
            auto ptr2 = states[k+1].find(v^1);
            if (ptr2 == states[k+1].end()) {
                // Merge with a default state
                states[k+1][v^1] = getInitialState(K-1-k);
                ptr2 = states[k+1].find(v^1);
            }
            v >>= 1;
            State s2 = ptr2->second;

            State s = {0, 0, 0};

            int t = -1;
            auto ptr3 = toAdd[k].find(v);
            if (ptr3 != toAdd[k].end()) {
                // Fixed value for this node
                t = ptr3->second;
                toAdd[k].erase(ptr3);
            }
            if (t == 0 || t == -1) s.a = (s1.b+s1.c) * (s2.b+s2.c) % MOD;
            if (t == 1 || t == -1) s.b = (s1.a+s1.c) * (s2.a+s2.c) % MOD;
            if (t == 2 || t == -1) s.c = (s1.a+s1.b) * (s2.a+s2.b) % MOD;
            states[k][v] = s;

            states[k+1].erase(ptr1);
            states[k+1].erase(ptr2);

            // debug << k << " " << v << " = " << s.a << " " << s.b << " " << s.c << '\n';
        }
        // Add new fixed states
        while (!toAdd[k].empty()) {
            auto ptr = toAdd[k].begin();
            ll v = ptr->first;
            int t = ptr->second;
            State s = getInitialState(K-k);
            if (t != 0) s.a = 0;
            if (t != 1) s.b = 0;
            if (t != 2) s.c = 0;
            states[k][v] = s;
            toAdd[k].erase(ptr);

            // debug << k << " " << v << " = " << s.a << " " << s.b << " " << s.c << '\n';
        }
    }

    ll ans = (states[0][1].a + states[0][1].b + states[0][1].c) % MOD;
    ans = ans * powmod(2, (1LL << K) - 1 - N) % MOD;
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}