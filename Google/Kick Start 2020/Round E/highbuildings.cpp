#include <iostream>

using namespace std;

const int MAXN = 100;

int N, A, B, C;
int arr[MAXN];

void solve(int tn) {
    cin >> N >> A >> B >> C;
    A -= C;
    B -= C;
    if (A + B + C > N) {
        cout << "Case #" << tn << ": IMPOSSIBLE\n";
        return;
    }
    int leftOver = N - A - B - C;

    if (N > 2) {
        if (leftOver > N - 2) {
            cout << "Case #" << tn << ": IMPOSSIBLE\n";
            return;
        }
        int i = 0;
        for (int j = 0; j < A; i++, j++) {
            arr[i] = 2;
        }
        bool leftOverPlaced = false;
        if (A != 0) {
            leftOverPlaced = true;
            for (int j = 0; j < leftOver; i++, j++) {
                arr[i] = 1;
            }
        }
        arr[i++] = 3;
        if (!leftOverPlaced) {
            leftOverPlaced = true;
            for (int j = 0; j < leftOver; i++, j++) {
                arr[i] = 1;
            }
        }
        for (int j = 1; j < C; i++, j++) {
            arr[i] = 3;
        }
        for (int j = 0; j < B; i++, j++) {
            arr[i] = 2;
        }
    } else if (N == 1) {
        if (C != 1) {
            cout << "Case #" << tn << ": IMPOSSIBLE\n";
            return;
        } else arr[0] = 1;
    } else {
        if (C == 2) {
            arr[0] = 1;
            arr[1] = 1;
        } else if (C == 0) {
            cout << "Case #" << tn << ": IMPOSSIBLE\n";
            return;
        } else if (A == 1 && B == 0) {
            arr[0] = 1;
            arr[1] = 2;
        } else if (B == 1 && A == 0) {
            arr[0] = 2;
            arr[1] = 1;
        } else {
            cout << "Case #" << tn << ": IMPOSSIBLE\n";
            return;
        }
    }

    cout << "Case #" << tn << ": ";
    for (int i = 0; i < N; i++) {
        cout << arr[i] << (i == N-1 ? '\n' : ' ');
    }
}

int main() {
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) solve(i);
    return 0;
}