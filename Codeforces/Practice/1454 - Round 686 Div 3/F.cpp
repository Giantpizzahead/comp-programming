#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5;

int N;
pair<int, int> sortedA[MAXN];
int A[MAXN], maxL[MAXN], maxR[MAXN];
set<int> avoid, minLocs;
vector<int> maxLocs;

void solve() {
    cin >> N;
    rep(i, 0, N) {
        cin >> A[i];
        sortedA[i].first = A[i];
        sortedA[i].second = i;
    }
    sort(sortedA, sortedA+N);
    maxL[0] = A[0];
    rep(i, 1, N) maxL[i] = max(A[i], maxL[i-1]);
    maxR[0] = A[N-1];
    for (int i = N-2; i >= 0; i--) maxR[N-1-i] = max(A[i], maxR[N-2-i]);

    // Deal with special case
    maxLocs.clear();
    rep(i, 0, N) {
        if (A[i] == maxL[N-1]) maxLocs.push_back(i);
    }
    if (maxLocs.size() >= 3) {
        cout << "YES\n";
        cout << maxLocs[1] << " " << 1 << " " << N-1-maxLocs[1] << "\n";
        return;
    }

    avoid.clear();
    minLocs.clear();
    rep(i, 0, N) {
        if (sortedA[i].first == maxL[N-1]) break;  // Max element
        while (!minLocs.empty()) {
            avoid.insert(*minLocs.begin());
            minLocs.erase(minLocs.begin());
        }
        minLocs.insert(sortedA[i].second);
        while (i != N-1 && sortedA[i+1].first == sortedA[i].first) {
            i++;
            minLocs.insert(sortedA[i].second);
        }
        // Maxes must cover avoid spots, leave at least one minLoc open
        int target = sortedA[i].first;
        int li1 = distance(maxL, lower_bound(maxL, maxL+N, target));
        int ri1 = distance(maxR, lower_bound(maxR, maxR+N, target));
        if (maxL[li1] != target || maxR[ri1] != target) continue;
        int li2 = distance(maxL, prev(upper_bound(maxL, maxL+N, target)));
        int ri2 = distance(maxR, prev(upper_bound(maxR, maxR+N, target)));
        ri1 = N-1-ri1;
        ri2 = N-1-ri2;
        //cout << target << " " << li1 << " " << li2 << " " << ri2 << " " << ri1 << endl;
        // Avoid any bad locations possible
        auto ptr = avoid.lower_bound(ri2);
        if (ptr != avoid.end()) ri1 = min(*ptr, ri1);
        ptr = avoid.upper_bound(li2);
        if (ptr != avoid.begin()) li1 = max(*prev(ptr), li1);
        //cout << target << " " << li1 << " " << li2 << " " << ri2 << " " << ri1 << endl;
        // Find location
        ptr = avoid.upper_bound(li2);
        if (ptr != avoid.end() && *ptr < ri2) continue;  // Cannot form min
        // Range is clear of bad locations; can we form correct min?
        ptr = minLocs.upper_bound(li1);
        if (ptr == minLocs.end() || *ptr >= ri1) continue;
        // Valid loc found!
        //cout << "minLoc " << *ptr << endl;
        cout << "YES\n";
        cout << li1+1 << " " << N-(N-ri1)-(li1+1) << " " << N-ri1 << "\n";
        return;
    }

    cout << "NO\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}