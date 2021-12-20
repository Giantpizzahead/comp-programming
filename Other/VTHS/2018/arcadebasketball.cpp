#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 100005;

int N, P, M;
unordered_map<string, int> scores;

void solve() {
    cin >> N >> P >> M;
    string name;
    int p;
    for (int i = 0; i < N; i++) {
        cin >> name;
        scores[name] = 0;
    }
    bool wins = false;
    for (int i = 0; i < M; i++) {
        cin >> name >> p;
        if (scores[name] >= P) continue;
        scores[name] += p;
        if (scores[name] >= P) {
            wins = true;
            cout << name << " wins!\n";
        }
    }
    if (!wins) cout << "No winner!\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    // cin >> T;
    for (int i = 1; i <= T; i++) {
        solve();
    }
    return 0;
}