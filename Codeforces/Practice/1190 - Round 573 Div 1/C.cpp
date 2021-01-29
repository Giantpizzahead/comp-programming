#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

int N, K;
deque<int> zeros, ones;
string S;

void solve() {
    cin >> N >> K >> S;

    // Can T win immediately?
    int left0 = N+1, left1 = N+1, right0 = -1, right1 = -1;
    rep(i, 0, N) {
        if (S[i] == '0') {
            zeros.push_back(i);
            left0 = min(i, left0);
            right0 = max(i, right0);
        } else {
            ones.push_back(i);
            left1 = min(i, left1);
            right1 = max(i, right1);
        }
    }
    if (right0 - left0 < K || right1 - left1 < K) {
        cout << "tokitsukaze\n";
        return;
    }

    // Can Q win in the 2nd turn?
    bool qMustWin = true;
    bool has0 = false, has1 = false;
    int seen0 = N+1, seen1 = N+1;
    rep(i, 0, N-K+1) {
        // Move from [i, i+K-1]
        int j = i+K-1;
        while (!zeros.empty() && zeros.front() <= j) zeros.pop_front();
        while (!ones.empty() && ones.front() <= j) ones.pop_front();
        
        // Set all to 0
        int l0 = N+1, l1 = N+1, r0 = -1, r1 = -1;
        l0 = min(left0, i);
        r0 = max(right0, j);
        l1 = (has1 ? seen1 : N+1);
        r1 = (has1 ? seen1 : -1);
        if (!ones.empty()) {
            l1 = min(ones.front(), l1);
            r1 = max(ones.back(), r1);
        }
        if (r0-l0 >= K && r1-l1 >= K) qMustWin = false;

        // Set all to 1
        l0 = N+1, l1 = N+1, r0 = -1, r1 = -1;
        l1 = min(left1, i);
        r1 = max(right1, j);
        l0 = (has0 ? seen0 : N+1);
        r0 = (has0 ? seen0 : -1);
        if (!zeros.empty()) {
            l0 = min(zeros.front(), l0);
            r0 = max(zeros.back(), r0);
        }
        if (r0-l0 >= K && r1-l1 >= K) qMustWin = false;

        if (S[i] == '0') {
            has0 = true;
            seen0 = min(i, seen0);
        }
        if (S[i] == '1') {
            has1 = true;
            seen1 = min(i, seen1);
        }
    }

    if (qMustWin) {
        cout << "quailty" << '\n';
        return;
    }

    cout << "once again\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}