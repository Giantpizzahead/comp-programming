#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5;

unordered_map<int, int> lastLoc;

int N, K;
int A[MAXN];

void solve() {
    cin >> N >> K;
    rep(i, 0, N) {
        cin >> A[i];
    }
    lastLoc.reserve(N);

    ll answer = 0;
    int j = 0;
    rep(i, 0, N) {
        if (lastLoc.find(A[i]) == lastLoc.end()) {
            K--;
            while (K < 0) {
                // Must remove elements until all distinct
                auto ptr = lastLoc.find(A[j]);
                if (ptr->second == j) {
                    lastLoc.erase(ptr);
                    K++;
                }
                j++;
            }
        }
        lastLoc[A[i]] = i;
        answer += i-j+1;
    }

    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}