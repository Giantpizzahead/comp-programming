#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 1005;

int N;
bool used[MAXN];
int A[MAXN], B[MAXN], C[MAXN];

void solve() {
    cin >> N;
    for (int i = 0; i < N; i++) cin >> A[i];
    for (int i = 0; i < N; i++) cin >> B[i];

    int diffIndex1 = -1, diffIndex2 = -1;
    for (int i = 0; i < N; i++) {
        if (A[i] != B[i]) {
            if (diffIndex1 == -1) diffIndex1 = i;
            else diffIndex2 = i;
        } else {
            used[A[i]] = true;
            C[i] = A[i];
        }
    }

    if (diffIndex2 == -1) {
        for (int i = 1; i <= N; i++) {
            if (!used[i]) {
                C[diffIndex1] = i;
                break;
            }
        }
    } else {
        if (used[A[diffIndex1]] || used[B[diffIndex2]]) {
            C[diffIndex1] = B[diffIndex1];
            C[diffIndex2] = A[diffIndex2];
        } else {
            C[diffIndex1] = A[diffIndex1];
            C[diffIndex2] = B[diffIndex2];
        }
    }

    for (int i = 0; i < N; i++) {
        if (i != 0) cout << ' ';
        cout << C[i];
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}