#include <iostream>
#include <vector>
//#include <bitset>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;

const int MAXN = 1024;
const ll MOD = 1e9+7;

int N, M, S;
vector<int> trans[MAXN];

void genTrans(int i, int s, int p) {
    // cout << i << " " << bitset<5>(s) << " " << bitset<5>(states[p]) << endl;
    while (true) {
        if (i == N) {
            trans[p].push_back(s);
            return;
        }
        if (p & 1 << i) i++;
        else {
            if (i != N-1 && !(p & 1 << (i+1))) genTrans(i+2, s, p);
            s |= 1 << i;
            i++;
        }
    }
}

ll dp[2][MAXN];

void solve() {
    cin >> N >> M;
    S = 1 << N;
    rep(i, 0, S) genTrans(0, 0, i);
    // cout << S << endl;
    // rep(i, 0, S) {
    //     cout << bitset<10>(states[i]) << ": ";
    //     for (int j : trans[i]) cout << bitset<10>(states[j]) << " ";
    //     cout << endl;
    // }

    dp[0][0] = 1;
    ll *currDP = dp[0];
    ll *oldDP = dp[1];
    rep(i, 0, M) {
        swap(currDP, oldDP);
        rep(j, 0, S) currDP[j] = 0;
        rep(j, 0, S) {
            if (oldDP[j] == 0) continue;
            oldDP[j] %= MOD;
            for (int k : trans[j]) currDP[k] += oldDP[j];
        }
    }
    cout << currDP[0] % MOD << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}