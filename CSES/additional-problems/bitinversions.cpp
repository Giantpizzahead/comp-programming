#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 2e5+5;

int N, M;
string str;

struct SegmentTree {
    int left0[MAXN*4+1], left1[MAXN*4+1], right0[MAXN*4+1], right1[MAXN*4+1], answer[MAXN*4+1];

    void init(int n = 1, int lb = 0, int ub = N-1) {
        if (lb == ub) {
            answer[n] = 1;
            if (str[lb] == '0') {
                left0[n] = 1;
                left1[n] = 0;
                right0[n] = 1;
                right1[n] = 0;
            } else {
                left0[n] = 0;
                left1[n] = 1;
                right0[n] = 0;
                right1[n] = 1;
            }
            return;
        }
        init(n*2, lb, (lb+ub)/2);
        init(n*2+1, (lb+ub)/2+1, ub);
        merge(n, lb, ub);
    }

    void merge(int n, int lb, int ub) {
        left0[n] = left0[n*2];
        if (left0[n*2] == (lb+ub)/2-lb+1) left0[n] = left0[n*2] + left0[n*2+1];
        left1[n] = left1[n*2];
        if (left1[n*2] == (lb+ub)/2-lb+1) left1[n] = left1[n*2] + left1[n*2+1];
        right0[n] = right0[n*2+1];
        if (right0[n*2+1] == ub-(lb+ub)/2) right0[n] = right0[n*2+1] + right0[n*2];
        right1[n] = right1[n*2+1];
        if (right1[n*2+1] == ub-(lb+ub)/2) right1[n] = right1[n*2+1] + right1[n*2];
        answer[n] = max(max(answer[n*2], answer[n*2+1]), max(right0[n*2] + left0[n*2+1], right1[n*2] + left1[n*2+1]));
    }

    void update(int i, int n = 1, int lb = 0, int ub = N-1) {
        if (lb == ub) {
            swap(left0[n], left1[n]);
            swap(right0[n], right1[n]);
            return;
        } else if (i > (lb+ub)/2) update(i, n*2+1, (lb+ub)/2+1, ub);
        else update(i, n*2, lb, (lb+ub)/2);
        merge(n, lb, ub);
    }

    int query() {
        return answer[1];
    }
};

SegmentTree segt;

void solve() {
    cin >> str;
    N = str.size();
    segt.init();
    cin >> M;
    int x;
    for (int i = 0; i < M; i++) {
        cin >> x;
        x--;
        segt.update(x);
        if (i != 0) cout << ' ';
        cout << segt.query();
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}