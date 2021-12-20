#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 100005;

int N, A;
int L[MAXN], finalLoc[MAXN];
bool isCoin[MAXN], isWarp[MAXN];
vector<pair<int, int>> pipes[MAXN];

void solve() {
    cin >> N;
    int x;
    for (int i = 0; i < N; i++) {
        cin >> x;
        if (x == -1) isCoin[i] = true;
        else isWarp[x] = true;
        L[i] = x;
    }
    for (int i = 0; i < N; i++) {
        if (!isCoin[i] && !isWarp[i]) {
            int steps = 0, currI = i;
            while (!isCoin[currI]) {
                steps++;
                currI = L[currI];
            }
            finalLoc[i] = currI;
            pipes[currI].emplace_back(steps, i);
        }
    }
    for (int i = 0; i < N; i++) sort(pipes[i].begin(), pipes[i].end());
    cin >> A;
    for (int i = 0; i < A; i++) {
        cin >> x;
        cout << pipes[finalLoc[x]][0].second << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    // cin >> T;
    for (int i = 1; i <= T; i++) {
        solve();
    }
    return 0;
}