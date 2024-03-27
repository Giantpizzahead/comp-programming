#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

int N, M;
ll T;
const ll INF = 1e18;

struct Train {
    bool r;
    ll t;
};
vector<Train> trains;
vector<ll> times;
// dpR/dpB[i] = Min delay, ending at times[i] sec, with last portion allowing red/blue trains through
vector<ll> dpR, dpB;

void solve() {
    cin >> N >> T;
    rep(i, 0, N) {
        char c; cin >> c;
        ll t; cin >> t;
        trains.push_back({c == 'A', t});
    }
    sort(all(trains), [](const Train& a, const Train& b) { return a.t < b.t; });

    // Switch times must be either at the end of a train (t+T), or t+2T, t+3T, ...
    set<ll> timesSet;
    timesSet.insert(0);
    rep(i, 0, N) {
        rep(j, 1, N+1-i) {
            timesSet.insert({trains[i].t + j*T});
        }
    }
    for (ll t : timesSet) times.push_back(t);
    M = sz(times);
    
    // Do DP
    dpR.resize(M, INF), dpB.resize(M, INF);
    dpR[0] = 0, dpB[0] = 0;
    rep(i, 1, M) {
        // Try all previous times
        ll delayR = 0, delayB = 0;
        int k = N-1;
        while (k >= 0 && trains[k].t >= times[i]) k--;
        for (int j = i-1; j >= 0; j--) {
            if (times[i] - times[j] < T) continue;  // Not enough time for trains to pass
            if (times[i] - times[j] > 3*T) break;  // Not needed, probably not optimal?

            // Update stalled trains
            while (k >= 0 && trains[k].t > times[j] - T) {
                if (trains[k].r) delayB += times[i] - trains[k].t;
                else delayR += times[i] - trains[k].t;
                k--;
                // cout << "stalled " << k << endl;
            }

            // Switch from red to blue
            dpB[i] = min(dpR[j] + delayR, dpB[i]);

            // Switch from blue to red
            dpR[i] = min(dpB[j] + delayB, dpR[i]);

            // cout << "from " << times[j] << " to " << times[i] << endl;
            // cout << "time " << times[i] << ": " << dpR[i] << " " << dpB[i] << endl;
        }
    }

    // Get answer
    ll ans = INF;
    bool worksR = true, worksB = true;
    int latestR = N-1, latestB = N-1;
    while (latestR >= 0 && !trains[latestR].r) latestR--;
    while (latestB >= 0 && trains[latestB].r) latestB--;
    for (int i = M-1; i >= 0; i--) {
        if (latestR != -1 && trains[latestR].t > times[i] - T) worksR = false;
        if (latestB != -1 && trains[latestB].t > times[i] - T) worksB = false;
        if (worksR) ans = min(dpR[M-1], ans);
        if (worksB) ans = min(dpB[M-1], ans);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // freopen("test.in", "r", stdin);
    solve();
    return 0;
}
