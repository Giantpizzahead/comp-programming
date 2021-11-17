#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); ++i)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXS = 16384;

int N, M, answer = 0;

bool A[MAXS];

int V[MAXS*2];
bool on[MAXS*2];

int cnt[MAXS], newRoot[MAXS];

int stackTop = 0;
int stackArr[MAXS*2];

int find(int i) {
    while (V[i] >= 0) {
        stackArr[stackTop++] = i;
        i = V[i];
    }
    while (stackTop != 0) {
        V[stackArr[--stackTop]] = i;
    }
    return i;
}

int merge(int a, int b) {
    assert(on[a] || on[b]);
    if (!on[a]) return b;
    if (!on[b]) return a;
    a = find(a), b = find(b);
    if (a == b) return a;
    answer--;
    if (V[a] < V[b]) {
        V[a] += V[b];
        V[b] = a;
        return a;
    } else {
        V[b] += V[a];
        V[a] = b;
        return b;
    }
}

void activate(int i) {
    if (!on[i]) {
        on[i] = true;
        ++answer;
    }
}

void solve() {
    cin >> N >> M;
    int x;
    char s;
    rep(i, 0, MAXS*2) {
        V[i] = -1;
        on[i] = false;
    }
    rep(i, 0, N) {
        string S; cin >> S;
        rep(j, 0, M/4) {
            s = S[j];
            if (s >= '0' && s <= '9') x = s - '0';
            else x = s - 'A' + 10;
            A[4*j] = (x & 0b1000) != 0;
            A[4*j+1] = (x & 0b0100) != 0;
            A[4*j+2] = (x & 0b0010) != 0;
            A[4*j+3] = (x & 0b0001) != 0;
        }
        // Transition to next row
        rep(j, 0, M) {
            if (!A[j]) continue;
            activate(M+j);
            if (j != 0) merge(M+j, M+j-1);
            if (j != M-1) merge(M+j, M+j+1);
            merge(M+j, j);
        }
        // Replace roots that are moving out of range
        rep(j, 0, M) {
            cnt[j] = 0;
            newRoot[j] = -1;
        }
        rep(j, 0, M) {
            if (!on[M+j]) continue;
            find(M+j);
        }
        rep(j, 0, M) {
            if (!on[M+j]) continue;
            int r = (V[M+j] < 0 ? M+j : V[M+j]);
            if (r < M) {
                // Move root
                if (cnt[r] == 0) {
                    newRoot[r] = M+j;
                }
                ++cnt[r];
                V[M+j] = newRoot[r];
                // if (M+j == newRoot[r]) debug << "same " << M+j << endl;
            }
        }
        // Migrate root sizes
        rep(j, 0, M) {
            if (newRoot[j] != -1) {
                // debug << "set " << newRoot[j] << " neg " << endl;
                V[newRoot[j]] = -cnt[j];
            }
        }
        // Migrate row
        rep(j, 0, M) {
            // assert(V[M+j] >= M || V[M+j] < 0);
            V[j] = V[M+j];
            if (V[j] >= M) V[j] -= M;
            on[j] = on[M+j];
            V[M+j] = -1;
            on[M+j] = false;
        }
    }
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}