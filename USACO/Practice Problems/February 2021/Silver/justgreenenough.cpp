#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 500;

int N;
int G[MAXN][MAXN];
bool A[MAXN][MAXN];

int leftB[MAXN];
vector<int> blocked[MAXN];
set<pair<int, int>> ranges;
ll countRects() {
    // Fix left column
    rep(i, 0, N) leftB[i] = N;
    ll answer = 0;
    for (int j = N-1; j >= 0; j--) {
        // Find leftmost blocked squares
        rep(i, 0, N) if (A[i][j]) leftB[i] = j;
        rep(i, j, N) blocked[i].clear();
        rep(i, 0, N) if (leftB[i] != N) blocked[leftB[i]].push_back(i);
        ll currCnt = N*(N+1)/2;
        ranges.clear();
        ranges.emplace(0, N-1);
        rep(k, j, N) {
            // Process blocked events
            for (int b : blocked[k]) {
                auto ptr = prev(ranges.upper_bound({b, INT32_MAX}));
                // Split range
                int l = ptr->first, r = ptr->second;
                ranges.erase(ptr);
                int length = r-l+1;
                currCnt -= length*(length+1)/2;
                if (l != b) {
                    ranges.emplace(l, b-1);
                    length = b-l;
                    currCnt += length*(length+1)/2;
                }
                if (b != r) {
                    ranges.emplace(b+1, r);
                    length = r-b;
                    currCnt += length*(length+1)/2;
                }
            }
            // Add to answer
            answer += currCnt;
        }
    }
    return answer;
}

void solve() {
    cin >> N;
    rep(i, 0, N) {
        rep(j, 0, N) {
            cin >> G[i][j];
            if (G[i][j] < 100) G[i][j] = 0;
            else if (G[i][j] == 100) G[i][j] = 1;
            else G[i][j] = 2;
        }
    }
    // Answer = (# with no < 100) - (# with no <= 100)
    ll answer = 0;
    rep(i, 0, N) rep(j, 0, N) A[i][j] = (G[i][j] == 0);
    answer += countRects();
    rep(i, 0, N) rep(j, 0, N) A[i][j] = (G[i][j] <= 1);
    answer -= countRects();
    cout << answer << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}