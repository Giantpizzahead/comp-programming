#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

string S;
int cnt[26];

void solve() {
    cin >> S;
    rep(i, 0, sz(S)) cnt[S[i]-'a']++;
    int maxCnt = 0;
    rep(i, 0, 26) maxCnt = max(cnt[i], maxCnt);
    rep(i, 0, 26) if (cnt[i] == maxCnt) {
        cout << (char)(i+'a') << '\n';
        break;
    }
    cout << S << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}