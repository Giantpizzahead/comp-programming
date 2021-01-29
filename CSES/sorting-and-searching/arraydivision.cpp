#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 2e5+5;

int N, K;
int A[MAXN];

int check(ll s) {
    int k = 1;
    ll currSum = 0;
    for (int i = 0; i < N; i++) {
        currSum += A[i];
        if (currSum > s) {
            k++;
            currSum = A[i];
            if (A[i] > s) return INT32_MAX;
        }
    }
    return k;
}

void solve() {
    cin >> N >> K;
    for (int i = 0; i < N; i++) cin >> A[i];

    ll low = 0, high = 1e16;
    while (low < high) {
        ll mid = (low + high) / 2;
        int k = check(mid);
        if (k > K) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    cout << low << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}