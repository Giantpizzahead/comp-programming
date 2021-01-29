#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1e6+5;

int N, cntChar[27];
int nextC[MAXN];
int charToI[256];
vi locs[27];
string str;

void solve() {
    cin >> str;
    N = sz(str);
    rep(i, 1, 27) {
        charToI[i-1+'a'] = i;
    }
    charToI['#'] = 0;
    rep(i, 0, N) {
        int x = charToI[str[i]];
        locs[x].push_back(i);
    }
    int cj = 0;
    rep(i, 0, N) {
        while (cntChar[cj] == locs[cj].size()) cj++;
        nextC[i] = locs[cj][cntChar[cj]];
        cntChar[cj]++;
        // cout << nextC[i] << ' ';
    }
    // cout << endl;

    cj = locs[0][0];
    rep(i, 0, N-1) {
        cj = nextC[cj];
        cout << str[cj];
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}