#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 1001;

int N, Q;
int pre[MAXN][MAXN];

void solve() {
    cin >> N >> Q;
    for (int i = 1; i <= N; i++) {
        string str;
        cin >> str;
        for (int j = 1; j <= N; j++) {
            pre[i][j] = str[j-1] == '*';
        }
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            pre[i][j] += pre[i-1][j] + pre[i][j-1] - pre[i-1][j-1];
        }
    }
    for (int i = 0; i < Q; i++) {
        int y1, x1, y2, x2;
        cin >> y1 >> x1 >> y2 >> x2;
        cout << pre[y2][x2] - pre[y1-1][x2] - pre[y2][x1-1] + pre[y1-1][x1-1] << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}