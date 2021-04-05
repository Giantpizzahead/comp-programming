#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5;
bool B[MAXN];
int N;
vector<int> zeros, ones;
string S;

void solve() {
    cin >> N >> S;
    zeros.clear();
    ones.clear();
    rep(i, 0, N) {
        if (S[i] == '0') zeros.push_back(i);
        else ones.push_back(i);
    }
    if (S[0] == '0' || S[N-1] == '0' || sz(zeros) % 2 == 1) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        rep(i, 0, sz(ones)/2) B[ones[i]] = true;
        rep(i, sz(ones)/2, sz(ones)) B[ones[i]] = false;
        rep(i, 0, sz(zeros)) B[zeros[i]] = i % 2;
        rep(i, 0, N) cout << (B[i] ? '(' : ')');
        cout << '\n';
        rep(i, 0, sz(zeros)) B[zeros[i]] = (i+1) % 2;
        rep(i, 0, N) cout << (B[i] ? '(' : ')');
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}