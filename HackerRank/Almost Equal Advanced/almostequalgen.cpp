#include <iostream>
using namespace std;

const int MAXN = 100000, MAXQ = 100000, MAXC = 1e9;

int randInt(int l, int r) {
    return rand() % (r-l+1) + l;
}

int N, K, Q;
int H[MAXN], L[MAXQ], R[MAXQ];

int main(int argc, const char* argv[]) {
    srand(hash<const char*>()(argv[1]));
    N = randInt(100000, MAXN);
    K = randInt(0, MAXC);
    int Q = randInt(100000, MAXQ);
    for (int i = 0; i < N; i++) H[i] = randInt(0, MAXC);
    for (int i = 0; i < Q; i++) {
        L[i] = randInt(0, N-1);
        R[i] = randInt(0, N-1);
        if (L[i] > R[i]) swap(L[i], R[i]);
    }

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout << N << " " << K << '\n';
    for (int i = 0; i < N; i++) cout << H[i] << ' ';
    cout << '\n' << Q << '\n';
    for (int i = 0; i < Q; i++) cout << L[i] << ' ' << R[i] << '\n';
    return 0;
}