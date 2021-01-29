#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define F0R(i, a) for (int i = 0; i < a; i++)
#define FOR(i, a, b) for (int i = a; i < b; i++)

const int MAXN = 2e5;

int N, X;
multiset<int> P;

void solve() {
    cin >> N >> X;
    F0R(i, N) {
        int x;
        cin >> x;
        P.insert(x);
    }

    int answer = 0;
    while (!P.empty()) {
        answer++;
        auto ptr = prev(P.end());
        int p = *ptr;
        P.erase(ptr);
        ptr = P.upper_bound(X-p);
        if (ptr == P.begin()) continue;
        P.erase(prev(ptr));
    }

    cout << answer << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}