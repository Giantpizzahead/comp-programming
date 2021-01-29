#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 5e5+5;

int N, M, currI;
// int edge[MAXN];
bool isRoot[MAXN];
vi used;

struct DisjointSet {
    int R[MAXN], S[MAXN], leftMost[MAXN];

    DisjointSet() {
        rep(i, 0, MAXN) {
            R[i] = -1;
            S[i] = 1;
            leftMost[i] = i;
        }
    }

    int find(int n) {
        if (R[n] == -1) return n;
        int res = find(R[n]);
        R[n] = res;
        return res;
    }

    int getLeft(int n) {
        return leftMost[find(n)];
    }

    void merge(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return;
        if (a > b) swap(a, b);
        if (S[a] > S[b]) {
            S[a] += S[b];
            leftMost[a] = min(leftMost[a], leftMost[b]);
            R[b] = a;
        } else {
            S[b] += S[a];
            leftMost[b] = min(leftMost[a], leftMost[b]);
            R[a] = b;
        }
    }
};

DisjointSet ds;

void insert1(int a) {
    a = ds.getLeft(a);
    if (isRoot[a]) return;  // Can be made
    else {
        // Add this vector
        used.push_back(currI);
        isRoot[a] = true;
    }
}

void insert2(int a, int b) {
    a = ds.getLeft(a);
    b = ds.getLeft(b);
    if (isRoot[a] && isRoot[b]) return;  // Can be made
    if (a == b) return;  // The two cancel out
    // Must add vector
    if (a > b) swap(a, b);
    used.push_back(currI);
    if (isRoot[a]) {
        // Only b remains
        isRoot[b] = true;
    } else if (isRoot[b]) {
        // Only a remains
        isRoot[a] = true;
    } else {
        // Both remain
        ds.merge(a, b);
    }
}

void solve() {
    cin >> N >> M;
    rep(i, 0, N) {
        currI = i;
        int k, a, b;
        cin >> k;
        if (k == 1) {
            cin >> a;
            a--;
            insert1(a);
        } else {
            cin >> a >> b;
            a--, b--;
            if (a > b) swap(a, b);
            insert2(a, b);
        }
    }
    int answer = 1;
    rep(i, 0, sz(used)) {
        answer = answer * 2 % 1000000007;
    }
    cout << answer << " " << sz(used) << "\n";
    rep(i, 0, sz(used)) {
        if (i != 0) cout << " ";
        cout << used[i]+1;
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}