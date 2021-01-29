#include <bits/stdc++.h>
#define sz(x) (int) (x.size())
#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;
using ll = long long;
using vi = vector<int>;

int N;
vector<pair<int, int>> P;

void solve() {
    cin >> N;
    P.reserve(N*2);
    rep(i, 0, N) {
        int a, b;
        cin >> a >> b;
        P.emplace_back(a, 1);
        P.emplace_back(b, -1);
    }
    sort(P.begin(), P.end());
    int answer = 0, curr = 0;
    for (auto p : P) {
        curr += p.second;
        answer = max(curr, answer);
    }
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}