#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5;

int N;
int A[MAXN];
stack<int> smaller;

void solve() {
    cin >> N;
    smaller.push(-1);
    rep(i, 0, N) {
        cin >> A[i];
        while (smaller.size() != 1 && A[smaller.top()] >= A[i]) smaller.pop();
        if (i != 0) cout << ' ';
        cout << smaller.top() + 1;
        smaller.push(i);
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}