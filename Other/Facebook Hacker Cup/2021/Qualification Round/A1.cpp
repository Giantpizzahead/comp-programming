#include <iostream>
#include <vector>
#include <algorithm>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
using namespace std;
using ll = long long;

bool isVowel(int x) {
    return x == 0 || x == 4 || x == 8 || x == 14 || x == 20;
}

// Simulates how many seconds are needed to make S consistent
int tryChar(vector<int>& S, int C) {
    int ans = 0;
    bool targetVowel = isVowel(C);
    for (int x : S) {
        if (x == C) continue;
        else if (isVowel(x) != targetVowel) ans++;
        else ans += 2;
    }
    return ans;
}

void solve() {
    string str; cin >> str;
    vector<int> S(sz(str));
    rep(i, 0, sz(str)) S[i] = str[i] - 'A';
    
    // Try changing to every character
    int ans = 999999999;
    rep(i, 0, 26) ans = min(tryChar(S, i), ans);
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    int T; cin >> T;
    rep(i, 0, T) {
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    return 0;
}