#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 2e5+5;

int N;
int A[MAXN];

struct BIT {
    ll V[MAXN];

    void upd(int i, ll v) {
        for (; i <= MAXN; i+=i&-i) {
            V[i] += v;
        }
    }

    ll query(int i) {
        ll r = 0;
        for (; i > 0; i-=i&-i) {
            r += V[i];
        }
        return r;
    }
} bit;

ll leftSum = 0, rightSum = 0;
set<int> leftSet, rightSet;

void solve() {
    cin >> N;
    rep(i, 1, N+1) {
        int x; cin >> x;
        A[x] = i;
    }
    ll inv = 0;
    rep(i, 1, N+1) {
        // Inversions
        bit.upd(A[i], 1);
        inv += i - bit.query(A[i]);

        // Add to median
        if (leftSet.empty() || *prev(leftSet.end()) >= A[i]) {
            leftSum += A[i];
            leftSet.insert(A[i]);
        } else {
            rightSum += A[i];
            rightSet.insert(A[i]);
        }
        // Balance the sets
        if (sz(leftSet) < sz(rightSet)) {
            auto ptr = rightSet.begin();
            leftSum += *ptr;
            rightSum -= *ptr;
            leftSet.insert(*ptr);
            rightSet.erase(ptr);
        } else if (sz(leftSet) - 1 > sz(rightSet)) {
            auto ptr = prev(leftSet.end());
            rightSum += *ptr;
            leftSum -= *ptr;
            rightSet.insert(*ptr);
            leftSet.erase(ptr);
        }

        // Join all numbers
        ll mid = *prev(leftSet.end());
        ll S = sz(leftSet);
        ll leftDist = mid * S - leftSum;
        leftDist -= S * (S-1) / 2;
        S = sz(rightSet);
        ll rightDist = rightSum - mid * S;
        rightDist -= S * (S+1) / 2;

        // cout << inv << ' ' << leftDist << ' ' << rightDist << endl;
        cout << inv + leftDist + rightDist << " \n"[i==N];
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}