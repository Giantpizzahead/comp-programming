#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

const int MAXN = 200005;

int N;
ll K;
int arr[MAXN];

void solve() {
    cin >> N >> K;
    for (int i = 0; i < N; i++) cin >> arr[i];

    K = (K % 2 == 0) ? 2 : 1;
    for (int i = 0; i < K; i++) {
        int maxI = 0;
        for (int j = 0; j < N; j++) {
            if (arr[j] > arr[maxI]) maxI = j;
        }
        int maxV = arr[maxI];
        for (int j = 0; j < N; j++) {
            arr[j] = maxV - arr[j];
        }
    }

    for (int i = 0; i < N; i++) {
        if (i != 0) cout << ' ';
        cout << arr[i];
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) solve();
    return 0;
}