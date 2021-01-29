#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 2e5;

int N, K;
int A[MAXN];
multiset<int> small, big;

void insert(int x) {
    auto ptr = big.begin();
    if (ptr == big.end() || x <= *ptr) small.insert(x);
    else big.insert(x);
}

void balance() {
    // cout << "small: ";
    // for (int x : small) cout << x << ' ';
    // cout << endl;
    // cout << "big: ";
    // for (int x : big) cout << x << ' ';
    // cout << endl;
    if (small.size() > big.size() + 1) {
        auto ptr = prev(small.end());
        big.insert(*ptr);
        small.erase(ptr);
    }
    if (big.size() > small.size()) {
        auto ptr = big.begin();
        small.insert(*ptr);
        big.erase(ptr);
    }
}

void solve() {
    cin >> N >> K;
    for (int i = 0; i < N; i++) cin >> A[i];
    for (int i = 0; i < K; i++) {
        insert(A[i]);
        balance();
    }
    for (int i = K; i <= N; i++) {
        if (i != K) cout << ' ';
        cout << *prev(small.end());
        if (i == N) break;

        auto ptr = big.find(A[i-K]);
        if (ptr != big.end()) big.erase(ptr);
        else small.erase(small.find(A[i-K]));
        balance();

        insert(A[i]);
        balance();
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}