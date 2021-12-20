/*
# of inadmissible squares with N = 10^7: 7850
# of unique rows/columns with inadmissible (same by symmetry): 2029
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

int N;

void solve() {
    cin >> N;
    unordered_set<int> xs;
    int sqrtN = round(sqrt(N)) + 5;
    int numSquares = 0;
    rep(i, 1, sqrtN) {
        rep(j, 1, sqrtN) {
            int k = round(sqrt(i*i+j*j));
            if (i*i <= N && j*j <= N && i*i+j*j == k*k) {
                numSquares++;
                xs.insert(i);
                // cout << i*i << " " << j*j << " " << k*k << endl;
            }
        }
    }
    cout << sz(xs) << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}