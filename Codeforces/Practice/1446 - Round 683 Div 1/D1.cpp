#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5, MAXV = 101;

int N, mode;
vector<int> locs[MAXV];
int A[MAXN], cnt[MAXV];

unordered_map<int, int> pre;
int tryFrequent(int v) {
    pre.clear();
    pre.emplace(0, -1);
    int curr = 0, answer = 0;
    rep(i, 0, N) {
        if (A[i] == mode) curr++;
        else if (A[i] == v) curr--;
        auto ptr = pre.find(curr);
        if (ptr == pre.end()) pre[curr] = i;
        else answer = max(i - ptr->second, answer);
    }
    return answer;
}

void solve() {
    cin >> N;
    rep(i, 0, N) {
        cin >> A[i];
        cnt[A[i]]++;
        locs[A[i]].push_back(i);
    }

    // Duplicate mode?
    int maxCnt = 0;
    mode = -1;
    bool dup = false;
    rep(i, 1, MAXV) {
        if (cnt[i] > maxCnt) {
            maxCnt = cnt[i];
            mode = i;
            dup = false;
        } else if (cnt[i] == maxCnt) dup = true;
    }
    if (dup) {
        cout << N << '\n';
        return;
    }

    // Try making every element the most frequent (along with mode)
    int answer = 0;
    rep(i, 1, MAXV) {
        if (i != mode && !locs[i].empty()) {
            answer = max(tryFrequent(i), answer);
        }
    }
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}