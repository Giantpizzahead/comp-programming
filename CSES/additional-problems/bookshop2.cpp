#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 100, MAXX = 1e5+1;

int N, X;
int H[MAXN], S[MAXN], K[MAXN];
int dp[MAXX];
deque<pair<int, int>> mq;

// i must be monotonically increasing
void mqInsert(int i, int v) {
    while (!mq.empty() && mq.back().second <= v) mq.pop_back();
    mq.emplace_back(i, v);
}

// i must be monotonically increasing
void mqMove(int i) {
    if (!mq.empty() && mq.front().first <= i) mq.pop_front();
}

void solve() {
    cin >> N >> X;
    for (int i = 0; i < N; i++) cin >> H[i];
    for (int i = 0; i < N; i++) cin >> S[i];
    for (int i = 0; i < N; i++) cin >> K[i];

    for (int i = 0; i < N; i++) {        
        for (int j = 0; j < H[i]; j++) {
            mq.clear();
            mqInsert(0, dp[j]);
            int loc = j + H[i];
            for (int k = 1; loc <= X; k++, loc += H[i]) {
                mqInsert(k, dp[loc] - S[i] * k);
                auto trans = mq.front();
                dp[loc] = max(trans.second + S[i] * k, dp[loc]);
                mqMove(k-K[i]);
            }
        }
    }
    // cout << "dp: ";
    // for (int i = 0; i <= X; i++) cout << dp[i] << ' ';
    // cout << endl;

    cout << dp[X] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}