#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using namespace std;

const int MAXN = 24 * 60 + 1;

string S;
int M, X;
bool seen[MAXN];

void solve() {
    cin >> S >> X;
    M = stoi(S.substr(0, 2)) * 60 + stoi(S.substr(3, 2));
    rep(i, 0, MAXN) seen[i] = false;
    int ans = 0;
    while (!seen[M]) {
        seen[M] = true;
        int h = M / 60;
        int m = M % 60;
        string curr = "";
        if (h < 10) curr += '0';
        curr += to_string(h);
        curr += ':';
        if (m < 10) curr += '0';
        curr += to_string(m);
        // Is this a palindrome?
        bool palin = true;
        rep(i, 0, sz(curr)/2) {
            if (curr[i] != curr[sz(curr)-1-i]) palin = false;
        }
        if (palin) ans++;
        // Next time
        M = (M + X) % (24 * 60);
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}