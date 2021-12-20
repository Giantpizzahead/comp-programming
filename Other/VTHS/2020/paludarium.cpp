#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 500005;

int H, W;
int B[MAXN];

ll getDiff(int X) {
    ll diff = 0;
    for (int i = 0; i < W; i++) {
        int water = max(0, X-B[i]);
        int air = H-B[i]-water;
        diff += water - air;
    }
    // cout << X << ": " << diff << endl;
    return diff;
}

ll countWater(int X) {
    ll water = 0;
    for (int i = 0; i < W; i++) {
        water += max(0, X-B[i]);
    }
    return water;
}

void solve() {
    cin >> H >> W;
    for (int i = 0; i < W; i++) {
        cin >> B[i];
    }
    int low = 0, high = H;
    while (low < high) {
        int mid = (low+high+1)/2;
        ll diff = getDiff(mid);
        if (diff <= 0) low = mid;
        else high = mid-1;
    }
    ll lowDiff = getDiff(low), highDiff = getDiff(low+1);
    int best = low;
    if (abs(highDiff) < abs(lowDiff)) best = low+1;
    ll water = countWater(best);
    if (water == 0) cout << "0 0" << endl;
    else cout << best << ' ' << water << endl;
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