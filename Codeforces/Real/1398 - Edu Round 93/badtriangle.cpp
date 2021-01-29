#include <iostream>

using namespace std;

int N;
int arr[50000];

void solve() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    if (arr[0] + arr[1] > arr[N-1]) {
        cout << -1 << endl;
    } else {
        cout << "1 2 " << N << endl;
    }
}

int main() {
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) solve();
    return 0;
}