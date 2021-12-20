#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 20;

int N;
int A[MAXN];

void solve() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    int Y = 20, firstDown = 30, downs = 4;
    for (int x : A) {
        downs--;
        Y += x;
        if (Y <= 0) {
            cout << "Safety\n";
            return;
        } else if (Y >= 100) {
            cout << "Touchdown\n";
            return;
        }
        if (Y >= firstDown) {
            firstDown = Y+10;
            downs = 4;
        }
        if (downs == 0) break;  // Fourth down
    }
    cout << "Nothing\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    // cin >> T;
    for (int i = 1; i <= T; i++) {
        solve();
    }
    return 0;
}