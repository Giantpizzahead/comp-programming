#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 2e5+5, LOGN = 19;
const int INF = 1e9;

int N, Q;
int parent[LOGN][MAXN], movieCount[MAXN];
pair<int, int> movies[MAXN];

void solve() {
    cin >> N >> Q;
    for (int i = 0; i < N; i++) cin >> movies[i].first >> movies[i].second;
    sort(movies, movies+N, [](const pair<int, int>& a, const pair<int, int>& b) {
        if (a.first == b.first) return a.second < b.second;
        else return a.first > b.first;
    });
    int ri = 0, minSoFar = INF;
    for (int i = 0; i < N; i++) {
        if (movies[i].second >= minSoFar) continue;
        else {
            minSoFar = movies[i].second;
            movies[ri++] = movies[i];
        }
    }
    movies[ri++] = {INF, INF};
    N = ri;
    sort(movies, movies+N);

    movieCount[N-1] = 0;
    parent[0][N-1] = N-1;
    for (int i = N-2; i >= 0; i--) {
        auto ptr = lower_bound(movies, movies+N, pair<int, int>{movies[i].second, -1});
        parent[0][i] = ptr-movies;
        movieCount[i] = movieCount[parent[0][i]] + 1;
    }

    for (int i = 1; i < LOGN; i++) {
        for (int j = 0; j < N; j++) {
            parent[i][j] = parent[i-1][parent[i-1][j]];
            // cout << parent[i][j] << ' ';
        }
        // cout << endl;
    }
    // cout << "movies\n";
    // for (int i = 0; i < N; i++) cout << movies[i].first << ' ' << movies[i].second << endl;

    int a, b;
    for (int i = 0; i < Q; i++) {
        cin >> a >> b;
        a = lower_bound(movies, movies+N, pair<int, int>{a, -1}) - movies;
        if (movies[a].second > b) {
            cout << "0\n";
            continue;
        }
        // Find last movie watched
        int l = a;
        for (int k = LOGN-1; k >= 0; k--) {
            if (movies[parent[k][l]].second <= b) {
                l = parent[k][l];
            }
        }
        cout << movieCount[a] - movieCount[parent[0][l]] << '\n';
        // cout << "pair " << a << " " << l << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}