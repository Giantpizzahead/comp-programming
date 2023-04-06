#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

const int K = 18;

vi S, T;
vector<vector<bool>> validPair(K, vector<bool>(K));
int Q;

bool checkPair(int a, int b) {
    vi newS, newT;
    for (int x : S) if (x == a || x == b) newS.push_back(x);
    for (int x : T) if (x == a || x == b) newT.push_back(x);
    return newS == newT;
}

void solve() {
    string s, t;
    cin >> s >> t;
    for (char c : s) S.push_back(c - 'a');
    for (char c : t) T.push_back(c - 'a');
    // Find valid pairs
    rep(i, 0, K) rep(j, i, K) validPair[i][j] = checkPair(i, j);
    // Process queries
    cin >> Q;
    rep(i, 0, Q) {
        string q; cin >> q;
        bool valid = true;
        rep(a, 0, sz(q)) {
            rep(b, a, sz(q)) {
                if (!validPair[q[a]-'a'][q[b]-'a']) {
                    valid = false;
                    break;
                }
            }
        }
        cout << (valid ? 'Y' : 'N');
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    solve();
    return 0;
}