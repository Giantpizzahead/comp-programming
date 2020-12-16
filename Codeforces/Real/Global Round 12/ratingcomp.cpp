#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 300005;

int N;
int cnt[MAXN], leftLoc[MAXN], rightLoc[MAXN];
int A[MAXN];
bool works[MAXN];

void solve() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cnt[i] = 0;
        works[i] = false;
        leftLoc[i] = N;
        rightLoc[i] = -1;
    }
    for (int i = 0; i < N; i++) {
        cin >> A[i];
        cnt[A[i]]++;
        leftLoc[A[i]] = min(i, leftLoc[A[i]]);
        rightLoc[A[i]] = max(i, rightLoc[A[i]]);
    }
    if (cnt[1] != 0) works[N] = true;
    works[1] = true;
    for (int i = 1; i <= N; i++) {
        if (cnt[i] != 1) {
            works[1] = false;
            break;
        }
    }

    // Start from N
    int le = 0, re = N-1;
    for (int i = N; i >= 1; i--) {
        // Find element
        int x = N + 1 - i;
        if (leftLoc[x] == N) {
            // Doesn't exist
            break;
        } else if (leftLoc[x] != rightLoc[x]) {
            // Multiple elements; end of k-comp
            works[i] = true;
            break;  
        } else if (leftLoc[x] == le) {
            // This works
            le++;
            works[i] = true;
        } else if (leftLoc[x] == re) {
            // This works
            re--;
            works[i] = true;
        } else {
            // Invalid position; end of k-compression
            works[i] = true;
            break;
        }
    }

    for (int i = 1; i <= N; i++) cout << works[i];
    cout << '\n';
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