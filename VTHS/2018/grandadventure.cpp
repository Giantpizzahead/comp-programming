#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 100005;

string str;
stack<char> items;

void solve() {
    cin >> str;
    while (!items.empty()) items.pop();
    for (int i = 0; i < str.size(); i++) {
        char c = str[i];
        if (c == '$' || c == '|' || c == '*') items.push(c);
        else if (c == 't' || c == 'j' || c == 'b') {
            char d = items.empty() ? ' ' : items.top();
            if (!items.empty()) items.pop();
            if ((c == 't' && d != '|') || (c == 'j' && d != '*') || (c == 'b' && d != '$')) {
                cout << "NO\n";
                return;
            }
        }
    }
    if (items.empty()) cout << "YES\n";
    else cout << "NO\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        solve();
    }
    return 0;
}