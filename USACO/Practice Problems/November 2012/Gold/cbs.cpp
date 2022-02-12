/**
 * Solution:
 * Sweep the right endpoint of the range, and count the # of ranges with the two properties:
 * 1) # of opening parens = # of closing parens. This can be calculated by maintaing K values (# open - # closed) at
 * each index, and looking the # of previous indices with all K matching values (same # of open and closed in between).
 * 2) (# open - # closed) is never negative in the range. This can be maintained using a stack, removing previous
 * indices when any of the K strings violate this constraint.
 * 
 * Runtime: O(NK * log(N))
 */

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXK = 10;
const int MAXN = 50005;

int K, N;
string S[MAXK];
vector<int> stacks[MAXK];
vector<pair<int, vector<int>>> oldParens;
vector<int> parens;
map<vector<int>, int> cnt;

void solve() {
    cin >> K >> N;
    rep(j, 0, K) {
        cin >> S[j];
    }
    parens.resize(K);

    oldParens.emplace_back(-1, parens);
    cnt[parens]++;
    // Sweep right endpoint of range
    ll answer = 0;
    rep(i, 0, N) {
        rep(j, 0, K) {
            if (S[j][i] == '(') {
                stacks[j].push_back(i);
                parens[j]++;
            } else {
                // Remove ranges that go below 0
                int top;
                if (stacks[j].empty()) top = -1;
                else {
                    top = stacks[j].back();
                    stacks[j].pop_back();
                }
                while (!oldParens.empty() && oldParens.back().first >= top) {
                    cnt[oldParens.back().second]--;
                    oldParens.pop_back();
                }
                parens[j]--;
            }
        }
        // Count # of ranges with equal #s of ( and )
        answer += cnt[parens];
        oldParens.emplace_back(i, parens);
        cnt[parens]++;
        // cout << i << ": ";
        // rep(j, 0, K) cout << parens[j] << " \n"[j==K-1];
    }
    cout << answer << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    freopen("cbs.in", "r", stdin);
    freopen("cbs.out", "w", stdout);
    solve();
    return 0;
}