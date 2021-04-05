#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const double EPS = 1e-9;

ll A, B, C;

void solve() {
    cin >> A >> B >> C;
    if (A == 0 && B == 0) {
        cout << (C == 0 ? -1 : 0) << '\n';
        return;
    }
    if (A == 0) {
        double root = (double) -C / B;
        cout << fixed << 1 << '\n' << root << '\n';
        return;
    }

    ll disc = B * B - 4 * A * C;
    if (disc < 0) {
        cout << 0 << '\n';
        return;
    }

    double root1 = (-B + sqrt(disc)) / A / 2;
    double root2 = (-B - sqrt(disc)) / A / 2;
    if (root1 > root2) swap(root1, root2);
    if (disc == 0) cout << fixed << 1 << '\n' << root1 << '\n';
    else {
        cout << fixed << 2 << '\n' << root1 << '\n' << root2 << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}