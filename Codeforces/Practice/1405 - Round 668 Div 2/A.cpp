#include <iostream>

using namespace std;
using ll = long long;

const int MAXN = 105;
int N;
int arr[MAXN];

void solve() {
    cin >> N;
    for (int i = 0; i < N; i++) cin >> arr[i];
    for (int i = N-1; i >= 0; i--) {
        cout << arr[i] << (i == 0 ? '\n' : ' ');
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) solve();
    return 0;
}