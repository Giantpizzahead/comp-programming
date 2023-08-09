#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

void solve() {
    int N = 5000;
    int M = 0;
    int K = 20;
    int splits[] = {3, 3, 3, 3, 3, 3, 2, 2, 2, 2};
    cout << "N = " << N << endl;
    rep(i, 0, K) {
        if (N == 2) {
            // No more numbers needed (can immediately answer)
            cout << "+0 final with N = " << N << endl;
            break;
        } else if (N <= 4) {
            // 1 more number needed (3: Check against middle; 4: Check other bag)
            cout << "+1 final with N = " << N << endl;
            M += 1;
            break;
        }
        // Split using binary, ternary, etc. search
        int split = splits[i];
        // Optimization: If you see highest or lowest in possible range, you can answer straight away
        N -= 2;
        N = (N+split-1) / split;
        M += split;
        cout << "+" << split << " split #" << i << ": N = " << N << endl;
    }
    cout << "Result: M = " << M << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}
