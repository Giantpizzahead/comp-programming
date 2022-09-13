/*
https://codeforces.com/gym/383128/problem/I

Solution: Greedily assign velocities by going in increasing order.
Runtime: O(NlogN)
*/

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

const int MAXN = 2e5+5;

int N, K, T;
int X[MAXN], V[MAXN], L[MAXN];

void solve() {
    cin >> N >> K;
    rep(i, 0, N) cin >> X[i];
    rep(i, 0, K) {
        cin >> T;
        rep(j, 0, N) cin >> L[j];
        multiset<int> locs;
        rep(j, 0, N) locs.insert(L[j]);
        // Determine velocities of each person
        rep(j, 0, N) {
            // Go left?
            auto ptr = locs.find(X[j]-T);
            if (ptr != locs.end()) {
                locs.erase(ptr);
                if (V[j] == 1) {
                    cout << "0\n";
                    return;
                } else V[j] = -1;
            } else {
                ptr = locs.find(X[j]+T);
                if (ptr == locs.end() || V[j] == -1) {
                    cout << "0\n";
                    return;
                }
                locs.erase(ptr);
                V[j] = 1;
            }
        }
    }
    rep(i, 0, N) cout << V[i] << " \n"[i==N-1];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    solve();
    return 0;
}