#include <bits/stdc++.h>
#define sz(x) (int) (x.size())
#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;
using ll = long long;
using vi = vector<int>;

int N;
vector<string> strings;
string curr;
int C[26];

void search(int i) {
    if (i == N) {
        strings.push_back(curr);
        return;
    }
    rep(j, 0, 26) {
        if (C[j] == 0) continue;
        C[j]--;
        curr += 'a' + j;
        search(i+1);
        C[j]++;
        curr.pop_back();
    }
}

void solve() {
    string str; cin >> str;
    for (char c : str) C[c-'a']++;
    N = sz(str);
    search(0);
    cout << sz(strings) << '\n';
    for (string& s : strings) cout << s << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}