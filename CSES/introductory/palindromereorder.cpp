#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int cnt[256];
string str;

void solve() {
    cin >> str;
    for (char c : str) cnt[c]++;

    str = "";
    char middle = '?';
    for (int i = 0; i < 256; i++) {
        while (cnt[i] > 1) {
            str += (char) i;
            cnt[i] -= 2;
        }
        if (cnt[i] == 1) {
            if (middle != '?') {
                cout << "NO SOLUTION\n";
                return;
            }
            middle = i;
        }
    }

    cout << str;
    if (middle != '?') cout << middle;
    reverse(str.begin(), str.end());
    cout << str << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}