#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXX = 1e6+1;

int N;
int D[MAXX];

void solve() {
    rep(i, 1, MAXX) {
        for (int j = i; j < MAXX; j += i) D[j]++;
    }
    cin >> N;
    rep(i, 0, N) {
        int x;
        cin >> x;
        cout << D[x] << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}