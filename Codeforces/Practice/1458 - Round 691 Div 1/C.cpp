#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1001;

int N, M;
int loc[3], delta[3];
struct Point {
    int i, j, v;
};
vector<Point> points;
string str;

int arr[MAXN][MAXN];

void solve() {
    rep(i, 0, 3) {
        loc[i] = i;
        delta[i] = 0;
    }
    cin >> N >> M;
    points.clear();
    rep(i, 0, N) {
        rep(j, 0, N) {
            int x;
            cin >> x;
            points.push_back({i, j, x-1});
        }
    }

    cin >> str;
    rep(i, 0, M) {
        char c = str[i];
        if (c == 'R') {
            delta[1]++;
        } else if (c == 'L') {
            delta[1]--;
        } else if (c == 'D') {
            delta[0]++;
        } else if (c == 'U') {
            delta[0]--;
        } else if (c == 'I') {
            swap(loc[1], loc[2]);
            swap(delta[1], delta[2]);
        } else if (c == 'C') {
            swap(loc[0], loc[2]);
            swap(delta[0], delta[2]);
        }
    }

    int i, j, v;
    for (Point& p : points) {
        if (loc[0] == 0) i = p.i + delta[0];
        if (loc[0] == 1) i = p.j + delta[0];
        if (loc[0] == 2) i = p.v + delta[0];
        if (loc[1] == 0) j = p.i + delta[1];
        if (loc[1] == 1) j = p.j + delta[1];
        if (loc[1] == 2) j = p.v + delta[1];
        if (loc[2] == 0) v = p.i + delta[2];
        if (loc[2] == 1) v = p.j + delta[2];
        if (loc[2] == 2) v = p.v + delta[2];
        i = ((i % N) + N) % N;
        j = ((j % N) + N) % N;
        v = ((v % N) + N) % N;
        arr[i][j] = v;
    }

    rep(i, 0, N) {
        rep(j, 0, N) {
            if (j != 0) cout << ' ';
            cout << arr[i][j]+1;
        }
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    rep(i, 0, T) {
        if (i != 0) cout << '\n';
        solve();
    }
    return 0;
}