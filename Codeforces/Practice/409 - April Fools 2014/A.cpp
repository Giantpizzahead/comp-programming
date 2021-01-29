#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

string a, b;

void solve() {
    cin >> a >> b;
    int s = 0;
    for (int i = 0; i < sz(a); i += 2) {
        string str1 = a.substr(i, 2);
        string str2 = b.substr(i, 2);
        if (str1 == str2) continue;
        if (str1 == "8<" && str2 == "[]") s--;
        if (str1 == "[]" && str2 == "8<") s++;
        if (str1 == "8<" && str2 == "()") s++;
        if (str1 == "()" && str2 == "8<") s--;
        if (str1 == "[]" && str2 == "()") s--;
        if (str1 == "()" && str2 == "[]") s++;
    }
    if (s < 0) cout << "TEAM 1 WINS\n";
    else if (s == 0) cout << "TIE\n";
    else cout << "TEAM 2 WINS\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}