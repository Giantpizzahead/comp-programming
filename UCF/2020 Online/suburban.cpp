#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 100005;

int N;

void solve() {
    cin >> N;
    int answer = 9999999;
    for (int i = 0; i*i <= N; i++) {
        int target = N - i*i;
        int other = round(sqrt(target));
        if (other * other == target) answer = min(i + other, answer);
    }
    if (answer == 9999999) cout << -1 << '\n';
    else cout << answer << '\n';
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