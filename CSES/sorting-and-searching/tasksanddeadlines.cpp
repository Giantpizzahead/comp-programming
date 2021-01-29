#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 2e5;

int N;
pair<int, int> A[MAXN];

void solve() {
    cin >> N;
    int a, d;
    for (int i = 0; i < N; i++) {
        cin >> a >> d;
        A[i].first = a;
        A[i].second = d;
    }
    sort(A, A+N);
    ll answer = 0, currTime = 0;
    for (int i = 0; i < N; i++) {
        currTime += A[i].first;
        answer += A[i].second - currTime;
    }
    cout << answer << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}