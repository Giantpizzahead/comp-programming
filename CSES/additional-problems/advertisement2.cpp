#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 2e5;

int N;
int K[MAXN], L[MAXN], R[MAXN];

stack<int> mono;

void solve() {
    cin >> N;
    for (int i = 0; i < N; i++) cin >> K[i];

    mono.push(-1);
    for (int i = 0; i < N; i++) {
        while (mono.size() > 1 && K[mono.top()] >= K[i]) {
            mono.pop();
        }
        L[i] = mono.top() + 1;
        mono.push(i);
    }

    while (!mono.empty()) mono.pop();
    mono.push(N);
    for (int i = N-1; i >= 0; i--) {
        while (mono.size() > 1 && K[mono.top()] >= K[i]) {
            mono.pop();
        }
        R[i] = mono.top() - 1;
        mono.push(i);
    }

    // cout << "L: ";
    // for (int i = 0; i < N; i++) cout << L[i] << ' ';
    // cout << endl;
    // cout << "R: ";
    // for (int i = 0; i < N; i++) cout << R[i] << ' ';
    // cout << endl;

    ll answer = 0;
    for (int i = 0; i < N; i++) answer = max((ll) (R[i] - L[i] + 1) * K[i], answer);
    cout << answer << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}