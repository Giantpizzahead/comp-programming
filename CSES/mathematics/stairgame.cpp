/**
 * The # of balls on the 1st stair does not matter. In fact, all the balls on the odd stairs do not matter! One way to
 * prove this is to assume that the fact is true, and see what happens. If the current even stair config is a winning
 * configuration, then if the other player moves anything from an odd stair, the winning player can just move the same
 * # of balls out of the even stairs, back to the odd ones. So, the winning player can "cancel out" any moves involving
 * the odd stairs. If the current even config is losing, then moving the odd stairs will not do any good, for the same
 * reasons as above. Therefore, only the balls on the even stairs matter.
 * 
 * The next step is to see what happens when an even stair move is made: It transfers balls into the odd stairs. Even
 * though those balls were just moved, they are now in the odd stairs, so they no longer affect whether the state is
 * winning or losing. In other words, one way to view a move is to say that instead of moving the balls, you simply
 * delete them from the even stairs. This is just the classic Nim game, but with only the balls on the even stairs!
 * 
 * So, the final solution is to solve Nim for the even stair ball counts only:
 * This is the XOR sum of all p_i, where i is even. If this is nonzero, player 1 wins; else, player 2 wins.
 * 
 * Runtime: O(N)
 */

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5;

int N;
int P[MAXN];

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> P[i];
    int xorSum = 0;
    for (int i = 1; i < N; i += 2) xorSum ^= P[i];
    cout << (xorSum == 0 ? "second" : "first") << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    rep(i, 0, T) solve();
    return 0;
}