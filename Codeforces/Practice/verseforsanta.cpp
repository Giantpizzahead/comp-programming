#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 100005;

int N;
long long S;
int arr[MAXN];

void solve() {
    cin >> N >> S;
    for (int i = 0; i < N; i++) cin >> arr[i];
    
    int maxI = 0;
    long long sum = 0;
    for (int i = 0; i < N; i++) {
        sum += arr[i];
        if (arr[i] > arr[maxI]) maxI = i;
        if (sum > S) {
            // Try to skip
            if (sum - arr[maxI] <= S) {
                cout << maxI+1 << endl;
            } else cout << 0 << endl;
            return;
        }
    }
    cout << 0 << endl;
}

int main() {
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) solve();
    return 0;
}