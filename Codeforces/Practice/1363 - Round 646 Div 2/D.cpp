#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 1005;

int N, K;
int inSet[MAXN];
vector<int> A[MAXN];

vector<int> nums;

int query() {
    cout << "? " << sz(nums);
    for (int x : nums) cout << " " << x;
    cout << endl;
    nums.clear();
    int x; cin >> x;
    if (x == -1) exit(0);
    return x;
}

void solve() {
    cin >> N >> K;
    rep(i, 1, N+1) inSet[i] = -1;
    rep(i, 0, K) {
        A[i].clear();
        int c; cin >> c;
        rep(j, 0, c) {
            int x; cin >> x;
            inSet[x] = i;
            A[i].push_back(x);
        }
    }
    
    // Find maximum of all
    rep(i, 1, N+1) nums.push_back(i);
    int maxAll = query();
    
    // Binary search for maximum
    int low = 0, high = K-1;
    while (low < high) {
        int mid = (low + high) / 2;
        // Check if maximum is on left side
        rep(i, low, mid+1) {
            for (int x : A[i]) nums.push_back(x);
        }
        if (query() == maxAll) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    
    // Find maximum outside
    rep(i, 1, N+1) {
        if (inSet[i] == low) continue;
        nums.push_back(i);
    }
    int maxOut = query();
    
    // Guess the password
    cout << "!";
    rep(i, 0, K) {
        cout << " ";
        if (i == low) cout << maxOut;
        else cout << maxAll;
    }
    cout << endl;
    
    string str; cin >> str;
    if (str != "Correct") exit(0);
}

int main() {
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}