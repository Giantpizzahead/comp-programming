/**
 * The points can be split greedily using parity. If all the
 * points have the same parity, manipulate the coordinate grid
 * to squish the points closer toether, and recurse.
 * 
 * Runtime: O(N * probably log(N)?)
 */

#include <iostream>
using namespace std;

const int MAXN = 1000;
int N;
int X[MAXN], Y[MAXN];

void solve() {
    int numEven = 0, numOdd = 0;
    for (int i = 0; i < N; i++) {
        if ((X[i] + Y[i]) % 2 == 0) numEven++;
        else numOdd++;
    }

    if (numEven == 0) {
        // All odd; +1 to all point y
        for (int i = 0; i < N; i++) Y[i]++;
    }

    if (numOdd == 0 || numEven == 0) {
        // All even; rotate coordinate grid -45 degrees
        for (int i = 0; i < N; i++) {
            int ox = X[i], oy = Y[i];
            int nx = (X[i] - Y[i]) / 2;
            int ny = (X[i] + Y[i]) / 2;
            X[i] = nx;
            Y[i] = ny;
        }
        // Recurse
        solve();
    } else {
        // Solvable right now
        cout << numEven << '\n';
        for (int i = 0; i < N; i++) {
            if ((X[i] + Y[i]) % 2 == 0) {
                cout << i+1 << (--numEven == 0 ? '\n' : ' ');
            }
        }
    }
}

int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> X[i] >> Y[i];
    }
    solve();
}