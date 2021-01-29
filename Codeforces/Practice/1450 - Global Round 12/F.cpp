#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 100005;

int N, answer;
int A[MAXN], cnt[MAXN], numSame[MAXN];
vector<pair<int, int>> ranges;
priority_queue<pair<int, int>> pq;

void solve() {
    ranges.clear();
    while (!pq.empty()) pq.pop();
    cin >> N;
    for (int i = 0; i < N; i++) {
        cnt[i] = 0;
        numSame[i] = 0;
    }
    for (int i = 0; i < N; i++) {
        cin >> A[i];
        A[i]--;
        cnt[A[i]]++;
    }
    // Possible?
    int maxCount = -1;
    for (int i = 0; i < N; i++) {
        maxCount = max(cnt[i], maxCount);
        if (maxCount > (N+1) / 2) {
            cout << -1 << '\n';
            return;
        }
    }
    answer = 0;
    int li = 0;
    for (int i = 0; i < N; i++) {
        if (i == N-1 || A[i] == A[i+1]) {
            // Split
            int a = A[li];
            int b = A[i];
            if (a > b) swap(a, b);
            if (a == b) numSame[a]++;
            else ranges.emplace_back(a, b);
            li = i+1;
        }
    }
    for (int i = 0; i < N; i++) if (numSame[i] != 0) pq.emplace(numSame[i], i);
    // for (auto p : ranges) cout << p.first << " " << p.second << endl;
    // cout << endl;
    // Greedily pair same
    while (pq.size() > 1) {
        pair<int, int> a = pq.top();
        pq.pop();
        pair<int, int> b = pq.top();
        pq.pop();
        // Change a-a, b-b into a-b with 1 jump
        answer++;
        int x = a.second, y = b.second;
        if (x > y) swap(x, y);
        ranges.emplace_back(x, y);
        if (a.first != 1) pq.emplace(a.first-1, a.second);
        if (b.first != 1) pq.emplace(b.first-1, b.second);
    }
    if (pq.size() == 0) {
        // Only ranges left
        // cout << "ranges left" << endl;
        answer += ranges.size() - 1;
    } else {
        // Start at one range, merge remaining
        auto p = pq.top();
        // cout << "pq " << p.first << " " << p.second << endl;
        for (int i = 0; i < ranges.size(); i++) {
            auto x = ranges[i];
            if (p.first == 1) {
                // No more need to merge
                answer++;
            } else if (x.first == p.second || x.second == p.second) {
                // Merge into new one range (doesn't do anything overall)
                answer++;
            } else {
                // Merge into different range
                answer++;
                p.first--;
                ranges.emplace_back(p.second, x.first);
            }
        }
        answer += (p.first - 1) * 2;
        pq.pop();
    }
    // for (auto p : ranges) cout << p.first << " " << p.second << endl;
    // cout << endl;
    cout << answer << '\n';
    
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        solve();
    }
    return 0;
}