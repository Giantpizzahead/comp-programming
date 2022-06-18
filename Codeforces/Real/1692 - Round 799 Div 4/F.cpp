#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using namespace std;

const int MAXN = 2e5+5;

int N, M;
int cnt[10];
vector<int> V;

void solve() {
    cin >> N;
    rep(i, 0, 10) cnt[i] = 0;
    V.clear();
    M = 0;
    rep(i, 0, N) {
        int x; cin >> x; x %= 10;
        if (cnt[x]++ < 3) {
            V.push_back(x % 10);
            M++;
        }
    }
    rep(i, 0, M) rep(j, 0, M) rep(k, 0, M) {
        if (i == j || i == k || j == k) continue;
        if ((V[i] + V[j] + V[k]) % 10 == 3) {
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}