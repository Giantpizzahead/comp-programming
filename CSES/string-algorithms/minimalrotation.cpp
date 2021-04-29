#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

void solve() {
    int N;
    string S;
    vector<int> lps;
    cin >> S;
    N = sz(S);
    S += S;
    lps.resize(2*N);
    int bestR = 0, currLPS = 0;
    rep(i, 1, 2*N) {
        // Update LPS
        while (currLPS != 0 && S[bestR+currLPS] != S[i]) {
            if (S[i] < S[bestR+currLPS]) {
                // Update best rotation
                // LPS remains the same (currLPS prefix already matches)
                bestR = i-currLPS;
            }
            currLPS = lps[currLPS-1];
        }
        if (S[bestR+currLPS] == S[i]) currLPS++;
        else if (S[i] < S[bestR+currLPS]) {
            bestR = i-currLPS;
        }
        lps[i-bestR] = currLPS;
    }
    // rep(i, 0, 2*N) cout << lps[i] << ' ';
    // cout << endl;
    cout << S.substr(bestR, N-bestR) << S.substr(0, bestR) << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}