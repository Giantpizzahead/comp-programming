#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 2e5;

int X, N;
ll answer;
multiset<int> D;

void solve() {
    cin >> X >> N;
    int d;
    for (int i = 0; i < N; i++) {
        cin >> d;
        D.insert(d);
    }
    while (D.size() > 1) {
        auto a = D.begin();
        auto b = next(a);
        int nd = *a + *b;
        answer += nd;
        D.erase(a);
        D.erase(b);
        D.insert(nd);
    }
    cout << answer << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}