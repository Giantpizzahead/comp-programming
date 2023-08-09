/*
IOI 2022 Day 1: Fish
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

struct Fish {
    int x, y, w;
    bool operator<(const Fish& o) const {
        return y < o.y;
    }
};

struct State {
    int y;
    ll ans;
    bool operator<(const State& o) const {
        return y < o.y;
    }
};

// These sets should have distinct y-valued states in increasing (or decreasing) order of ans
// Think monotonic queue
set<State> dpInc, dpDec;
vector<State> waitingInc, waitingDec;

void insertInc(int y, ll ans) {
    // Check if old y value is here
    auto ptr = dpInc.lower_bound({y, -1});
    if (ptr->y == y) {
        // Keep the one that's better
        if (ptr->ans >= ans) return;
        else dpInc.erase(ptr);
    }

    // Check if lower y value has a better answer
    ptr = prev(dpInc.lower_bound({y, -1}));
    if (ptr->ans >= ans) return;

    // Remove any higher y values with lower answers
    while (true) {
        auto ptr = dpInc.lower_bound({y, -1});
        if (ptr->ans < ans) dpInc.erase(ptr);
        else break;
    }

    // Insert
    dpInc.insert({y, ans});
    cout << "dpInc insert " << y << " " << ans << endl;
}

void insertDec(int y, ll ans) {
    // Check if old y value is here
    auto ptr = dpDec.lower_bound({y, -1});
    if (ptr->y == y) {
        // Keep the one that's better
        if (ptr->ans >= ans) return;
        else dpDec.erase(ptr);
    }

    // Check if higher y value has a better answer
    ptr = dpDec.lower_bound({y, -1});
    if (ptr->ans >= ans) return;

    // Remove any lower y values with lower answers
    while (true) {
        auto ptr = prev(dpDec.lower_bound({y, -1}));
        if (ptr->ans < ans) dpDec.erase(ptr);
        else break;
    }

    // Insert
    dpDec.insert({y, ans});
    cout << "dpDec insert " << y << " " << ans << endl;
}

ll max_weights(int N, int M, vector<int> X, vector<int> Y, vector<int> W) {
    // Store fish in a better way
    vector<vector<Fish>> colToFish(N);
    for (int i = 0; i < M; i++) {
        colToFish[X[i]].push_back({X[i], Y[i]+1, W[i]});
    }
    for (int x = 0; x < N; x++) {
        // To avoid edge cases
        colToFish[x].push_back({x, 0, 0});
        colToFish[x].push_back({x, N+1, 0});
        sort(colToFish[x].begin(), colToFish[x].end());
    }

    // Do the DP
    ll INF = 1e18;
    waitingInc.clear();
    waitingDec.clear();
    dpInc.insert({0, 0});
    waitingDec.push_back({N+1, 0});

    // To avoid edge cases
    dpInc.insert({-1, -INF});
    dpInc.insert({N+2, INF});
    dpDec.insert({N+2, -INF});
    dpDec.insert({-1, INF});

    for (int x = 0; x < N; x++) {
        cout << "on x = " << x << endl;
        // Update dpDec
        for (int i = colToFish[x].size()-1; i >= 0; i--) {
            int cy = colToFish[x][i].y, cw = colToFish[x][i].w;
            // Find closest element with y > cy, including current x
            auto ptr = dpDec.lower_bound({cy+1, -1});
            ll newAns = ptr->ans + cw;
            insertDec(cy, newAns);
            // Add to dpInc after a short delay
            if (cy == 0) waitingInc.push_back({cy, newAns});
        }
        // Now add to dpDec
        for (State& s : waitingDec) insertDec(s.y, s.ans);
        waitingDec.clear();

        // Update dpInc
        for (int i = 0; i < colToFish[x].size(); i++) {
            int cy = colToFish[x][i].y, cw = colToFish[x][i].w;
            // Find closest element with y < cy, including current x
            auto ptr = prev(dpInc.lower_bound({cy, -1}));
            ll newAns = ptr->ans + cw;
            insertInc(cy, newAns);
            // Add to dpDec after a long delay
            if (cy == N+1) waitingDec.push_back({cy, newAns});
        }
        // Now add to dpInc
        for (State& s : waitingInc) {
            insertInc(s.y, s.ans);
            waitingDec.push_back({N+1, s.ans});
        }
        waitingInc.clear();
    }

    // Erase edge cases
    dpInc.erase({-1, -INF});
    dpInc.erase({N+2, INF});
    dpDec.erase({N+2, -INF});
    dpDec.erase({-1, INF});

    // Get the answer (must be decreasing at the end, since the last pier is technically 0)
    ll ans = 0;
    // cout << "dpDec:\n";
    for (const State& s : dpDec) {
        // cout << s.y << " " << s.ans << endl;
        ans = max(s.ans, ans);
    }
    dpInc.clear();
    dpDec.clear();
    return ans;
}






















void sampleCase() {
    int N = 5, M = 4;
    vector<int> X({0, 1, 4, 3}), Y({2, 1, 4, 3}), W({5, 2, 1, 3});
    ll ans = 8;
    ll result = max_weights(N, M, X, Y, W);
    if (ans == result) {
        cout << "Sample case passed!" << endl;
    } else {
        cout << "Wrong answer: Expected " << ans << ", got " << result << endl;
        exit(-1);
    }
}

void validationCase() {
    int N = 7, M = 9;
    vector<int> X({0, 0, 1, 3, 3, 4, 5, 5, 6});
    vector<int> Y({1, 4, 2, 3, 5, 3, 1, 3, 4});
    vector<int> W({3, 13, 8, 4, 10, 5, 20, 4, 15});
    ll ans = 55;
    ll result = max_weights(N, M, X, Y, W);
    if (ans == result) {
        cout << "Validation case passed!" << endl;
    } else {
        cout << "Wrong answer: Expected " << ans << ", got " << result << endl;
        exit(-1);
    }
}

void debugCase() {
    int N = 13, M = 13;
    vector<int> X({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
    vector<int> Y({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
    vector<int> W({0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1});
    ll result = max_weights(N, M, X, Y, W);
    cout << result << endl;
}

int main() {
    sampleCase();
    validationCase();
    debugCase();
    return 0;
}
