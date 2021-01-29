#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 2e5;

int N;
pair<int, int> A[MAXN];

void solve() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> A[i].second >> A[i].first;
    }
    sort(A, A+N);
    int ending = 0, answer = 0;
    for (int i = 0; i < N; i++) {
        int s = A[i].second;
        int e = A[i].first;
        if (s >= ending) {
            ending = e;
            answer++;
        }
    }
    cout << answer << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}