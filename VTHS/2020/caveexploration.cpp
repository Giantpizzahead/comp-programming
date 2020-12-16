#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 103;

int N;
int H[MAXN][MAXN];
int bestDist[MAXN][MAXN];
bool visited[MAXN][MAXN];
int cx[] = {1, 0, -1, 0}, cy[] = {0, 1, 0, -1};

priority_queue<pair<int, pair<int, int>>> pq;

void solve() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> H[i][j];
            bestDist[i][j] = 1e9;
        }
    }
    bestDist[0][0] = 0;
    pq.emplace(0, make_pair(0, 0));
    while (!pq.empty()) {
        auto ptr = pq.top();
        int c = -ptr.first;
        int x = ptr.second.first;
        int y = ptr.second.second;
        pq.pop();
        for (int d = 0; d < 4; d++) {
            int nx = x + cx[d], ny = y + cy[d];
            if (nx < 0 || nx >= N || ny < 0 || ny >= N || visited[nx][ny]) continue;
            int nc = max(c, H[nx][ny]);
            if (bestDist[nx][ny] > nc) {
                bestDist[nx][ny] = nc;
                pq.emplace(-bestDist[nx][ny], make_pair(nx, ny));
            }
        }
    }
    cout << bestDist[N-1][N-1] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    // cin >> T;
    for (int i = 1; i <= T; i++) {
        solve();
    }
    return 0;
}