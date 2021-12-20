// 837799

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

int N;

unordered_map<ll, int> steps;

ll getNext(ll x) {
    if (x % 2 == 0) return x/2;
    else return x*3+1;
}

int getSteps(ll x) {
    vector<ll> nums;
    nums.push_back(x);
    while (steps.find(x) == steps.end()) {
        x = getNext(x);
        nums.push_back(x);
    }
    // Fill in memo table
    for (int i = 1; i < sz(nums); i++) {
        steps[nums[sz(nums)-1-i]] = steps[x] + i;
    }
    return steps[nums[0]];
}

void solve() {
    cin >> N;
    int ans = 0, maxSteps = 0;
    steps[1] = 0;
    rep(i, 1, N+1) {
        int currSteps = getSteps(i);
        // cout << i << ": " << currSteps << endl;
        if (currSteps > maxSteps) {
            maxSteps = currSteps;
            ans = i;
        }
    }
    cout << ans << ": " << maxSteps << " steps" << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}