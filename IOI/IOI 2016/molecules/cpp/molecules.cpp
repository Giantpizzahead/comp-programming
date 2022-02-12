/*
Solution: Sort the weights, and take all of the largest ones until the sum >= l. To check if it's possible, take the
same # of elements, but all the smallest ones now. If the smallest sum <= u, then it's possible.
Now, start with all the largest weights, and move one at a time down to the smallest ones. You'll step by no more than
w_max - w_min, which means you'll step no more than u-l, so you'll hit the target range eventually.
Runtime: O(N * log(N))
*/

#include "molecules.h"
#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

int N, K;
ll L, U;

struct Pair {
    int w, id;
};
vector<Pair> W;
vector<bool> used;

ll currSum;

void use(int i) {
    assert(!used[i]);
    used[i] = true;
    currSum += W[i].w;
}

void drop(int i) {
    assert(used[i]);
    used[i] = false;
    currSum -= W[i].w;
}

vector<int> find_subset(int l, int u, vector<int> w) {
    vector<int> ans;
    N = sz(w), L = l, U = u;
    used.resize(N);
    rep(i, 0, N) W.push_back({w[i], i});
    sort(all(W), [](const Pair& a, const Pair& b) { return a.w < b.w; });

    // Use K largest
    K = 0, currSum = 0;
    while (true) {
        use(N-1-K);
        K++;
        if (K == N || currSum >= L) break;
    }
    if (currSum < L) return ans;
    // Use K smallest
    ll minSum = 0;
    rep(i, 0, K) minSum += W[i].w;
    if (minSum > U) return ans;

    // Answer exists in between these
    rep(i, 0, K+1) {
        if (currSum >= L && currSum <= U) {
            // This works
            rep(j, 0, N) if (used[j]) ans.push_back(W[j].id);
            return ans;
        }
        if (i == K) break;
        drop(N-K+i);
        use(i);
    }
    return ans;
}
