#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

const int MAXN = 2e5+5;

int N, M;
int numProf[MAXN];

bool check(int T) {
    ll openSlots = 0;
    ll unprofCnt = 0;
    rep(i, 0, N) {
        ll profCnt = min(T, numProf[i]);
        openSlots += (T - profCnt) / 2;
        unprofCnt += numProf[i] - profCnt;
    }
    return openSlots >= unprofCnt;
}

void solve() {
    cin >> N >> M;
    rep(i, 0, M) {
        int a; cin >> a; a--;
        numProf[a]++;
    }

    int low = 1, high = 2*M;
    while (low < high) {
        int mid = (low+high)/2;
        if (check(mid)) high = mid;
        else low = mid+1;
    }
    cout << low << '\n';

    rep(i, 0, N) numProf[i] = 0;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}