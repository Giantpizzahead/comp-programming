#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

int randint(int a, int b) {
    return rand() % (b-a+1) + a;
}

void solve() {
    int T = randint(1, 45);
    cout << T << "\n";
    rep(i, 0, T) {
        int N = randint(2, 250);
        cout << N << "\n";
        vector<int> xToI(N);
        rep(j, 0, N) xToI[j] = j+1;
        vector<pair<int, int>> M;
        rep(a, 1, N) {
            int b = randint(0, a-1);
            if (randint(1, 2) == 1) M.emplace_back(a, b);
            else M.emplace_back(b, a);
        }
        random_shuffle(all(xToI));
        random_shuffle(all(M));
        for (auto& e : M) {
            cout << xToI[e.first] << " " << xToI[e.second] << " " << randint(1, 20) << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    srand(chrono::system_clock::now().time_since_epoch().count());
    solve();
    return 0;
}