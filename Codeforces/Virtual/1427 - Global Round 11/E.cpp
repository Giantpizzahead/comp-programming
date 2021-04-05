#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXQ = 1e5;
const ll MAXC = 1e18;

int X, Q, M;
set<ll> numsSet;
vector<ll> nums;

int randint(int a, int b) {
    return rand() % (b-a+1) + a;
}

vector<string> ops;

void doOp(ll a, ll b, ll r, int t) {
    Q++;
    if (r == 1) Q = MAXQ;  // Found it!
    if (t == 0) ops.push_back(to_string(a) + " + " + to_string(b));
    else ops.push_back(to_string(a) + " ^ " + to_string(b));
}

void solve() {
    srand(time(NULL));
    cin >> X;
    nums.push_back(X);
    numsSet.insert(X);
    // Rely on randomness
    while (true) {
        rep(j, 0, 300) {
            int a = randint(0, sz(nums)-1);
            int b = randint(0, sz(nums)-1);
            int t = randint(0, 1);
            ll r;
            if (t == 0) {
                r = nums[a] + nums[b];
            } else {
                r = nums[a] ^ nums[b];
            }
            if (r <= MAXC && !numsSet.count(r)) {
                doOp(nums[a], nums[b], r, t);
                nums.push_back(r);
                numsSet.insert(r);
                if (Q == MAXQ) goto endPrint;
            }
        }
        sort(all(nums));
        M = sz(nums);
        rep(j, 1, M) {
            ll r = nums[j-1] ^ nums[j];
            if (!numsSet.count(r)) {
                doOp(nums[j-1], nums[j], r, 1);
                nums.push_back(r);
                numsSet.insert(r);
                if (Q == MAXQ) goto endPrint;
            }
        }
    }
    endPrint:
    // sort(all(nums));
    // for (int x : nums) cout << x << ' ';
    // cout << endl;

    cout << sz(ops) << '\n';
    rep(i, 0, sz(ops)) {
        cout << ops[i] << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}