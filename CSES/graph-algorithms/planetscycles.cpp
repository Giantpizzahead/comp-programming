#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
const int MAXN = 2e5;
 
int N;
int T[MAXN], L[MAXN];
 
stack<int> nodes;
 
void dfs(int n, int t) {
    if (L[n] < 0) {
        // Cycle found
        int cycleLen = t + L[n];
        while (nodes.top() != n) {
            L[nodes.top()] = cycleLen;
            nodes.pop();
        }
        L[nodes.top()] = cycleLen;
        nodes.pop();
    } else {
        if (L[T[n]] <= 0) {
            L[n] = -t;
            nodes.push(n);
            dfs(T[n], t+1);
            if (L[n] < 0) {
                L[n] = L[T[n]] + 1;
                nodes.pop();
            }
        } else L[n] = L[T[n]] + 1;
    }
}
 
void solve() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> T[i];
        T[i]--;
    }
    for (int i = 0; i < N; i++) {
        if (L[i] == 0) dfs(i, 1);
    }
    for (int i = 0; i < N; i++) {
        if (i != 0) cout << ' ';
        cout << L[i];
    }
    cout << '\n';
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}