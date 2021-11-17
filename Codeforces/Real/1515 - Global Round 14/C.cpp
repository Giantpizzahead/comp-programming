#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 1e5+5;

int N, M, X;
int H[MAXN];
set<pair<int, int>> T;

void solve() {
    cin >> N >> M >> X;
    rep(i, 0, N) cin >> H[i];
    rep(i, 0, M) T.insert({0, i});
    cout << "YES\n";
    rep(i, 0, N) {
        auto ptr = T.begin();
        int w = ptr->first, j = ptr->second;
        T.erase(ptr);
        cout << j+1 << " \n"[i==N-1];
        w += H[i];
        T.insert({w, j});
    }
    T.clear();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}