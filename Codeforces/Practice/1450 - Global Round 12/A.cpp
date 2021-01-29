#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 205;

int N;
string str;
char chars[MAXN];

void solve() {
    cin >> N >> str;
    for (int i = 0; i < N; i++) chars[i] = str[i];
    sort(chars, chars+N);
    for (int i = 0; i < N; i++) cout << chars[i];
    cout << '\n';
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