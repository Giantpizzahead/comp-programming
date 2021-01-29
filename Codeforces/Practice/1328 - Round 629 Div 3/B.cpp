#include <iostream>

using namespace std;
using ll = long long;

int T;
ll N, K;

int main() {
    cin >> T;
    for (int i = 0; i < T; i++) {
        cin >> N >> K;
        int firstB = 1;
        ll sum = 0;
        for (firstB = 1; firstB <= N; firstB++) {
            sum += firstB;
            if (K <= sum) break;
        }
        sum -= firstB;
        K -= sum;

        int b1i = N - 1 - firstB;
        int b2i = N - K;
        for (int j = 0; j < N; j++) {
            if (j == b1i || j == b2i) cout << 'b';
            else cout << 'a';
        }
        cout << '\n';
    }
    return 0;
}