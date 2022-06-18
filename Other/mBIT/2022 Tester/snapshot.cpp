#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using namespace std;

const int MAXN = 2e5+5;

int N, K;
int X[MAXN];
int L[MAXN];
vector<vector<int>> V;

void solve() {
    cin >> N >> K;
    rep(i, 0, N) cin >> X[i];
    rep(i, 0, K) {
        int T; cin >> T;
        multiset<int> locs;
        rep(j, 0, N) {
            cin >> L[j];
            locs.insert(L[j]);
        }
        vector<int> v(N);
        rep(j, 0, N) {
            auto ptr = locs.find(X[j] - T);
            if (ptr != locs.end()) {
                // Go left
                locs.erase(ptr);
                v[j] = -1;
            } else {
                // Must go right
                ptr = locs.find(X[j] + T);
                if (ptr != locs.end()) {
                    // Go right
                    locs.erase(ptr);
                    v[j] = 1;
                } else {
                    // Invalid
                    cout << -1 << '\n';
                    return;
                }
            }
        }
        V.push_back(v);
    }
    rep(i, 0, N) {
        for (auto& v : V) {
            if (v[i] != V[0][i]) {
                cout << -1 << '\n';
                return;
            }
        }
    }
    rep(i, 0, N) cout << V[0][i] << " \n"[i==N-1];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}