#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

const ll INF = 1e16;
const int MAXN = 100005;

int N, D, M;
ll goodPre[MAXN], badPre[MAXN];
vector<int> good, bad;

void solve() {
    cin >> N >> D >> M;
    int x;
    for (int i = 0; i < N; i++) {
        cin >> x;
        if (x > M) {
            bad.push_back(x);
        } else {
            good.push_back(x);
        }
    }
    sort(good.begin(), good.end());
    sort(bad.begin(), bad.end());

    ll currPre = 0;
    for (int i = 0; i < good.size(); i++) {
        currPre += good[i];
        goodPre[i] = currPre;
    }
    currPre = 0;
    for (int i = 0; i < bad.size(); i++) {
        currPre += bad[i];
        badPre[i] = currPre;
    }

    if (bad.empty()) {
        cout << goodPre[good.size()-1] << endl;
        return;
    }

    int minBadToUse = (bad.size() + D) / (D + 1);
    int maxBadToUse = min((N + D) / (D + 1), (int) bad.size());

    ll answer = 0;
    for (int badToUse = minBadToUse; badToUse <= maxBadToUse; badToUse++) {
        // Remove the bad ones that aren't being used
        int numBadRemoved = bad.size() - badToUse;
        // The rest must be good (one bad can go on the rightmost edge)
        int numGoodRemoved = max((badToUse - 1) * D - numBadRemoved, 0);
        // Sum of badToUse biggest bad ones
        ll result = badPre[bad.size()-1] - (badToUse == bad.size() ? 0 : badPre[bad.size()-1-badToUse]);
        // Sum of all (good minus numGoodRemoved) biggest ones
        result += goodPre[good.size()-1];
        result -= (numGoodRemoved == 0 ? 0 : goodPre[numGoodRemoved-1]);
        // cout << badToUse << ' ' << numGoodRemoved << ' ' << result << endl;
        answer = max(result, answer);
    }
    cout << answer << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}