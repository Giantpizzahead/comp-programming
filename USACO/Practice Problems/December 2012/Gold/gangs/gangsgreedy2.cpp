/*
Wrong greedy solution 2

Solution:
Special case if M is 2, just put all the 1s and then 2s

Fix a cow to go, then figure out the optimal # of gang 1 cows after matching the rest in O(1)
    Think of the process as making pairs of cows
    # cows left to match = max in 1...M - sum(all except max in 1...M)
    (if above is negative, it becomes either 0 or 1 depending on parity)
    Use this to figure out the # of remaining gang 1 cows

Optimal order will be increasing from 1 to M, except for the largest gang that's not 1
Order will end with all 1s, all the other gang 1 cows will be paired
    Using the above, will only try at most 2N cows

Runtime: O(N+M)
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (false) cerr
using ll = long long;

const int MAXM = 105;

int N, M, maxI, curr, cnt, prevCurr, prevCnt;
int A[MAXM];
vector<int> order;

void useNum(int x) {
    assert(A[x] > 0);
    order.push_back(x);
    A[x]--;
    N--;
    prevCurr = curr;
    prevCnt = cnt;
    if (curr == -1 || curr == x) {
        curr = x;
        cnt++;
    } else {
        cnt--;
        if (cnt == 0) curr = -1;
    }
    debug << "use " << x << endl;
}

void backtrack() {
    int x = order.back();
    order.pop_back();
    A[x]++;
    N++;
    curr = prevCurr;
    cnt = prevCnt;
}

int doGreedy() {
    if (curr > 0) A[curr] += cnt;

    // Match all cows, not including unused from gang 1
    int currN = N - A[0] + cnt;
    int toMatch = A[maxI] - (currN - A[maxI]);
    if (toMatch < 0) {
        if (currN % 2 == 0) toMatch = 0;
        else toMatch = 1;
    }

    // Match 1 cows if needed
    int ans;
    if (toMatch > A[0]) ans = -1;
    else ans = A[0] - toMatch;
    debug << "greedy " << currN << " " << maxI << " " << A[maxI] << " " << toMatch << " " << A[0] << " " << ans << endl;
    
    if (curr > 0) A[curr] -= cnt;
    return ans;
}

void solve() {
    cin >> N >> M;
    rep(i, 0, M) cin >> A[i];

    maxI = 1;
    rep(i, 1, M) if (A[i] > A[maxI]) maxI = i; 

    if (M == 2) {
        // Special case
        if (A[0] <= A[1]) cout << "NO\n";
        else {
            cout << "YES\n";
            cout << A[0]-A[1] << '\n';
            rep(i, 0, A[0]) cout << "1\n";
            rep(i, 0, A[1]) cout << "2\n";
        }
        return;
    }

    int ans = doGreedy();
    if (ans <= 0) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    cout << ans << '\n';

    curr = -1, cnt = 0;
    int ci = 0;
    int res;
    int origN = N;
    while (sz(order) < origN - ans) {
        // Find next cow to place
        bool found = false;
        rep(i, 0, M) {
            if (A[i] == 0) continue;
            useNum(i);
            res = doGreedy();
            if (res == ans) {
                found = true;
                debug << endl;
                break;
            } else backtrack();
        }
        assert(found);
    }
    rep(i, 0, ans) useNum(0);

    for (int x : order) cout << x+1 << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("gangs.in", "r", stdin);
    freopen("gangs.out", "w", stdout);
    solve();
    return 0;
}