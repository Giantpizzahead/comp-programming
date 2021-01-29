#include <iostream>
using namespace std;
using ll = long long;
const int MAXN = 1e6+5;

ll N;
ll sum;
ll H[MAXN], A[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> H[i];
        sum += H[i];
    }

    ll from1 = (N-1) * N / 2;
    ll start = (sum - from1 + N - 1) / N;
    // Determine where the flat part is
    int flat = N + (sum - from1 - start * N);
    for (int i = 0; i < N; i++) {
        A[i] = start;
        if (i+1 != flat) start++;
    }

    for (int i = 0; i < N; i++) cout << A[i] << ' ';
    cout << endl;
    return 0;
}