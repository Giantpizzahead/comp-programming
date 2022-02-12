/*
1 4 5 9 10
2 3 6 7 8

For first x pairs, do (min of wanted, max of unwanted)
Then for n-x, do (max of wanted, min of unwanted)

Ex: x = 2, (4, 8) (1, 7)
and (5, 2), (9, 3), (10, 6)

If a certain x doesn't work, depending on what caused it:
Ex: x = 0
(1, 2) -> In n-x pairs, wanted < unwanted
This means x needs to be larger to work
Ex: x = 4, (9, 8)
In x pairs, wanted > unwanted
This means x needs to be smaller to work
Find these bounds with 2 binary searches

Runtime: O(N * log(N))
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 4e5+5;

int N;
bool used[MAXN];
int W[MAXN], U[MAXN];

int searchLower() {
    int low = 0, high = N;
    while (low < high) {
        int mid = (low + high + 1) / 2;
        bool works = true;
        // cout << "check low " << mid << '\n';
        rep(i, 0, mid) {
            // cout << W[i]+1 << ' ' << U[N-mid+i]+1 << '\n';
            if (W[i] > U[N-mid+i]) {
                works = false;
                break;
            }
        }
        if (works) low = mid;
        else high = mid - 1;
    }
    return low;
}

int searchHigher() {
    int low = 0, high = N;
    while (low < high) {
        int mid = (low + high) / 2;
        bool works = true;
        // cout << "check high " << mid << '\n';
        rep(i, 0, N-mid) {
            // cout << W[mid+i]+1 << ' ' << U[i]+1 << '\n';
            if (W[mid+i] < U[i]) {
                works = false;
                break;
            }
        }
        if (works) high = mid;
        else low = mid + 1;
    }
    return low;
}

void solve() {
    cin >> N;
    rep(i, 0, 2*N) used[i] = false;
    rep(i, 0, N) {
        cin >> W[i];
        W[i]--;
        used[W[i]] = true;
    }
    int j = 0;
    rep(i, 0, 2*N) if (!used[i]) U[j++] = i;

    // rep(i, 0, N) cout << W[i] <<  " \n"[i==N-1];
    // rep(i, 0, N) cout << U[i] <<  " \n"[i==N-1];

    // Binary searches
    int higherX = searchLower();
    int lowerX = searchHigher();
    cout << max(higherX - lowerX + 1, 0) << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}