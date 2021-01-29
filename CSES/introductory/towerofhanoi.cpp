#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 17;

int N;
int loc[4];
vector<pair<int, int>> moves[MAXN];

void solve() {
    cin >> N;
    rep(i, 1, N+1) {
        // Move i-1 from left to middle
        loc[1] = 1, loc[2] = 3, loc[3] = 2;
        for (auto& p : moves[i-1]) {
            moves[i].emplace_back(loc[p.first], loc[p.second]);
        }
        // Move ith from left to right
        moves[i].emplace_back(1, 3);
        // Move i-1 from middle to right
        loc[1] = 2, loc[2] = 1, loc[3] = 3;
        for (auto& p : moves[i-1]) {
            moves[i].emplace_back(loc[p.first], loc[p.second]);
        }
    }
    cout << sz(moves[N]) << '\n';
    for (auto& p : moves[N]) cout << p.first << ' ' << p.second << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}