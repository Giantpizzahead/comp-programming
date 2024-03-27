#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

int N, M;
struct Model {
    int s, n;
};
vector<Model> S;

void solve() {
    S.clear();
    cin >> N >> M;
    rep(i, 0, M) {
        int x; cin >> x;
        S.push_back({x, 0});
    }
    rep(i, 0, N) {
        unordered_map<int, int> P;
        rep(j, 0, M) {
            int x; cin >> x;
            P[x]++;
        }
        sort(all(S), [](const Model& a, const Model& b) {
            return a.n > b.n;
        });
        vector<int> toSwitch;
        rep(j, 0, M) {
            if (P[S[j].s] == 0) {
                // This model must switch
                S[j].n++;
                toSwitch.push_back(j);
            } else P[S[j].s]--;
        }
        for (int x : toSwitch) {
            while (true) {
                auto p = P.begin();
                if (p->second == 0) P.erase(p);
                else {
                    p->second--;
                    S[x].s = p->first;
                    break;
                }
            }   
        }
        // cout << "round " << i << endl;
        // rep(j, 0, M) cout << S[j].s << " " << S[j].n << endl;
    }
    ll answer = 0;
    rep(j, 0, M) answer += max(S[j].n-1, 0);
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int T; cin >> T;
    rep(i, 0, T) {
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    return 0;
}