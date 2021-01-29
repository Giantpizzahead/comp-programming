#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAXN = 500005;
const ll INF = 1e18;

int N, K, M;
int P[MAXN];

// Check if splitting as soon as sum < X will use <= K resets.
bool check(ll X) {
    int resetsLeft = K;
    ll currBonus = 0, currSum = 0;
    for (int i = 0; i < N-K; i++) {
        if (currSum + currBonus < X) {
            // Split (use up worst one instead of this one)
            currBonus = 0;
            currSum = 0;
            resetsLeft--;
            i--;
            if (resetsLeft < 0) return false;
        }
        if (currBonus < 0) currSum += currBonus;
        currBonus += P[i];
    }
    return resetsLeft >= 0;
}

// Split when sum < X or sum - 1 < X and i >= S.
bool check(ll X, int S) {
    int resetsLeft = K;
    ll currBonus = 0, currSum = 0;
    for (int i = 0; i < N-K; i++) {
        if (currSum + currBonus < X || (i >= S && currSum + currBonus - 1 < X)) {
            // Split (use up worst one instead of this one)
            currBonus = 0;
            currSum = 0;
            resetsLeft--;
            i--;
            if (resetsLeft < 0) return false;
        }
        if (currBonus < 0) currSum += currBonus;
        currBonus += P[i];
    }
    return resetsLeft >= 0;
}

vector<int> points;

void doGreedy(ll X, int S) {
    for (int i = 0; i < N; i++) points.push_back(P[i]);
    int resetsLeft = K;
    ll currBonus = 0, currSum = 0, answer = 0;
    for (int i = 0; i < points.size(); i++) {
        if (currSum + currBonus < X || (i >= S && currSum + currBonus - 1 < X)) {
            // Split (use up worst one instead of this one)
            currBonus = 0;
            currSum = 0;
            resetsLeft--;
            i--;
            points.pop_back();
            // cout << "split" << endl;
        }
        // cout << "at " << points[i] << endl;
        if (currBonus < 0) currSum += currBonus;
        answer += currBonus;
        currBonus += points[i];
    }
    cout << answer << endl;
}

void solve() {
    ll low = -INF, high = 0;
    while (low < high) {
        ll mid = (low + high + 1) / 2;
        if (check(mid)) {
            low = mid;
        } else {
            high = mid - 1;
        }
    }
    // cout << "split at " << low << endl;

    // Find first place to start splitting before
    int low2 = 1, high2 = N;
    while (low2 < high2) {
        int mid2 = (low2 + high2) / 2;
        if (check(low, mid2)) {
            high2 = mid2;
        } else {
            low2 = mid2 + 1;
        }
    }
    // cout << "first more " << low2 << endl;

    // Solve by greedily splitting at this
    doGreedy(low, low2);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> K;
    for (int i = 0; i < N; i++) cin >> P[i];
    sort(P, P+N, greater<int>());
    solve();
    return 0;
}