#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

int A, B, sum0, sum1;
vi ansA, ansB;

void solve() {
    cin >> A >> B;
    while (sum0+1+sum1 <= A + B) {
        sum0++;
        sum1 += sum0;
    }
    for (int i = sum0; i > 0; i--) {
        if (A >= i) {
            A -= i;
            ansA.push_back(i);
        } else {
            B -= i;
            ansB.push_back(i);
        }
    }
    cout << sz(ansA) << '\n';
    rep(i, 0, sz(ansA)) {
        if (i != 0) cout << ' ';
        cout << ansA[i];
    }
    cout << '\n';
    cout << sz(ansB) << '\n';
    rep(i, 0, sz(ansB)) {
        if (i != 0) cout << ' ';
        cout << ansB[i];
    }
    cout << '\n';
    // cout << sum0 << " " << sum1 << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}