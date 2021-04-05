#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5;

int N, K;
int A[MAXN];
ll lowSum, highSum;
multiset<int> msLow, msHigh;

void output() {
    for (int x : msLow) cout << x << ' ';
    cout << endl;
    for (int x : msHigh) cout << x << ' ';
    cout << endl;
}

void balance() {
    // cout << "balance" << endl;
    while ((int) msLow.size() - (int) msHigh.size() >= 2) {
        // Low to high
        // output();
        auto ptr = prev(msLow.end());
        highSum += *ptr;
        lowSum -= *ptr;
        msHigh.insert(*ptr);
        msLow.erase(ptr);
        // output();
    }
    while (msHigh.size() > msLow.size()) {
        // High to low
        // output();
        auto ptr = msHigh.begin();
        lowSum += *ptr;
        highSum -= *ptr;
        msLow.insert(*ptr);
        msHigh.erase(ptr);
        // output();
    }
}

void insert(int x) {
    // cout << "insert " << x << endl;
    if (msHigh.empty() || x < *msHigh.begin()) {
        lowSum += x;
        msLow.insert(x);
    } else {
        highSum += x;
        msHigh.insert(x);
    }
}

void solve() {
    cin >> N >> K;
    rep(i, 0, N) cin >> A[i];
    rep(i, 0, K) {
        insert(A[i]);
        balance();
        // output();
    }
    rep(i, K, N+1) {
        ll median = *prev(msLow.end());
        // cout << "med " << median << " " << lowSum << " " << highSum << endl;
        ll cost = (median * msLow.size() - lowSum) + (highSum - median * msHigh.size());
        cout << cost << (i == N ? '\n' : ' ');
        if (i == N) break;

        auto ptr = msLow.find(A[i-K]);
        if (ptr == msLow.end()) {
            ptr = msHigh.find(A[i-K]);
            highSum -= *ptr;
            msHigh.erase(ptr);
        } else {
            lowSum -= *ptr;
            msLow.erase(ptr);
        }

        insert(A[i]);
        balance();
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}