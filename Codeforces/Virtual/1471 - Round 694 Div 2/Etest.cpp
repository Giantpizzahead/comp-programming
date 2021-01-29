#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1e5+5;

int N, K, P, R;
int C[MAXN], temp[MAXN];

void print() {
    rep(i, 0, N) cout << C[i] << ' ';
    cout << endl;
}

void solve() {
    cin >> N >> K >> P >> R;
    P--;
    rep(i, 0, N) C[i] = K;
    print();
    rep(j, 0, R) {
        rep(i, 0, N) temp[i] = 0;
        rep(i, 0, N) {
            if (i != P) {
                temp[(i+1)%N] += (C[i]+1)/2;
                int o = (i == 0 ? N-1 : i-1);
                temp[o] += C[i]/2;
            } else {
                temp[(i+1)%N] += C[i];
            }
        }
        swap(temp, C);
        print();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}