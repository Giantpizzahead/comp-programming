#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

const int MAXN = 200005;

int N;
int arr[MAXN];

void solve() {
    cin >> N;
    for (int i = 0; i < N; i++) cin >> arr[i];

    int furthestLeft = N-1;
    ll answer = 0;
    for (int i = N-1; i > 0; i--) {
        if (arr[i] < arr[i-1]) {
            answer += arr[i-1] - arr[i];
            arr[i] = arr[i-1];
        }
    }
    cout << answer << endl;
}

int main() {
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) solve();
    return 0;
}