#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1e5+5;

int N;
int A[MAXN];
struct Triple {
    int i, j, k;
};
vector<Triple> moves;

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> A[i];
    if (N % 2 == 0) {
        int xorSum = 0;
        rep(i, 0, N) xorSum ^= A[i];
        if (xorSum != 0) {
            cout << "NO\n";
            return;
        }
        N--;
    }
    // Handle odd case (even will work since XOR sum is 0)
    for (int i = 0; i < N-2; i += 2) {
        moves.push_back({i, i+1, i+2});
    }
    for (int i = 0; i < N-2; i += 2) {
        moves.push_back({i, i+1, N-1});
    }
    cout << "YES\n" << sz(moves) << '\n';
    for (auto& m : moves) cout << m.i+1 << ' ' << m.j+1 << ' ' << m.k+1 << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}