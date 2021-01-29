#include <iostream>

using namespace std;
using ll = long long;

const int MAXN = 100005;

int N;
ll arr[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin >> N;
    for (int i = 0; i < N; i++) cin >> arr[i];

    if (N <= 3) {
        for (int i = 0; i < N; i++) {
            cout << i+1 << ' ' << i+1 << '\n';
            cout << -arr[i] << '\n';
        }
        for (int i = N; i < 3; i++) {
            cout << "1 1\n0\n";
        }
        return 0;
    }

    cout << 1 << ' ' << N-1 << '\n';
    for (int i = 0; i < N-1; i++) {
        ll currMod = arr[i] % N;
        ll toAdd = currMod * (N-1);
        cout << toAdd << (i == N-2 ? '\n' : ' ');
        arr[i] += toAdd;
    }

    cout << N << ' ' << N << '\n';
    cout << -arr[N-1] << '\n';
    arr[N-1] = 0;

    cout << 1 << ' ' << N << '\n';
    for (int i = 0; i < N; i++) {
        cout << -arr[i] << (i == N-1 ? '\n' : ' ');
    }
    return 0;
}