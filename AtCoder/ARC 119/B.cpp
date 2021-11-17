#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

int N;
string S, T;

void solve() {
    cin >> N >> S >> T;
    int cnt1 = 0, cnt2 = 0;
    ll answer = 0;
    rep(i, 0, N) {
        if (S[i] == '0' && T[i] == '0') {
            cnt1++, cnt2++;
            if (cnt1 != cnt2) {
                answer++;
            }
        } else if (S[i] == '0') {
            cnt1++;
            answer++;
        } else if (T[i] == '0') {
            cnt2++;
        }
    }
    if (cnt1 != cnt2) cout << -1 << "\n";
    else cout << answer << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}