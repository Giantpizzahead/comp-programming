#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

string str;

ll val(string s) {
    // cout << s << endl;
    ll x = 1;
    for (char c : s) {
        x *= c - '0';
    }
    return x;
}

void solve() {
    cin >> str;
    ll answer = val(str);
    string partial = "";
    rep(i, 0, sz(str)) {
        // Set as not max
        if (str[i] != '0') {
            string newS = partial + ((char) (str[i]-1));
            rep(j, i+1, sz(str)) newS += '9';
            if (newS[0] == '0') newS = newS.substr(1);
            answer = max(val(newS), answer);
        }
        partial += str[i];
    }
    cout << answer << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}