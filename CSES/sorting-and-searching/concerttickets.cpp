#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
using namespace std;
using ll = long long;

const int MAXN = 2e5+5;

int N, M;
multiset<int> S;
int H[MAXN], T[MAXN];

void solve() {
    cin >> N >> M;
    rep(i, 0, N) {
        cin >> H[i];
        S.insert(H[i]);
    }
    rep(i, 0, M) {
        cin >> T[i];
        auto ptr = S.upper_bound(T[i]);
        if (ptr == S.begin()) cout << -1 << '\n';
        else {
            ptr = prev(ptr);
            cout << *ptr << '\n';
            S.erase(ptr);
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}