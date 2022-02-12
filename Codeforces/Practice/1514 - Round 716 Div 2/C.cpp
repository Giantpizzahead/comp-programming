#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

int N;
vector<int> V;

int gcd(int a, int b) {
    if (a == 0) return b;
    else return gcd(b % a, a);
}

void solve() {
    cin >> N;
    int x = 1;
    rep(i, 2, N) {
        if (gcd(i, N) != 1) continue;
        x = ((ll) x * i) % N;
        V.push_back(i);
    }
    int ans = sz(V) + 1;
    if (x != 1) ans--;
    cout << ans << '\n' << 1;
    for (int v : V) {
        if (x == v) continue;
        cout << ' ' << v;
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}