#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXC = 20;

int N, answer;
string A, B;
bool conv[MAXC][MAXC];

void solve() {
    cin >> N >> A >> B;
    rep(i, 0, MAXC) {
        rep(j, 0, MAXC) conv[i][j] = false;
    }
    rep(i, 0, N) conv[A[i]-'a'][B[i]-'a'] = true;
    // Convert from bottom up
    answer = 0;
    rep(i, 0, MAXC) {
        rep(j, 0, MAXC) {
            if (!conv[j][i] || i == j) continue;
            if (j > i) {
                cout << -1 << '\n';
                return;
            }
            answer++;
            rep(k, 0, MAXC) {
                conv[i][k] |= conv[j][k];
                conv[j][k] = false;
            }
        }
    }
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}