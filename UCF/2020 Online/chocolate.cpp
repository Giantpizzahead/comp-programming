#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 100005;

int N, M, answer;
pair<int, int> points[MAXN * 2];

void solve() {
    cin >> N >> M;
    int a, b;
    for (int i = 0; i < M; i++) {
        cin >> a >> b;
        points[i*2] = {a-1, 0};
        points[i*2+1] = {b, 1};
    }
    sort(points, points + 2*M);
    answer = 0;
    int lastCount = 0, currCount = 0, cj = 0;
    for (int i = 0; i <= N; i++) {
        while (cj != M * 2 && points[cj].first == i) {
            if (points[cj].second == 0) currCount++;
            else currCount--;
            cj++;
        }
        if (currCount < lastCount) answer += lastCount - currCount;
        lastCount = currCount;
    }
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        solve();
    }
    return 0;
}