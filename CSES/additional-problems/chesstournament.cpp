#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1e5+5;

int N;
int A[MAXN];
priority_queue<pair<int, int>> pq;
vector<pair<int, int>> games, toPush;

void solve() {
    cin >> N;
    rep(i, 0, N) {
        cin >> A[i];
        pq.emplace(A[i], i);
    }
    while (!pq.empty()) {
        int i = pq.top().second;
        pq.pop();
        while (A[i] != 0) {
            if (pq.empty()) {
                cout << "IMPOSSIBLE\n";
                return;
            }
            int j = pq.top().second;
            pq.pop();
            games.emplace_back(i, j);
            A[i]--; A[j]--;
            toPush.emplace_back(A[j], j);
        }
        while (!toPush.empty()) {
            pq.emplace(toPush.back());
            toPush.pop_back();
        }
    }
    cout << games.size() << '\n';
    for (auto& p : games) {
        cout << p.first+1 << ' ' << p.second+1 << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}