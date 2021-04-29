#include <iostream>
#include <vector>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXP = 19;
vector<ll> pow10(MAXP);

bool check(string S, vector<ll>& D, bool first=false) {
    // cout << "check " << S << endl;
    // for (ll x : D) cout << x << ' ';
    // cout << endl;
    // Base case
    if (sz(S) == 1) {
        rep(d, (first ? 0 : 1), S[0]-'0'+1) {
            D[d]--;
            if (D[d] < 0) return false;
        }
        return true;
    }
    // Top digit is not maximum
    int maxtopd = S[0]-'0';
    rep(topd, 0, maxtopd) {
        if (!first || topd != 0) {
            D[topd] -= pow10[sz(S)-1];
            if (D[topd] < 0) return false;
        }
        rep(d, 0, 10) {
            D[d] -= pow10[sz(S)-2] * (sz(S)-1);
            if (D[d] < 0) return false;
        }
    }
    // Top digit is maximum
    string newS = S.substr(1);
    D[maxtopd] -= stoll(newS) + 1;
    if (D[maxtopd] < 0) return false;
    return check(newS, D);
}

bool check(ll N, ll actualN) {
    vector<ll> D(10);
    fill(all(D), actualN);
    return check(to_string(N), D, true);
}

void solve() {
    pow10[0] = 1;
    rep(i, 1, MAXP) pow10[i] = pow10[i-1] * 10;
    ll N; cin >> N;
    ll low = 1, high = 8*1e17;
    while (low < high) {
        ll mid = (low+high+1)/2;
        if (check(mid, N)) {
            low = mid;
        } else {
            high = mid-1;
        }
    }
    cout << low << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}