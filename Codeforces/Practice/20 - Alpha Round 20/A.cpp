#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

string S;

void solve() {
    cin >> S;
    int last = sz(S)-1;
    while (last != 0 && S[last] == '/') last--;
    rep(i, 0, last+1) if (i == 0 || S[i] != '/' || S[i-1] != '/') cout << S[i];
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}