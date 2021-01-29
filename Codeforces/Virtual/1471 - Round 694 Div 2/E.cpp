#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int WAIT = 300;
int N, K, R;

int query(int i) {
    cout << "? " << i+1 << "\n";
    cout.flush();
    int a;
    cin >> a;
    R++;
    return a;
}

void binarySearch(int l) {
    int r = l + min(R, N/2);
    l++;
    // cout << "bin search " << l << " to " << r << endl;
    while (l < r) {
        int mid = (l+r)/2;
        int a = query(mid%N);
        if (a > K) r = mid-1;
        else if (a < K) l = mid+1;
        else {
            l = mid;
            r = mid;
        }
    }
    cout << "! " << l%N+1 << endl;
}

void solve() {
    cin >> N >> K;
    // Wait
    rep(i, 0, WAIT) query(0);
    // R = WAIT;

    // Find - person
    int minusLoc = 0;
    if (N > 650) {
        for (;; minusLoc += WAIT-2) {
            int a = query(minusLoc);
            if (a < K) {
                // Minus found
                binarySearch(minusLoc);
                return;
            }
        }
    } else {
        for (;; minusLoc++) {
            int a = query(minusLoc);
            if (a < K) {
                // Minus found
                binarySearch(minusLoc);
                return;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}