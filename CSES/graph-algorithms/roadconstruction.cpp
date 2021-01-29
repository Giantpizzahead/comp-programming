#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 1e5;

int N, M;

struct DisjointSet {
    int V[MAXN], S[MAXN], numComps, largestSize = 1;

    DisjointSet() {
        fill(V, V+MAXN, -1);
        fill(S, S+MAXN, 1);
    }

    int find(int i) {
        if (V[i] == -1) return i;
        else {
            int res = find(V[i]);
            V[i] = res;
            return res;
        }
    }

    void merge(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        else if (S[a] > S[b]) {
            S[a] += S[b];
            S[b] = 0;
            largestSize = max(S[a], largestSize);
            V[b] = a;
        } else {
            S[b] += S[a];
            S[a] = 0;
            largestSize = max(S[b], largestSize);
            V[a] = b;
        }
        numComps--;
    }
};

DisjointSet ds;

void solve() {
    cin >> N >> M;
    ds.numComps = N;
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        ds.merge(a, b);
        cout << ds.numComps << ' ' << ds.largestSize << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}