#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

int answer = 0;
bool board[8][8], temp[8][8], queens[8][8], col[8];

bool checkDiag() {
    rep(k, 0, 15) {
        int i = max(k-7, 0), j = min(k, 7);
        bool queen = false;
        for (int l = 0; l < min(k+1, 15-k); l++, i++, j--) {
            if (queens[i][j]) {
                if (queen) return false;
                queen = true;
            }
        }
    }
    return true;
}

void rotateCCW() {
    rep(i, 0, 8) {
        rep(j, 0, 8) {
            temp[7-j][i] = queens[i][j];
        }
    }
    swap(temp, queens);
}

void rotateCW() {
    rep(i, 0, 8) {
        rep(j, 0, 8) {
            temp[i][j] = queens[7-j][i];
        }
    }
    swap(temp, queens);
}

bool check() {
    bool yes = true;
    yes &= checkDiag();
    rotateCW();
    yes &= checkDiag();
    rotateCCW();
    return yes;
}

void go(int i) {
    if (i == 8) {
        if (check()) answer++;
        return;
    }
    rep(j, 0, 8) {
        if (!col[j] && board[i][j]) {
            col[j] = true;
            queens[i][j] = true;
            go(i+1);
            col[j] = false;
            queens[i][j] = false;
        }
    }
}

void solve() {
    string str;
    rep(i, 0, 8) {
        cin >> str;
        rep(j, 0, 8) board[i][j] = str[j] == '.';
    }
    go(0);
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}