#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1000;

int N, M;
int width[MAXN], top[MAXN], bot[MAXN];
queue<int> trees[MAXN];
char grid[MAXN][MAXN];

stack<int> S;
int solveFixed() {
    S.push(-1);
    rep(i, 0, N) {
        while (S.size() > 1 && width[S.top()] >= width[i]) S.pop();
        top[i] = S.top()+1;
        S.push(i);
    }
    while (!S.empty()) S.pop();
    S.push(N);
    for (int i = N-1; i >= 0; i--) {
        while (S.size() > 1 && width[S.top()] >= width[i]) S.pop();
        bot[i] = S.top()-1;
        S.push(i);
    }
    while (!S.empty()) S.pop();
    int answer = 0;
    rep(i, 0, N) {
        answer = max((bot[i]-top[i]+1) * width[i], answer);
    }
    // cout << "fixed " << answer << endl;
    return answer;
}

void solve() {
    cin >> N >> M;
    rep(i, 0, N) {
        string str;
        cin >> str;
        rep(j, 0, M) {
            grid[i][j] = str[j];
            if (grid[i][j] == '*') trees[i].push(j);
        }
        trees[i].push(M);
    }
    int answer = 0;
    rep(j, 0, M) {
        // Fix left bound of rectangle
        rep(i, 0, N) {
            width[i] = trees[i].front() - j;
            if (trees[i].front() == j) trees[i].pop();
            // cout << width[i] << ' ';
        }
        // cout << endl;
        answer = max(solveFixed(), answer);
    }
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}