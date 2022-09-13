/*
Generator for sugar rush.
*/

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

int N, C;
set<int> nums;

void solve() {
    N = rand() % 10 + 2;
    C = rand() % 100 + N + 5;
    while (sz(nums) < N) {
        int x = rand() % C + 1;
        nums.insert(x);
    }
    cout << N << '\n';
    for (int x : nums) cout << x << ' ';
    cout << endl;
}

int main(int argc, char* argv[]) {
    srand(atoi(argv[1]));
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    solve();
    return 0;
}